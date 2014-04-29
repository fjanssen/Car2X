/*
 * main.cpp
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

#include "main.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Car_State state;
	alt_32 speed, iTotalSpeed = 0, iMaxAllowedSpeedFront, iMaxAllowedSpeedBack;
	alt_32 iLeftPercent = 100;
	alt_32 iRightPercent = 100;

	CUltrasoundSensorState* ultrasoundHelp;

	startConnection();

	while(true)
	{
		// Get current state:
		getState(&state);

		// Calculate current speed:
		speed = state.motorStates[0].iCurrentSpeed + state.motorStates[1].iCurrentSpeed + state.motorStates[2].iCurrentSpeed + state.motorStates[3].iCurrentSpeed;
		speed = speed / 4;

		// Print current state:
		printf("\rSpeed: %+5d mm/s,  Left: %+3d %%,  Right: %+3d %%,  ", speed, iLeftPercent, iRightPercent);
		
		// Frontal distance:
		ultrasoundHelp = (CUltrasoundSensorState*) state.motorStates[3].p_sensors[0];
		if(ultrasoundHelp != 0 && ultrasoundHelp->isDistanceValid())
		{
			printf("Front: %5hu mm,  ", ultrasoundHelp->getDistance());

			if(ultrasoundHelp->getDistance() < 100)
				iMaxAllowedSpeedFront = 0;
			else
				iMaxAllowedSpeedFront = (ultrasoundHelp->getDistance() * 17) / 10;
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

			if(ultrasoundHelp->getDistance() < 100)
				iMaxAllowedSpeedBack = 0;
			else
				iMaxAllowedSpeedBack = (ultrasoundHelp->getDistance() * 17) / 10;
		}
		else
		{
			printf("Back: no dist.,  ");
			iMaxAllowedSpeedBack = state.iMaxSpeed;
		}


		// Get user request
		if(GetAsyncKeyState(VK_UP))
		{
			if(iTotalSpeed < state.iMaxSpeed)
				iTotalSpeed+=10;
		}
		else if(GetAsyncKeyState(VK_DOWN))
		{
			if(iTotalSpeed > -1 * state.iMaxSpeed)
				iTotalSpeed-=10;
		}
		else if(GetAsyncKeyState(VK_LEFT))
		{
			if(iLeftPercent > -100 && iLeftPercent <= 100 && iRightPercent == 100 )
				iLeftPercent -= 1;
			else if(iLeftPercent == 100 && iRightPercent < 100 )
				iRightPercent += 1;
		}
		else if(GetAsyncKeyState(VK_RIGHT))
		{
			if(iRightPercent > -100 && iRightPercent <= 100 && iLeftPercent == 100 )
				iRightPercent -= 1;
			else if(iRightPercent == 100 && iLeftPercent < 100 )
				iLeftPercent += 1;
		}
		else if(GetAsyncKeyState(VK_ESCAPE))
		{
			return 0;
		}
		else
		{
			if( iTotalSpeed > -3 && iTotalSpeed < 3)
				iTotalSpeed = 0;
			else if(iTotalSpeed < 0)
				iTotalSpeed+=3;
			else
				iTotalSpeed-=3;
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

		Sleep(30);
	}
	

	return 0;
}


