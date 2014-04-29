/*
 * main.cpp
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

#include "CarAPI.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>


// Local variables:
Car_State *p_state;
int packetNumber;

// Thread
HANDLE  threadHandle;
DWORD   dwThreadId;

// Thread-Control
HANDLE threadStopMutex;
bool bStopThread;
HANDLE threadStateUpdateMutex;

// Local function:
DWORD WINAPI run(LPVOID lpParam);
void ErrorHandler(LPTSTR lpszFunction);

int sayWelcome();
int measure();

int generateRequest(char *cBuffers, int *p_iLengths);
int parseAnsweres(CCarProtocol **answeres);


bool startConnection()
{
	// Initialise variables
	p_state = NULL;
	bStopThread = false;
	packetNumber = 0;

	// Allocate State memory
	p_state = (Car_State*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(Car_State));

	// Init state
	memset(p_state, 0, sizeof(Car_State));

	// Allocate mutex
	threadStopMutex = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex

	threadStateUpdateMutex = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex

	// Create the thread which updates the state
	threadHandle = CreateThread( 
            NULL,           // default security attributes
            0,              // use default stack size  
            run,			// thread function name
            p_state,        // argument to thread function 
            0,				// use default creation flags 
            &dwThreadId);   // returns the thread identifier 

	if (threadHandle == NULL) 
    {
        ErrorHandler(TEXT("CreateThread"));
		return false;
    }
	return true;
}

bool stopConnection()
{
	// Set Stop-Request
	WaitForSingleObject( threadStopMutex, INFINITE);
		bStopThread = true;
	ReleaseMutex(threadStopMutex);

	// Wait for thread to be ended
	WaitForSingleObject(threadHandle, INFINITE);

	CloseHandle(threadHandle);
    if(p_state != NULL)
    {
        HeapFree(GetProcessHeap(), 0, p_state);
        p_state = NULL;    // Ensure address is not reused.
    }

	return true;
}

bool getState(Car_State *p_stateCopy)
{
	// Mutex for safe copy of state
	WaitForSingleObject( threadStateUpdateMutex, INFINITE);
		memcpy(p_stateCopy, p_state, sizeof(Car_State));
	ReleaseMutex(threadStateUpdateMutex);
	
	return true;
}

bool setState(Car_State *p_stateCopy)
{
	// Mutex for safe copy of state
	WaitForSingleObject( threadStateUpdateMutex, INFINITE);
		memcpy(p_state, p_stateCopy, sizeof(Car_State));
	ReleaseMutex(threadStateUpdateMutex);
	
	return true;
}



DWORD WINAPI run(LPVOID lpParam)
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
	p_state->iMaxSpeed = 0x7FFFFFFF;
	for(int i = 0; i < 4; i++)
	{
		if(p_state->motorStates[i].iMaxSpeed > 10 && p_state->iMaxSpeed > p_state->motorStates[i].iMaxSpeed)
			p_state->iMaxSpeed = p_state->motorStates[i].iMaxSpeed;
	}

	// Start state updating
	while(true)
	{
		// Check for Stop-Request
		WaitForSingleObject( threadStopMutex, INFINITE);
			if(bStopThread)
			{
				ReleaseMutex(threadStopMutex);

				closeConnections();
				return 0;
			}
		ReleaseMutex(threadStopMutex);


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

	WaitForSingleObject( threadStateUpdateMutex, INFINITE);

		for(int i = 0; i < 4; i++)
		{
			iMessageCount = 1;

			// Velocity Message:
			messages[0] = new CMotorVelocityMessage(p_state->motorStates[i].iDesiredSpeed);
			//p_state->motorStates[i].iDesiredSpeed++;

			for(int j = 0; j < p_state->motorStates[i].iSensorCount; j++)
			{
				messages[iMessageCount] = p_state->motorStates[i].p_sensors[j]->getCarMessage();
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

	ReleaseMutex(threadStateUpdateMutex);

	return 0;
}


int parseAnsweres(CCarProtocol **answeres)
{
	WaitForSingleObject( threadStateUpdateMutex, INFINITE);

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
					p_state->motorStates[i].iCurrentSpeed = ((CMotorVelocityMessage *) answeres[i]->getNthMessage(j))->getICurrentSpeed();	
					//printf("    %d    ", p_state->motorStates[i].iCurrentSpeed);
					continue;
				}

				// Check for a sensor number
				int sensorNumber = 0;
				for(; sensorNumber < p_state->motorStates[i].iSensorCount; sensorNumber++)
				{
					if(p_state->motorStates[i].uiOperations[sensorNumber] == answeres[i]->getNthMessage(j)->getType())
						break;
				}

				if(sensorNumber >= p_state->motorStates[i].iSensorCount)
					continue; // sensor could not be found!

				p_state->motorStates[i].p_sensors[sensorNumber]->updateSensorState(answeres[i]->getNthMessage(j));
			}
			//printf("\n");
		}

	ReleaseMutex(threadStateUpdateMutex);

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
			WaitForSingleObject( threadStateUpdateMutex, INFINITE);
				// Update state:
				p_state->motorStates[i].uiVersion = message->getUiVersionComponent();
				p_state->motorStates[i].uiType = message->getUiComponentType();
				p_state->motorStates[i].uiID = message->getUiComponentId();
				memcpy(&(p_state->motorStates[i].uiOperations), message->getUiOperations(), 4*sizeof(alt_u8));
				
				// Generate the sensor states:
				int sensorNumber = 0;
				for(; sensorNumber < 4; sensorNumber++)
				{
					if(p_state->motorStates[i].uiOperations[sensorNumber] != 0x00)
					{
						p_state->motorStates[i].iSensorCount++;
						switch(p_state->motorStates[i].uiOperations[sensorNumber])
						{
							case 0x08:
								p_state->motorStates[i].p_sensors[sensorNumber] = (CSensorState*) new CUltrasoundSensorState();
								break;
							case 0x09:
								p_state->motorStates[i].p_sensors[sensorNumber] = (CSensorState*) new CGSensorState();
								break;
							case 0x0A:
								p_state->motorStates[i].p_sensors[sensorNumber] = (CSensorState*) new CADCSensorState();
								break;
							default:
								p_state->motorStates[i].iSensorCount--;
								break;
						}
					}
				}

			ReleaseMutex(threadStateUpdateMutex);		
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
			WaitForSingleObject( threadStateUpdateMutex, INFINITE);
				// Update state:
				p_state->motorStates[i].iMaxSpeed = message->getIMaxSpeed();
				p_state->motorStates[i].uiWheelCircumference = message->getUiWheelCircumference();
				p_state->motorStates[i].iPType = message->getIPType();
				p_state->motorStates[i].iIType = message->getIIType();
				p_state->motorStates[i].iDType = message->getIDType();
			ReleaseMutex(threadStateUpdateMutex);					
		}
	}

	return 0;
}


void ErrorHandler(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code.

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message.

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR) lpMsgBuf) + lstrlen((LPCTSTR) lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR) lpDisplayBuf, TEXT("Error"), MB_OK); 

    // Free error-handling buffer allocations.

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

