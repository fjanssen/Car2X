/*
 * main.cpp
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

#include "main.h"


extern "C" {
    #include <pthread.h>
}

alt_32 iTotalSpeed, iLeftPercent, iRightPercent;
alt_32 iCurrentMaxSpeed;



void doSomething(void* data)
{
	/*
	char* cRequest = (char*) data;
	char cBuffer[256];

	char* idxSpeed = strstr(cRequest, "speed=");
	char* idxLeft = strstr(cRequest, "left=");
	char* idxRight = strstr(cRequest, "right=");

	iTotalSpeed = (atoi(idxSpeed+6) * iCurrentMaxSpeed) / 100;
	iLeftPercent = atoi(idxLeft+5);
	iRightPercent = atoi(idxRight+6);
*/
		
	
}

int main(int argc, char* argv[])
{
	pthread_t  threadHandle;

	Car_State state;
	alt_32 speed, iMaxAllowedSpeedFront, iMaxAllowedSpeedBack = 0;
	CUltrasoundSensorState* ultrasoundHelp;

	iCurrentMaxSpeed = iTotalSpeed = 0;
	iLeftPercent = iRightPercent = 100;

	startConnection();

	//setUpServer(50000, doSomething);
	// Create the thread which controlls the HTTPServer
	//threadHandle = pthread_create(&threadHandle,0,&openServer,0);
	

	while(true)
	{	
		// Get current state:
		getState(&state);

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
		getState(&state);
		state.motorStates[0].iDesiredSpeed = (iLeftPercent * iTotalSpeed) / 100;
		state.motorStates[2].iDesiredSpeed = (iLeftPercent * iTotalSpeed) / 100;

		state.motorStates[1].iDesiredSpeed = (iRightPercent * iTotalSpeed) / 100;
		state.motorStates[3].iDesiredSpeed = (iRightPercent * iTotalSpeed) / 100;

		setState(&state);	

		usleep(30000);
	}
	

	return 0;
}


