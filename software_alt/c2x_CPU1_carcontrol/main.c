/*
 * main.cpp
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */


/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "main.h"
#include "alt_types.h"
#include "MEM_Api.h"
#include "COMM_Api.h"
#include "ERR_Api.h"

/******************************************************************************
 * DEFINES
 *****************************************************************************/
#define CAR_NUMMOTORS (4u)

/******************************************************************************
 * FUNCTION IMPLEMENTATION
 *****************************************************************************/
int main(int argc, char* argv[])
{
	/* --- local variables --- */
	// Car message buffers
	static struct MotorSpeedMsg motorSpeedMsg_ast[CAR_NUMMOTORS];

	static struct CarCommandMsg carCommandMsg_ast[MEM_BUFFERLEN_CARCOMMAND];
	static struct C2xMsg c2xRxMsg_ast[MEM_BUFFERLEN_C2XRX];
	static struct C2xMsg c2xTxMsg_ast[MEM_BUFFERLEN_C2XTX];
	static struct UsSensorMsg usSensorMsg_ast[MEM_BUFFERLEN_USSENSOR];

	// Buffer indices
	static alt_u32 motorSpeedMsgIndex_u32, carCommandMsgIndex_u32, c2xRxMsgIndex_u32, usSensorMsgIndex_u32;

	// variables for motor speed calculations
	alt_32 speed, iMaxAllowedSpeedFront, iMaxAllowedSpeedBack = 0;
	alt_32 iTotalSpeed, iLeftPercent, iRightPercent;
	alt_32 iCurrentMaxSpeed;

	/* --- function body --- */
	// Module initialisation
	MEM_ModuleInit();

	// Local variable initialisation
	iCurrentMaxSpeed = iTotalSpeed = 0;
	iLeftPercent = iRightPercent = 100;

	// Main function loop
	while(1)
	{	
		// Get all received messages from the shared memory
		MEM_GetLastMotorSpeeds(motorSpeedMsg_ast, CAR_NUMMOTORS);
		MEM_GetMemCopy(MEM_AREA_CARCOMMAND, &carCommandMsgIndex_u32, (void *)carCommandMsg_ast,  sizeof(carCommandMsg_ast));
		MEM_GetMemCopy(MEM_AREA_C2XRX,      &c2xRxMsgIndex_u32,      (void *)c2xRxMsg_ast,       sizeof(c2xRxMsg_ast));
		MEM_GetMemCopy(MEM_AREA_USSENSOR,   &usSensorMsgIndex_u32,   (void *)usSensorMsg_ast,    sizeof(usSensorMsg_ast));

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


