/*
 * Documentation in header file!
 * main.cpp
 *
 *  (Re-)Created on: 05.01.2014
 *      Author: Florian
 */

// Export interface
#include "main.h"

int main (void)
{
	alt_u16 state = 0; // State to distinguish between the small cycles
	CCarMessage *pCurrentMessage = 0; // The current message

	if(!init())
		goto fail;

	*pLED = 0xAA;
	if(!waitForWelcome())
		goto fail;
	*pLED = 0;

	if(!setUpPIController())
		goto fail;

	// Restore speed = 0
	iDesiredSpeed = 0;
	iCurrentSpeed = 0;
	setSpeed(0);
	delay(1000);

	// Set timer and start it
	alt_u32 (*callback) (void*);
	callback = alarm_callback;
	alt_alarm_start(&alarm, 10, callback, 0);

	// Start first Speed Measurement
	measureSpeedUnblocking();

	// Small cycle:
	while(true)
	{
		if(!waitForEndOfCycle())
			goto fail;

		if(!controlSpeed())
			goto fail;

		if(state >= 9)
		{
			if(!waitForNextPacket())
				goto fail;
			state = 0;
		}
		else
		{
			// Get current message and call doAction()
			if(pProtocol != 0 && pProtocol->isValid() && state < pProtocol->getMessageCount())
			{
				alt_u32 count = pProtocol->getMessageCount();
				count = count - state - 1;
				pCurrentMessage = 0;
				pCurrentMessage = pProtocol->getNthMessage(count);
				if(pCurrentMessage != 0 && pCurrentMessage->isValid())
					pCurrentMessage->doAction();
			}
			state++;
		}
	}

// Label for failure
fail:
	setSpeed(0);
	*pLED = 0x80;
	delay(10000);
	return -1;
}



bool init()
{
	// Set speed to 0
	iDesiredSpeed = 0;
	iCurrentSpeed = 0;
	setSpeed(0);

	// Check LEDs
	*pLED = 0xFF;
	delay(1000);
	*pLED = 0x00;

	bCycleFinished = false;

	// Generate new socket object
	pSocket = new CEth_UART_Socket();

	// This function is always successful
	return true;
}

bool waitForWelcome()
{
	CCarMessage *pMessage = 0;   // Help reference
	alt_u32 uiTries = 0;         // Counts the tries, if >= 5 return
	alt_u8 cBuffer[128];         // Standard byte buffer
	alt_u32 uiReceivedCount = 0; // Count of received bytes (further: iLength)

	// Prepare welcome message
	CWelcomeMessage wMsg = CWelcomeMessage(FIRMWARE_VERSION, COMPONENT_TYPE, COMPONENT_ID, uiAvailableOperations);

	CCarMessage * pmsg = &wMsg; // needed for the CCarProtocol constructor.

	while (true) {
		if (uiTries > 5)
		{
			break;
		}

		// Is there a current protocol, delete it and generate a new one out of received data
		if(pProtocol) {
			delete(pProtocol);
		}
		// Put the WelcomeMessage into the protocol wrapper.
		pProtocol = new CCarProtocol(0, &pmsg, 1);
		pProtocol->getBytes(cBuffer);
		// Send out the packet.
		pSocket->Send(cBuffer, pProtocol->getLength());

		// Receive bytes from socket (timed blocking)
		uiReceivedCount = pSocket->Receive(cBuffer, 128, 10);
		if(uiReceivedCount <= 0)
			continue; // If nothing was received

		// Was the protocol generation unsuccessful then count one more try and continue
		if(pProtocol == 0 || !pProtocol->isValid() || pProtocol->getMessageCount() < 1)
		{
			uiTries++;
			continue;
		}

		// Check if the first message was a WelcomeMessage then break
		pMessage = pProtocol->getNthMessage(0);
		if(pMessage->isValid() && pMessage->getType() == 0x01)
			break;
	}

	if(uiTries > 5) {
		*pLED |= 0x01;
		return false;
	}
	else {
		*pLED &= 0xFE;
		return true;
	}
}

