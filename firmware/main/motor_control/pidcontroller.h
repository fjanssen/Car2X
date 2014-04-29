/*
 * pidcontroller.h
 *
 *  Created on: 25.11.2013
 *      Author: Florian
 */

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

#include <alt_types.h>


/*
 * Class implements a PI-Controller.
 *
 * The motor + hall-sensor shows PT1 behavior:
 *
 *   A speed
 * K |              XXXXXXX
 *   |        XXXXXX
 *   |    XXXX
 *   | XXX
 *   |XX
 * 0 X------------------> time
 *   0 T1             Tk
 *
 * To control a PT1 system you only need a PI controller. A D-value is not necessary or will have
 * no impact on the control value.
 *
 * The control-circle will be:
 *                                                                                      (current_speed)
 *                   +---+ (error)    +---------------+ (control value)  +------------+ (natural value)
 * desired_speed --->| + |----------->| PI controller |----------------->| Motor (P!) |-----+--->
 *                   +---+            +---------------+                  +------------+     |
 *                     A (-)                                                                |
 *     (current_speed) |                           (current_speed)                          |
 *     (mm/sec)        |   +---------------------+ (ticks 10ms)     +-------------------+   |
 *                     +---| Conversion (linear) |<-----------------| Hall-Sensor (T1!) |<--+
 *                         +---------------------+                  +-------------------+
 *
 * desired_speed, error in mm/sec. control value in 0.01 % (100000 is 100%).
 * (-) means negative value
 *
 * !: The exact transfer functions for the motor and the sensor are unknown. We assume that both
 *    have PT1 behavior. The motor dominates with his P and the sensor dominates with his T.
 *    Together they have a dominating PT1 behavior but in the strict sense total a PT2 behavior.
 *    Thus we can never guarantee that our PI controller produces no overshoots. The probability
 *    for this scenario may be very low and the overshoots also.
 *
 * The controller is written in software. This causes a high discretization (error). The speed
 * is not controlled continuously but every 10ms. With this errors and delays the PT2 behavior
 * becomes more unstable. We recommend a (hardware) implementation in the FPGA. This will
 * also not be fully continuously but will control the speed more detailed.
 *
 * All together the system has PIT1 behavior. This means there is still a remaining delay for
 * acceleration and slow-down!
 */
class CPIController
{
public:
	/*
	 * Constructs a new PI-Controller with the given P-, I- and Min/Max-Values.
	 */
	CPIController(alt_32 iPValue, alt_32 iIValue, alt_32 iMinimum, alt_32 iMaximum);

	/*
	 * Empty destructor.
	 */
	~CPIController(void);

	/*
	 * Returns the next speed using the given error.
	 * iError: desired_speed - current_speed in mm/sec
	 * return: next_speed in 0.01% (100000 means 100%) in 2-complement
	 */
	alt_32 control(alt_32 iError);

	// Getter / Setter methods
	void changeController(alt_32 iPValue, alt_32 iIValue);
	void getController(alt_32 *p_iPValue, alt_32 *p_iIValue);

private:
	alt_32 m_iPValue;
	alt_32 m_iIValue;

	alt_32 m_iMinimum; // in mm/sec
	alt_32 m_iMaximum; // in mm/sec

	alt_64 m_iErrorSum;  // in mm/sec
	alt_32 m_iLastError; // in mm/sec
};


#endif /* PIDCONTROLLER_H_ */
