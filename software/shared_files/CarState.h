/*********************************************************************
 *
 * CarState
 * 
 * \brief 
 *     The CarState struct contains all information pertaining to the
 *     car (motor speeds, operating mode, sensor data, control
 *     commands, etc). 
 *
 * \author Johannes <jwindelen@gmail.com>
 *
 * \details
 *     The CarState is used to shuffle data between the control core 
 *     and the communications core. Additionally, this file defines
 *     some configuration parameters and values.
 *
 * TODO: should the configuration parameters/values not be in another
 *     file?
 *
 *********************************************************************/

#ifndef CARSTATE_H_
#define CARSTATE_H_

/* ===================================================================
 * Includes
 * ==================================================================*/
#include "alt_types.h"

/* ===================================================================
 * Defines
 * ==================================================================*/
// Car Hardware configuration
#define CAR_NUM_MOTORS (4)
#define CAR_NUM_USS    (2)

// Settings for the various Operation modes of the car.
#define OPMODE_IDLE_MAXSPEED          (0u)
#define OPMODE_AUTODRIVE_MAXSPEED     (200u)
#define OPMODE_MANUDRIVE_MAXSPEED     (400u)
#define OPMODE_EMERGENCYSTOP_MAXSPEED (0u)

//camera ip
#define VCIPPart1 10
#define VCIPPart2 10
#define VCIPPart3 100
#define VCIPPart4 110

/* ===================================================================
 * Enums
 * ==================================================================*/
enum OpMode {
	OPMODE_PREOPERATIONAL,
	OPMODE_IDLE,
	OPMODE_AUTODRIVE,
	OPMODE_MANUDRIVE,
	OPMODE_EMERGENCYSTOP,
};

/* ===================================================================
 * Struct definitions
 * ==================================================================*/
/* -------------------------------------------------------------------
 * Velocity
 * 
 * \brief contains wheel velocities in mm/s
 * ------------------------------------------------------------------*/
struct Velocity
{
	alt_16 iFrontLeft;
	alt_16 iRearLeft;
	alt_16 iFrontRight;
	alt_16 iRearRight;
};

/* -------------------------------------------------------------------
 * UsSensor_State
 * ------------------------------------------------------------------*/
struct UsSensor_State
{
	alt_u32 distance;
};

/* -------------------------------------------------------------------
 * MotorECU_State
 * ------------------------------------------------------------------*/
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

/* -------------------------------------------------------------------
 * CarState
 * ------------------------------------------------------------------*/
// TODO: arrays for the IP addresses, no? This is a bit ugly.
struct CarState {
	alt_u32 counterCarControl;
	alt_u32 counterComm;
	alt_32 iMaxSpeed;
	alt_u8 ip1;
	alt_u8 ip2;
	alt_u8 ip3;
	alt_u8 ip4;
	alt_u8 reqip1;
	alt_u8 reqip2;
	alt_u8 reqip3;
	alt_u8 reqip4;
	enum OpMode currMode;
	enum OpMode reqMode;
	struct MotorECU_State motorEcus[CAR_NUM_MOTORS];
	struct UsSensor_State usSensors[CAR_NUM_USS];
	struct Velocity reqVelocity;
};

#endif /* CARSTATE_H_ */
