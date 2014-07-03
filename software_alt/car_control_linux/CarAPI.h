/*
 * main.h
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

#ifndef CARAPI_H_
#define CARAPI_H_

#include "RemoteConnection.h"
#include "../sensors/SensorState.h"

/*
 * This file seperates the logical and networking part of the central ECU.
 *
 * One proper way to handle this functions is:
 * 1. Call startConnection() // Enables networking and starts new Thread
 * 2. Allocate space for one Car_State object
 * 3. Call getState(..) with the said object. You will get a copy of the current state
 * 4. Call the sensors (Car_State.motorStates[i].p_sensors[j]->get....()) for additional 
 *    state information (distance, ADC values, ...)
 * 5. Use the information to do something.
 * 6. Get a more actual copy of the internal state by calling getState() once again.
 * 7. Set something in this copy to a new value (e.g. set a new desired_speed).
 * 8. Call setState(..) to transfer your changes. 
 *    It takes some time that the car adopts the new values (see message delay).
 * 9. Return to step 3. or call stopConnection() before program exit.
 */

/*
 * This struct contains all information about one motor-ECU.
 */
typedef struct
{
	// General information
	alt_u8	uiVersion;
	alt_u8	uiType;
	alt_u8	uiID;
	alt_u8	uiOperations[4];
	CSensorState*	p_sensors[4];
	alt_32	iSensorCount;

	// PID Controller information
	alt_16 	iMaxSpeed;
	alt_u16	uiWheelCircumference;
	alt_16	iPType;
	alt_16	iIType;
	alt_16	iDType;

	// Speed state
	alt_16	iDesiredSpeed;
	alt_16	iCurrentSpeed;
} MotorECU_State;

/*
 * This struct contains the four MotorECU states and the over all 
 * information (such as the current allowed maxSpeed).
 */
typedef struct
{
	MotorECU_State	motorStates[4];

	alt_32 iMaxSpeed;
} Car_State;

/*
 * Enables the connection to the car and starts the data interchange.
 * This function starts a new Thread and initializes the necessary mutexes.
 *
 * Note: Make sure that this function is called only once!
 */
bool startConnection();

/*
 * Stops the communication thread and waits for it to be terminated.
 */
bool stopConnection();

/*
 * Gets a copy of the current Car State. The current state is copied to the given 
 * Car_State reference.
 *
 * This function is thread safe!
 */
bool getState(Car_State *p_state);

/*
 * Updates the internal Car_State with the given one. 
 *
 * Make sure that the given Car_State is mostly up-to-date because it will be copied 
 * completely!
 *
 * This function is thread safe!
 */
bool setState(Car_State *p_state);

#endif /* CARAPI_H_ */
