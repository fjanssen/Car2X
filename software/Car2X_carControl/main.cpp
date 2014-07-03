/*
 * "Hello World" example.
 */

#include "MemController.h"
#include "ErrHandler.h"

using namespace c2x;


void switchState(CarState state);

void setMotorSpeeds(CarState state);


int main()
{
	MemController ctrl = MemController();

	CarState state;

	while(1)
	{
		// get the lastest car state from the shared memory
		state = ctrl.getLastElement<CarState>(MemController::AreaId_CarState);

		// print some diagnostics information
		int speed = state.motorEcus[0].iCurrentSpeed + state.motorEcus[1].iCurrentSpeed + state.motorEcus[2].iCurrentSpeed + state.motorEcus[3].iCurrentSpeed;

		printf("\rSpeed: %+5d mm/s, OpMode: %#x ", speed, state.currMode);
		printf("yippee!");

		// perform state switch if requested.
		if(state.reqMode != state.currMode)
		{
			switchState(state);
		}

		setMotorSpeeds(state);

		ctrl.pushElement(MemController::AreaId_CarState, state);

		// TODO: write a delay function w/ timer. Otherwise we might run into problems blocking the mutex from all the shared memory reads...
		// delay(10);
	}

	return -1;
}


void switchState(CarState state)
{
	LOG_DEBUG("Switching operating mode: %d -> %d", state.currMode, state.reqMode);

	switch(state.reqMode)
	{
	case OPMODE_IDLE:
	{
		state.iMaxSpeed = OPMODE_IDLE_MAXSPEED;
		break;
	}
	case OPMODE_EMERGENCYSTOP:
	{
		state.iMaxSpeed = OPMODE_EMERGENCYSTOP_MAXSPEED;
		break;
	}
	case OPMODE_AUTODRIVE:
	{
		state.iMaxSpeed = OPMODE_AUTODRIVE_MAXSPEED;
		break;
	}
	case OPMODE_MANUDRIVE:
	{
		state.iMaxSpeed = OPMODE_MANUDRIVE_MAXSPEED;
		break;
	}
	default:
	{
		LOG_ERROR(ERR_CARCTRL_INVALID_MODE, "Requested opMode: %d", state.reqMode);
		break;
	}
	}

	state.currMode = state.reqMode;
}


void setMotorSpeeds(CarState state)
{
	int iCurrVel, iReqVel;
	float fVelFactor;

	// Log current state:
	iCurrVel = (state.motorEcus[0].iCurrentSpeed
			+ state.motorEcus[1].iCurrentSpeed
			+ state.motorEcus[2].iCurrentSpeed
			+ state.motorEcus[3].iCurrentSpeed) / 4;

	LOG_DEBUG("Current velocity: %+5d, FL: %+3d, FR: %+3d, RL: %+3d, RR: %+3d",
			iCurrVel, state.motorEcus[0].iCurrentSpeed, state.motorEcus[1].iCurrentSpeed,
			state.motorEcus[2].iCurrentSpeed, state.motorEcus[3].iCurrentSpeed);

	// Calculate individual wheel speeds
	iReqVel = (state.reqVelocity.iFrontLeft
			+ state.reqVelocity.iFrontRight
			+ state.reqVelocity.iRearLeft
			+ state.reqVelocity.iRearRight) / 4;

	LOG_DEBUG("Request velocity: %+5d, FL: %+3d, FR: %+3d, RL: %+3d, RR: %+3d",
			iReqVel, state.reqVelocity.iFrontLeft, state.reqVelocity.iFrontRight,
			state.reqVelocity.iRearLeft, state.reqVelocity.iRearLeft);

	fVelFactor = abs(iReqVel) > abs(state.iMaxSpeed) ? (float) (state.iMaxSpeed) / (float) iReqVel : 1.0f;

	LOG_DEBUG("Request velocity too high. OpMode: %d, MaxVel: %d, VelFactor: %f",
			(int) state.currMode, (int) state.iMaxSpeed, fVelFactor);

	// Update state:
	state.motorEcus[0].iDesiredSpeed = (alt_16) (state.reqVelocity.iFrontLeft  * fVelFactor);
	state.motorEcus[1].iDesiredSpeed = (alt_16) (state.reqVelocity.iFrontRight * fVelFactor);
	state.motorEcus[2].iDesiredSpeed = (alt_16) (state.reqVelocity.iRearLeft   * fVelFactor);
	state.motorEcus[3].iDesiredSpeed = (alt_16) (state.reqVelocity.iRearLeft   * fVelFactor);

	// TODO: disregarding ultrasound sensor for now... sort out the many inclusions of comm stuff in CUltrasoundSensorState

	// Frontal distance:
	//	ultrasoundHelp = (CUltrasoundSensorState*) state.motorStates[3].p_sensors[0];
	//	if(ultrasoundHelp != 0 && ultrasoundHelp->isDistanceValid())
	//	{
	//		printf("Front: %5hu mm,  ", ultrasoundHelp->getDistance());
	//
	//		if(ultrasoundHelp->getDistance() < 300)
	//{
	//			iMaxAllowedSpeedFront = 0;
	//			iLeftPercent = 100;
	//			iRightPercent = -100;
	//			iTotalSpeed = 150;
	//}
	//		else
	//{
	//			iMaxAllowedSpeedFront = (ultrasoundHelp->getDistance() * 5) / 10;
	//			iTotalSpeed = 200;
	//			iLeftPercent = 100;
	//			iRightPercent = 100;
	//		}
	//	}
	//	else
	//	{
	//		printf("Front: no dist.,  ");
	//		iMaxAllowedSpeedFront = state.iMaxSpeed;
	//	}
	//
	//	// Backwards distance
	//	ultrasoundHelp = (CUltrasoundSensorState*) state.motorStates[1].p_sensors[0];
	//	if(ultrasoundHelp != 0 && ultrasoundHelp->isDistanceValid())
	//	{
	//		printf("Back: %5hu mm,  ", ultrasoundHelp->getDistance());
	//
	//		if(ultrasoundHelp->getDistance() < 300)
	//{
	//			iMaxAllowedSpeedBack = 0;
	//			iLeftPercent = 100;
	//			iRightPercent = -100;
	//			iTotalSpeed = 150;
	//}
	//		else
	//{
	//			iMaxAllowedSpeedBack = (ultrasoundHelp->getDistance() * 5) / 10;
	//			iTotalSpeed = 200;
	//			iLeftPercent = 100;
	//			iRightPercent = 100;
	//			}
	//	}
	//	else
	//	{
	//		printf("Back: no dist.,  ");
	//		iMaxAllowedSpeedBack = state.iMaxSpeed;
	//	}
}