bool controlSpeed()
{
	alt_32 iNextSpeed = 0;

	// Finish running speed measurement
	iCurrentSpeed = measureSpeedUnblocking();
	// Call PI-Controller with speed error
	iNextSpeed = pController->control(iDesiredSpeed - iCurrentSpeed);
	// Set new speed
	setSpeed(iNextSpeed);

	// Is there a VelocityMessage then set the current speed as an answer
	if(pProtocol != 0 && pProtocol->isValid() && pProtocol->getMessageCount() > 0)
	{
		CCarMessage *pMessage = pProtocol->getNthMessage(0);
		if(pMessage != 0 && pMessage->isValid() && pMessage->getType() == 4)
		{
			((CMotorVelocityMessage*) pMessage)->answerMessage(iCurrentSpeed);
		}
	}

	return true;
}

bool waitForNextPacket()
{
	CCarProtocol *pNewProtocol = 0;
	CCarMessage *pMessage = 0;
	alt_u8 cBuffer[128];
	alt_u32 uiReceivedCount = 0;

	// Get new package
	uiReceivedCount = pSocket->ReceiveImmediate(cBuffer, 128);
	if(uiReceivedCount > 0)
	{
		*pLED = *pLED & 0xEF;

		pNewProtocol = new CCarProtocol(cBuffer, uiReceivedCount);

		// Is there a VelocityMessage then set the desired speed along with the message
		if(pNewProtocol != 0 && pNewProtocol->isValid() && pNewProtocol->getMessageCount() > 0)
		{
			pMessage = pNewProtocol->getNthMessage(0);
			if(pMessage != 0 && pMessage->isValid() && pMessage->getType() == 4)
			{
				iDesiredSpeed = ((CMotorVelocityMessage*) pMessage)->getIDesiredSpeed();
			}
		}
	}
	else
	{
		*pLED = *pLED | 0x10;
	}

	// Send answer of the last packet
	if(pProtocol != 0 && pProtocol->isValid())
	{
		if(!pProtocol->getBytes(cBuffer))
		{
			*pLED = *pLED | 0x02;
			return false;
		}
		pSocket->Send(cBuffer, pProtocol->getLength());
	}

	if(pNewProtocol != 0 && pNewProtocol->isValid() && pNewProtocol->getMessageCount() > 0)
	{
		// Delete old Packet
		if(pProtocol)
		{
			delete(pProtocol);
			pProtocol = 0;
		}

		pProtocol = pNewProtocol;
	}

	return true;
}

bool setUpPIController()
{
	CCarMessage *pMessage = 0;
	alt_u32 uiTries = 0;
	alt_u8 cBuffer[128];
	alt_u32 uiReceivedCount = 0;

	alt_32 uiT;

	// Stop
	iDesiredSpeed = 0;
	iCurrentSpeed = 0;

	setSpeed(0);
	delay (1000);

	// Full speed
	setSpeed(100000);
	// Measure speed at T1 (=10ns)
	uiT = measureSpeed();

	delay (10000);

	// Measure speed at Tk (=10020ns) which should be the VMax
	uiMaxSpeed = measureSpeed();
	setSpeed(0);

	// Calculate I Value, I = (100*T1) / (Tk+1), K = Tk
	uiT = (uiT * 100) / (uiMaxSpeed+1);

	// Reset the controller
	if(pController)
		delete(pController);
	pController = new CPIController(uiMaxSpeed, uiT, -1*uiMaxSpeed, uiMaxSpeed);

	// Get the MeasurementRequestMessage
	while(true)
	{
		if(uiTries >= 5)
		{
			*pLED = *pLED | 0x04;
			return false;
		}

		uiReceivedCount = pSocket->Receive(cBuffer, 128, 10);
		if(uiReceivedCount <= 0)
			continue;

		if(pProtocol)
			delete(pProtocol);
		pProtocol = new CCarProtocol(cBuffer, uiReceivedCount);
		if(pProtocol == 0 || !pProtocol->isValid() || pProtocol->getMessageCount() != 1)
		{
			uiTries++;
			continue;
		}

		pMessage = pProtocol->getNthMessage(0);
		if(pMessage->isValid() && pMessage->getType() == 0x05)
			break;
	}

	*pLED = *pLED & 0xFE;
	((CMotorMeasurementMessage*) pMessage)->answerMessage((alt_16) uiMaxSpeed, WHEEL_SCALE, (alt_16) uiMaxSpeed, (alt_16) uiT, 0);

	return true;
}

bool waitForEndOfCycle()
{
	while(!bCycleFinished)
	{
		*pLED = 0x08;
	}
	*pLED = *pLED & 0xF7;

	bCycleFinished = false;
	return true;
}
