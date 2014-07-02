/*
 * CarState.h
 *
 *  Created on: Jun 19, 2014
 *      Author: wji
 */

#ifndef CARSTATE_H_
#define CARSTATE_H_


#include "alt_types.h"

#define CAR_NUM_MOTORS (4)
#define CAR_NUM_USS    (2)

namespace c2x {

enum OperatingMode {
	IDLE,
	AUTONOMOUS_DRIVE,
	REMOTE_DRIVE,
	EMERGENCY_STOP,
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
struct CarState {
	alt_u64 timeStamp;
	alt_32 iMaxSpeed;
	enum OperatingMode curMode;
	enum OperatingMode reqMode;
	struct MotorECU_State motorEcus[CAR_NUM_MOTORS];
	struct UsSensor_State usSensors[CAR_NUM_USS];
};


} /* namespace c2x */
#endif /* CARSTATE_H_ */
