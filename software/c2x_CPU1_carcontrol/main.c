/*
 * main.cpp
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

#include "main.h"
#include "alt_types.h"

#include "MEM_Api.h"
#include "COMM_Api.h"
#include "ERR_Api.h"

int main(int argc, char* argv[])
{
	struct CarState state;

	alt_32 speed, iMaxAllowedSpeedFront, iMaxAllowedSpeedBack = 0;
	alt_32 iTotalSpeed, iLeftPercent, iRightPercent;
	alt_32 iCurrentMaxSpeed;

	struct MotorSpeedMsg motorSpeeds_ast[MEM_BUFFERLEN_MOTORSPEED];
	struct CarCommandMsg carCommands_ast[MEM_BUFFERLEN_CARCOMMAND];
	struct C2XMsg c2xRx_ast[MEM_BUFFERLEN_C2XRX];
	struct USSensorMsg usSensors_ast[MEM_BUFFERLEN_USSENSOR];

	alt_u32 numMotorSpeedMsgs_u32, numCarCommandMsgs_u32, numC2xRxMsgs_u32, numUsSensorMsgs_u32;
	alt_u8 motorSpeedsFlags_u8, carCommandsFlags_u8, c2xRxFlags_u8, usSensorFlags_u8;

	iCurrentMaxSpeed = iTotalSpeed = 0;
	iLeftPercent = iRightPercent = 100;

	while(1)
	{	
		// Get all received messages from the shared memory
		MEM_GetMemCopy(MEM_AREA_MOTORSPEED, motorSpeeds_ast, &numMotorSpeedMsgs_u32, &motorSpeedsFlags_u8);
		MEM_GetMemCopy(MEM_AREA_CARCOMMAND, carCommands_ast, &numCarCommandMsgs_u32, &carCommandsFlags_u8);
		MEM_GetMemCopy(MEM_AREA_C2XRX,      c2xRx_ast,       &numC2xRxMsgs_u32,      &c2xRxFlags_u8);
		MEM_GetMemCopy(MEM_AREA_USSENSOR,   usSensors_ast,   &numUsSensorMsgs_u32,   &usSensorFlags_u8);

		setCarState(&state);

		// Calculate current speed:
		speed = state.motorStates[0].iCurrentSpeed + state.motorStates[1].iCurrentSpeed + state.motorStates[2].iCurrentSpeed + state.motorStates[3].iCurrentSpeed;
		speed = speed / 4;

		iCurrentMaxSpeed = state.iMaxSpeed;

		// Print current state:
		printf("\rSpeed: %+5d mm/s,  Left: %+3d %%,  Right: %+3d %%,  ", speed, iLeftPercent, iRightPercent);
	
		// Frontal distance:
		ultrasoundHelp = (CUltrasoundSensorState*) state.motorStates[3].p_sensors[0];
		if(ultrasoundHelp != 0 && ultrasoundHelp->isDistanceValid())
		{
			printf("Front: %5hu mm,  ", ultrasoundHelp->getDistance());

			if(ultrasoundHelp->getDistance() < 300)
			{
				iMaxAllowedSpeedFront = 0;
				iLeftPercent = 100;
				iRightPercent = -100;
				iTotalSpeed = 150;
			}
			else
			{
				iMaxAllowedSpeedFront = (ultrasoundHelp->getDistance() * 5) / 10;
				iTotalSpeed = 200;
				iLeftPercent = 100;
				iRightPercent = 100;
			}
		}
		else
		{
			printf("Front: no dist.,  ");
			iMaxAllowedSpeedFront = state.iMaxSpeed;
		}
	
		// Backwards distance
		ultrasoundHelp = (CUltrasoundSensorState*) state.motorStates[1].p_sensors[0];
		if(ultrasoundHelp != 0 && ultrasoundHelp->isDistanceValid())
		{
			printf("Back: %5hu mm,  ", ultrasoundHelp->getDistance());

			if(ultrasoundHelp->getDistance() < 300)
			{
				iMaxAllowedSpeedBack = 0;
				iLeftPercent = 100;
				iRightPercent = -100;
				iTotalSpeed = 150;
			}
			else 
			{
				iMaxAllowedSpeedBack = (ultrasoundHelp->getDistance() * 5) / 10;
				iTotalSpeed = 200;
				iLeftPercent = 100;
				iRightPercent = 100;
				}
		}
		else
		{
			printf("Back: no dist.,  ");
			iMaxAllowedSpeedBack = state.iMaxSpeed;
		}	

	
		if(iTotalSpeed > 0 && speed > iMaxAllowedSpeedBack)
			iTotalSpeed = iMaxAllowedSpeedBack;

		if(iTotalSpeed < 0 && (-1*speed) > iMaxAllowedSpeedFront)
			iTotalSpeed = -1*iMaxAllowedSpeedFront;


		// Update state:
		state.motorStates[0].iDesiredSpeed = (iLeftPercent * iTotalSpeed) / 100;
		state.motorStates[2].iDesiredSpeed = (iLeftPercent * iTotalSpeed) / 100;

		state.motorStates[1].iDesiredSpeed = (iRightPercent * iTotalSpeed) / 100;
		state.motorStates[3].iDesiredSpeed = (iRightPercent * iTotalSpeed) / 100;

		setCarState(&state);

		MEM_SetMem(MEM_MOTORSPEED, );

		usleep(30000);
	}
	

	return 0;
}


