/*
 * main.h
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

#ifndef CARAPI_H_
#define CARAPI_H_

#include "RemoteConnection.h"
#include "../networking/WelcomeMessage.h"
#include "../networking/UltrasoundDistanceMessage.h"
#include "../networking/UltrasoundConfigurationMessage.h"
#include "../networking/MotorVelocityMessage.h"
#include "../networking/MotorMeasurementMessage.h"

#include "SensorState.h"
#include "UltrasoundSensorState.h"
#include "GSensorState.h"
#include "ADCSensorState.h"

typedef struct
{
	// General information
	alt_u8	uiVersion;
	alt_u8	uiType;
	alt_u8	uiID;
	alt_u8	uiOperations[4];
	(CSensorState*)	p_sensors[4];
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


typedef struct
{
	MotorECU_State	motorStates[4];

	alt_32 iMaxSpeed;
} Car_State;

bool startConnection();
bool stopConnection();

bool getState(Car_State *p_state);
bool setState(Car_State *p_state);

#endif /* CARAPI_H_ */
