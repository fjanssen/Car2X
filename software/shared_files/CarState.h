/*
 * CarState.h
 *
 *  Created on: Jun 19, 2014
 *      Author: wji
 */

#ifndef CARSTATE_H_
#define CARSTATE_H_


#include "alt_types.h"

// Car Hardware configuration
#define CAR_NUM_MOTORS (4)
#define CAR_NUM_USS    (2)

// Settings for the various Operation modes of the car.
#define OPMODE_IDLE_MAXSPEED          (0u)
#define OPMODE_AUTODRIVE_MAXSPEED     (200u)
#define OPMODE_MANUDRIVE_MAXSPEED     (400u)
#define OPMODE_EMERGENCYSTOP_MAXSPEED (0u)


enum OpMode {
	OPMODE_IDLE,
	OPMODE_AUTODRIVE,
	OPMODE_MANUDRIVE,
	OPMODE_EMERGENCYSTOP,
};

struct Velocity
{
	alt_16 iFrontLeft;
	alt_16 iFrontRight;
	alt_16 iRearLeft;
	alt_16 iRearRight;
};

struct UsSensor_State
{
	alt_u32 distance;
};

struct MotorECU_State
{
	// General information
	alt_u8	uiVersion;
	alt_u8	uiType;
	alt_u8	uiID;
	alt_u8	uiOperations[4];
	//CSensorState*	p_sensors[4];
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
};

/*
 * This struct contains all information about one motor-ECU.
 */
typedef struct CarState {
	alt_u64 timeStamp;
	alt_32 iMaxSpeed;
	enum OpMode currMode;
	enum OpMode reqMode;
	struct MotorECU_State motorEcus[CAR_NUM_MOTORS];
	struct UsSensor_State usSensors[CAR_NUM_USS];
	struct Velocity reqVelocity;
};

#endif /* CARSTATE_H_ */
