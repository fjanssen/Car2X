/*
 * main.cpp
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

// Export interface
#include "CarAPI.h"

// Import interface
#include <stdio.h>

#include "../networking/WelcomeMessage.h"
#include "../networking/MotorVelocityMessage.h"
#include "../networking/MotorMeasurementMessage.h"

#include "../sensors/UltrasoundSensor.h"
#include "../sensors/AccelerationSensor.h"
#include "../sensors/ADCSensor.h"


extern "C" {
    #include <pthread.h>
}


// Local variables:
Car_State state;
int packetNumber;

// Thread
pthread_t  threadHandle;
void* run(void* lpParam);

// Thread-Control
pthread_mutex_t threadStopMutex;
bool bStopThread;
pthread_mutex_t threadStateUpdateMutex;


// Local functions
int sayWelcome();
int measure();

int generateRequest(char *cBuffers, int *p_iLengths);
int parseAnsweres(CCarProtocol **answeres);


bool startConnection()
{
	// Initialise variables
	bStopThread = false;
	packetNumber = 0;

	// Init state
	memset(&state, 0, sizeof(Car_State));

	// Allocate mutex
	threadStopMutex = PTHREAD_MUTEX_INITIALIZER;
	threadStateUpdateMutex = PTHREAD_MUTEX_INITIALIZER;

	// Create the thread which updates the state
	threadHandle = pthread_create(&threadHandle,0,&run,0);

	if (threadHandle != 0) 
    {
        printf("Error: Can not create new thread.\n");
		return false;
    }
	return true;
}

bool stopConnection()
{
	// Set Stop-Request
	pthread_mutex_lock( &threadStopMutex );
		bStopThread = true;
	pthread_mutex_unlock( &threadStopMutex );

	// Wait for thread to be ended
	pthread_join(threadHandle, 0);

	return true;
}

bool getState(Car_State *p_stateCopy)
{
	// Mutex for safe copy of state
	pthread_mutex_lock( &threadStateUpdateMutex );
		memcpy(p_stateCopy, &state, sizeof(Car_State));
	pthread_mutex_unlock(&threadStateUpdateMutex);
	
	return true;
}

bool setState(Car_State *p_stateCopy)
{
	// Mutex for safe copy of state
	pthread_mutex_lock( &threadStateUpdateMutex );
		memcpy(&state, p_stateCopy, sizeof(Car_State));
	pthread_mutex_unlock(&threadStateUpdateMutex);
	
	return true;
}



void* run(void* lpParam)
{
	// Local function variables
	char cBuffers[4*128];
	alt_u32 iLengths[4] = {0,0,0,0};
	CCarProtocol *answeres[4];	

	// Init and open Connections
	initRemoteConnection();
	openConnections();

	sayWelcome();
	measure();

	// Check for the maximum speed
	state.iMaxSpeed = 0x7FFFFFFF;
	for(int i = 0; i < 4; i++)
	{
		if(state.motorStates[i].iMaxSpeed > 10 && state.iMaxSpeed > state.motorStates[i].iMaxSpeed)
			state.iMaxSpeed = state.motorStates[i].iMaxSpeed;
	}

	// Start state updating
	while(true)
	{
		// Check for Stop-Request
		pthread_mutex_lock( &threadStopMutex );
			if(bStopThread)
			{
				pthread_mutex_unlock(&threadStopMutex);

				closeConnections();
				return 0;
			}
		pthread_mutex_unlock(&threadStopMutex);


		// Generate next request and send it:
		generateRequest(cBuffers, (int*) iLengths);
		sendData(cBuffers, iLengths);
		packetNumber++;

		// Receive Answer
		receiveNextPackets(answeres);

		// ParseAnsweres
		parseAnsweres(answeres);

		// Cleanup Answeres
		for(int i = 0; i < 4; i++)
		{
			if(answeres[i])
			{
				delete(answeres[i]);
				answeres[i] = 0;
			}
		}

	}
}


int generateRequest(char *cBuffers, int *p_iLengths)
{
	CCarProtocol *protocol = 0;	
	CCarMessage *messages[8];
	int iMessageCount = 1;

	pthread_mutex_lock( &threadStateUpdateMutex );

		for(int i = 0; i < 4; i++)
		{
			iMessageCount = 1;

			// Velocity Message:
			messages[0] = new CMotorVelocityMessage(state.motorStates[i].iDesiredSpeed);
			//p_state->motorStates[i].iDesiredSpeed++;

			for(int j = 0; j < state.motorStates[i].iSensorCount; j++)
			{
				messages[iMessageCount] = state.motorStates[i].p_sensors[j]->getCarMessage();
				if(messages[iMessageCount] != 0)
					iMessageCount++;
			}

			// Generate new Protocol
			protocol = new CCarProtocol(packetNumber, messages, iMessageCount);

			// Generate byte data
			protocol->getBytes((alt_u8*) cBuffers+i*128);
			p_iLengths[i] = protocol->getLength();

			// Cleanup protocol
			delete(protocol);
		}

	pthread_mutex_unlock(&threadStateUpdateMutex);

	return 0;
}


int parseAnsweres(CCarProtocol **answeres)
{
	pthread_mutex_lock( &threadStateUpdateMutex );

		for(int i = 0; i < 4; i++)
		{
			// Check for valid answer
			if(answeres[i] == 0 || !answeres[i]->isValid())
				continue;

			// Parse the responses
			for(int j = 0; j < answeres[i]->getMessageCount(); j++)
			{
				// Is it a speed message?
				if(answeres[i]->getNthMessage(j)->getType() == 0x04)
				{
					state.motorStates[i].iCurrentSpeed = ((CMotorVelocityMessage *) answeres[i]->getNthMessage(j))->getICurrentSpeed();	
					//printf("    %d    ", p_state->motorStates[i].iCurrentSpeed);
					continue;
				}

				// Check for a sensor number
				int sensorNumber = 0;
				for(; sensorNumber < state.motorStates[i].iSensorCount; sensorNumber++)
				{
					if(state.motorStates[i].uiOperations[sensorNumber] == answeres[i]->getNthMessage(j)->getType())
						break;
				}

				if(sensorNumber >= state.motorStates[i].iSensorCount)
					continue; // sensor could not be found!

				state.motorStates[i].p_sensors[sensorNumber]->updateSensorState(answeres[i]->getNthMessage(j));
			}
			//printf("\n");
		}

	pthread_mutex_unlock(&threadStateUpdateMutex);

	return 0;
}

int sayWelcome()
{
	char cBuffers[4*128];
	alt_u32 iLengths[4];
	CCarProtocol *answeres[4];
	CCarMessage *messages[8];

	iLengths[0] = iLengths[1] = iLengths[2] = iLengths[3] = 0;
	CCarProtocol *protocol = 0;	

	CWelcomeMessage *message = new CWelcomeMessage(FIRMWARE_VERSION);
	messages[0] = message;
	protocol = new CCarProtocol(packetNumber++, messages, 1);

	for(int i = 0; i < 4; i++)
	{
		protocol->getBytes((alt_u8*) cBuffers+i*128);
		iLengths[i] = protocol->getLength();
	}

	sendData(cBuffers, iLengths);
	receiveDataExactCount(cBuffers, iLengths);
	delete(protocol);

	for(int i = 0; i < 4; i++)
	{
		answeres[i] = new CCarProtocol((alt_u8*) cBuffers+i*128, iLengths[i]);

		if(answeres[i] != 0 && answeres[i]->isValid() && answeres[i]->getMessageCount() == 1)
		{
			message = (CWelcomeMessage *) answeres[i]->getNthMessage(0);
			if(message->getType() != 0x01)
				continue;

			// Mutex for safe changeing of state-values
			pthread_mutex_lock( &threadStateUpdateMutex );
				// Update state:
				state.motorStates[i].uiVersion = message->getUiVersionComponent();
				state.motorStates[i].uiType = message->getUiComponentType();
				state.motorStates[i].uiID = message->getUiComponentId();
				memcpy(&(state.motorStates[i].uiOperations), message->getUiOperations(), 4*sizeof(alt_u8));
				
				// Generate the sensor states:
				int sensorNumber = 0;
				for(; sensorNumber < 4; sensorNumber++)
				{
					if(state.motorStates[i].uiOperations[sensorNumber] != 0x00)
					{
						state.motorStates[i].iSensorCount++;
						switch(state.motorStates[i].uiOperations[sensorNumber])
						{
							case 0x08:
								state.motorStates[i].p_sensors[sensorNumber] = (CSensorState*) new CUltrasoundSensor();
								break;
							case 0x09:
								state.motorStates[i].p_sensors[sensorNumber] = (CSensorState*) new CAccelerationSensor();
								break;
							case 0x0A:
								state.motorStates[i].p_sensors[sensorNumber] = (CSensorState*) new CADCSensor();
								break;
							default:
								state.motorStates[i].iSensorCount--;
								break;
						}
					}
				}

			pthread_mutex_unlock(&threadStateUpdateMutex);		
		}
	}
	return 0;
}


int measure()
{
	char cBuffers[4*128];
	alt_u32 iLengths[4];
	CCarProtocol *answeres[4];
	CCarMessage *messages[8];

	iLengths[0] = iLengths[1] = iLengths[2] = iLengths[3] = 0;
	CCarProtocol *protocol = 0;

	
	CMotorMeasurementMessage *message = new CMotorMeasurementMessage();
	messages[0] = message;
	protocol = new CCarProtocol(packetNumber++, messages, 1);

	for(int i = 0; i < 4; i++)
	{
		protocol->getBytes((alt_u8*) cBuffers+i*128);
		iLengths[i] = protocol->getLength();
	}
	sendData(cBuffers, iLengths);
	receiveDataExactCount(cBuffers, iLengths);
	delete(protocol);

	for(int i = 0; i < 4; i++)
	{
		answeres[i] = new CCarProtocol((alt_u8*) cBuffers+i*128, iLengths[i]);

		if(answeres[i] != 0 && answeres[i]->isValid() && answeres[i]->getMessageCount() == 1)
		{
			message = (CMotorMeasurementMessage *) answeres[i]->getNthMessage(0);
			if(message->getType() != 0x05)
				continue;

			// Mutex for safe changeing of state-values
			pthread_mutex_lock( &threadStateUpdateMutex );
				// Update state:
				state.motorStates[i].iMaxSpeed = message->getIMaxSpeed();
				state.motorStates[i].uiWheelCircumference = message->getUiWheelCircumference();
				state.motorStates[i].iPType = message->getIPType();
				state.motorStates[i].iIType = message->getIIType();
				state.motorStates[i].iDType = message->getIDType();
			pthread_mutex_unlock(&threadStateUpdateMutex);					
		}
	}

	return 0;
}
