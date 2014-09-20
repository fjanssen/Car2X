/*
 * "Hello World" example.
 */

#include "MemController.h"
#include "ErrHandler.h"
#include <cstdlib>
#include <string.h>
#include "nios2.h";

void switchState(CarState * state);

void setMotorSpeeds(CarState * state);


int main()
{
	MemController<CarState> ctrl = MemController<CarState>();

	CarState state;

	//initial state:
	state = ctrl.getLastElement();
	memset(&state,0,sizeof(state));

	ctrl.pushElement(state);


	while(1)
	{
		for(int i=0;i<5000;i++){;}
		int nios;

		// get the lastest car state from the shared memory
		state = ctrl.getLastElement(true);

		// print some diagnostics information
		int speed = state.motorEcus[0].iCurrentSpeed + state.motorEcus[1].iCurrentSpeed + state.motorEcus[2].iCurrentSpeed + state.motorEcus[3].iCurrentSpeed;

		LOG_DEBUG("\rSpeed: %+5d mm/s, OpMode: %#x ", speed, state.currMode);
		//LOG_DEBUG("yippee!");

		// perform state switch if requested.
		if(state.reqMode != state.currMode)
		{
			switchState(&state);
		}
		state.counterCarControl=state.counterComm;

		setMotorSpeeds(&state);

		if(state.currMode==OPMODE_MANUDRIVE){
			state.ip1=state.reqip1;
			state.ip2=state.reqip2;
			state.ip3=state.reqip3;
			state.ip4=state.reqip4;
		}
		else{
			state.ip1=VCIPPart1;
			state.ip2=VCIPPart2;
			state.ip3=VCIPPart3;
			state.ip4=VCIPPart4;
		}
		ctrl.pushElement(state);

		// TODO: write a delay function w/ timer. Otherwise we might run into problems blocking the mutex from all the shared memory reads...
		//delay(10);
		for (int i = 0; i < 10000; i++) {;}
	}

	return -1;
}


void switchState(CarState * state)
{
	LOG_DEBUG("Switching operating mode: %d -> %d", state->currMode, state->reqMode);

	switch(state->reqMode)
	{
	case OPMODE_PREOPERATIONAL:
		{
			state->iMaxSpeed = OPMODE_IDLE_MAXSPEED;
			break;
		}
	case OPMODE_IDLE:
	{
		state->iMaxSpeed = OPMODE_IDLE_MAXSPEED;
		break;
	}
	case OPMODE_EMERGENCYSTOP:
	{
		state->iMaxSpeed = OPMODE_EMERGENCYSTOP_MAXSPEED;
		break;
	}
	case OPMODE_AUTODRIVE:
	{
		state->iMaxSpeed = OPMODE_AUTODRIVE_MAXSPEED;
		break;
	}
	case OPMODE_MANUDRIVE:
	{
		state->iMaxSpeed = OPMODE_MANUDRIVE_MAXSPEED;
		break;
	}
	default:
	{
		LOG_ERROR(ERR_CARCTRL_INVALID_MODE, "Requested opMode: %d", state->reqMode);
		break;
	}
	}

	state->currMode = state->reqMode;
}


void setMotorSpeeds(CarState * state)
{
	int iCurrVel, iReqVel;
	alt_u16 fVelFactor; // fixed comma integer, with resolution of 0.01

	// Log current state:
	iCurrVel = (state->motorEcus[0].iCurrentSpeed
			+ state->motorEcus[1].iCurrentSpeed
			+ state->motorEcus[2].iCurrentSpeed
			+ state->motorEcus[3].iCurrentSpeed) / 4;

	LOG_DEBUG("Current velocity: %+5d, LF: %+3hd, LR: %+3hd, RF: %+3hd, RR: %+3hd",
			iCurrVel, state->motorEcus[0].iCurrentSpeed, state->motorEcus[1].iCurrentSpeed,
			state->motorEcus[2].iCurrentSpeed, state->motorEcus[3].iCurrentSpeed);
	//LOG current PIController values
	LOG_DEBUG("LF: %hd, %hd, %hd LR: %hd, %hd, %hd RF: %hd, %hd, %hd RR: %hd, %hd, %hd",state->motorEcus[0].iIType,state->motorEcus[0].iPType,state->motorEcus[0].iMaxSpeed,state->motorEcus[1].iIType,state->motorEcus[1].iPType,state->motorEcus[1].iMaxSpeed,state->motorEcus[2].iIType,state->motorEcus[2].iPType,state->motorEcus[2].iMaxSpeed,state->motorEcus[3].iIType,state->motorEcus[3].iPType,state->motorEcus[3].iMaxSpeed);

	// Calculate individual wheel speeds
	iReqVel = (state->reqVelocity.iFrontLeft
			+ state->reqVelocity.iFrontRight
			+ state->reqVelocity.iRearLeft
			+ state->reqVelocity.iRearRight) / 4;

	LOG_DEBUG("Request velocity: %+5hd, LF: %+3hd, LR: %+3hd, RF: %+3hd, RR: %+3hd",
			iReqVel, state->reqVelocity.iFrontLeft, state->reqVelocity.iRearLeft,
			state->reqVelocity.iFrontRight, state->reqVelocity.iRearRight);

	if(abs(iReqVel) > abs(state->iMaxSpeed))
	{
		fVelFactor = state->iMaxSpeed * 100 / iReqVel;
		LOG_DEBUG("Request velocity too high. OpMode: %d, MaxVel: %d, VelFactor: %f",
			(int) state->currMode, (int) state->iMaxSpeed, fVelFactor);
	}
	else
	{
		fVelFactor = 100;
	}

	// Update state:
	state->motorEcus[0].iDesiredSpeed = (alt_16) (state->reqVelocity.iFrontLeft  * fVelFactor / 100);
	state->motorEcus[1].iDesiredSpeed = (alt_16) (state->reqVelocity.iRearLeft * fVelFactor / 100);
	state->motorEcus[2].iDesiredSpeed = (alt_16) (state->reqVelocity.iFrontRight   * fVelFactor / 100);
	state->motorEcus[3].iDesiredSpeed = (alt_16) (state->reqVelocity.iRearRight  * fVelFactor / 100);

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
