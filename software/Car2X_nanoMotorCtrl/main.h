/*
 * main.h
 *
 *  Created on: 11.11.2013
 *      Author: Florian
 */

#ifndef MAIN_H_
#define MAIN_H_

// Import interfaces:
#include <system.h>

#include <io.h>
#include <alt_types.h>

#include <sys/time.h>
#include <sys/alt_alarm.h>


#include "external_drivers\motor_pwm.h"
#include "external_drivers\eth_uart.h"

#include "CarProtocol.h"
#include "MotorMeasurementMessage.h"
#include "MotorVelocityMessage.h"
#include "WelcomeMessage.h"

#include "etc\utility.h"

#include "pidcontroller.h"
#include "properties.h"

/*
 * Main file of Motor-ECU.
 *
 * This file contains the starting point and working cycle of the Motor-ECU.
 *
 * Starting point is the main(..) function. This function controls the working cycle(s):
 * START --> INIT --> WELCOME --> PID MEASUREMENT --+-> BIG WORKING CYLCE --+-> (FAIL) --> EXIT
 *                                                  A                       |
 *                                                  +-----------------------+
 *
 * START:   Entry point
 * INIT:    Set global fields to zero.
 * WELCOME: Wait for the first WelcomeMessage. This is necessary to synchronize the Motor-ECUs.
 *          After this point every Motor-ECU should be nearly (theoretical clk) synchronous.
 *          Note: Due to the nature of TCP over Eth and the Eth2UART there is no guarantee that
 *          the ECUs work synchronous but the probability to do so is very high.
 * PID MEASUREMENT:
 *          Gets the P-, I- and D-Values for the PID controller by measurement or from the
 *          central ECU (Linux-PC) (second option not implemented yet).
 *          Note: The motors have a PT1 behavior so there is only a PI controller needed. The
 *          D-Value will be ignored (see also pidcontroller.h).
 *
 * EXIT on (FAIL):
 *         On every fail the speed is set to 0.
 *         Important Note: The central ECU is only informed about the failure because it gets no
 *         response from the Motor-ECU. Worst case (if you want to stop also the other motors) is
 *             CENTRAL to FAILED MOTOR: regular messages
 *             after 100 ms no response
 *             CENTRAL to all: stop
 *             after TCP / UART delay: motors try to stop
 *             after braking distance the car will be stopped
 *         The whole process can take about 500 ms!
 *
 *
 * BIG WORKING CYLCE:
 *         Cycle of exact 100 ms (+- a few clock cylces). Every run of this big cycle consists
 *         10 smaller cycle runs (SMALL WORKING CYCLE). Task of the big cycle is the network
 *         communication which is hard timed to the 100 ms. This means that every 100 ms there
 *         should be a new request from the central ECU and the last request is answered.
 *         A message ping will take aprox. 100 ms + 2 * TCP/UART delay. Don't forget that
 *         TCP/UART is not real-timed!
 *         Each of the small cycle runs controls the speed and handles one message (doAction) or
 *         waits for a new packet.
 *         Note: The big cycle does nothing but merges the small ones!
 *
 *
 * The SMALL WORKING CYLCE consists of:
 * --+-> WAIT --> CONTROL SPEED -+-> (state >= 9) --> WAIT FOR PACKET --+
 *   A                           |                                      V
 *   |                           +-> (state < 9 ) --> doAction() ------>+
 *   |                                                                  |
 *   +------------------------------------------------------------------+
 *
 * WAIT (WaitForEndOfCycle):
 *         The big cycle takes always 100ms, so the ten small cycles take each 10ms. At the begin
 *         of a small cycle run a timer is set to this 10ms. WaitForEndOfCycle will block until
 *         this timer reached 0. After that the timer is automatically set back to 10ms.
 *
 *         Note: The hard timing only works if the rest of the small cycle (including the
 *         doAction() method) doesn't take longer than 10 ms. There should be even a security
 *         window of 1-2ms!
 *         Don't forget that CONTROL SPEED itself takes some of the 10 ms. So said there are only
 *         4-5 ms remaining for your doAction()!
 *
 * CONTROL SPEED:
 *         The speed measurement takes place during the whole small cycle run. To get reliable
 *         measurement results this state has to be every 10 ms!
 *         It finishes the current running measurement, starts a new one and calls the PID
 *         controller to decide what the next speed should be. This new speed is given to the
 *         motor driver.
 *
 * doAction():
 *         Calls the doAction() method of the message with position [getMessageCount()-state-1].
 *         This is the reverse order. The last message in the packet is the first one handled.
 *         Use this ordering according to this:
 *         Message position | Handled at | Commands in the message | Results of the commands
 *         -----------------+------------+-------------------------+--------------------------
 *         First message    | last       | done after some delay   | the most current
 *             . . .        | .  .  .    |         . . .           |       .  .  .
 *         Last message     | first      | done immediate          | out-dated because of delay
 *
 *         The only exception of this rule is the VelocityMessage. If this message is the first in
 *         the packet (and it has to be the first!) it will be handled a number of times. The
 *         first time immediately after receiving the new packet and every time when CONTROL SPEED.
 *         This functionality guarantees that the desired speed is set immediately and the current
 *         speed is up-to-date!
 *
 * WAIT FOR PACKET:
 *         Receives a new packet and sends the answer of the last packet. Here is the highest
 *         possibility for an error which leads to the exit of the main function.
 *
 */



/*
 * Array which contains the (message-)types of all messages which can be understood by this build.
 * Only those types are included that are optional (so said with a value >= 8). Currently only
 * max. 4 message-types are supported.
 * All 4 array elements have to be filled with a value. Are there less then 4 messages the rest
 * should be filled up with 0x00.
 * This is implemented via AVAILABLE_OPERATIONS. See properties.h
 */
alt_u8 uiAvailableOperations[] = { AVAILABLE_OPERATIONS };

/*
 * Pointer to the LED register (memory mapped IO!).
 */
alt_u32 *pLED = (alt_u32 *) (0x80000000 | LED_BASE);

/*
 * Fields containing speed information of the wheel.
 */
alt_32 iCurrentSpeed; // 2-complement in mm/sec
alt_32 iDesiredSpeed; // 2-complement in mm/sec
alt_u32 uiMaxSpeed;   // unsigned in mm/sec

/*
 * Pointer (references) to used objects.
 */
CPIController *pController = 0; // Reference to the PI(D)-Controller
CEth_UART_Socket *pSocket = 0;  // Reference to the Ethernet to UART socket
CCarProtocol *pProtocol = 0;    // Reference to the current protocol

/*
 * Fields used for WaitForEndOfCycle
 */
bool bCycleFinished;    // If true the cycle is finished. Set by the timer!
static alt_alarm alarm; // Alarm structure

/*
 * Alarm callback. This function is called by the timer after 10ms. The return value will be
 * the next timer value.
 * This function will simply set the bCycleFinished to true. Thereby the WaitForEndOfCycle function
 * will not block anymore.
 */
alt_u32 alarm_callback(void* context)
{
	bCycleFinished = true;
	return 10;
}

// See INIT
bool init();

// See WAIT
bool sendWelcome();

// See CONTROL SPEED
bool controlSpeed();

// See WAIT FOR PACKET
bool waitForNextPacket();

// See PID MEASUREMENT
bool setUpPIController();

// See WAIT
bool waitForEndOfCycle();


#endif /* MAIN_H_ */
