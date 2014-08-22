/*
 * Documentation in header file!
 * main.cpp
 *
 *  (Re-)Created on: 05.01.2014
 *      Author: Florian
 */

// Export interface
#include "main.h"
#include "ErrHandler.h"

int main (void)
{
	bool ret;
	alt_u16 state = 0; // State to distinguish between the small cycles
	CCarMessage *pCurrentMessage = 0; // The current message

	LOG_DEBUG("init");
	if(!init())
	{
		goto fail;
	}

	*pLED = 0xAA;

	LOG_DEBUG("wait");
	ret = sendWelcome();
	if(!ret) {
		goto fail;
	}
	*pLED = 0;

	LOG_DEBUG("setuppid");
	ret = setUpPIController();
	if(!ret)
	{
		goto fail;
	}

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
	LOG_DEBUG("measure");
	measureSpeedUnblocking();

	// Small cycle:
	while(true)
	{
		printf(".");
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
	LOG_DEBUG("fail");
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

bool sendWelcome()
{
	LOG_DEBUG("wait entry");
	delay(200);

	CCarMessage * pMessage = 0;
	alt_u32 uiTries = 0;         // Counts the tries, if >= 5 return
	alt_u8 cBuffer[128];         // Standard byte buffer
	alt_u32 uiReceivedCount = 0; // Count of received bytes (further: iLength)
	CWelcomeMessage * wMsg;
	bool success;

	// Prepare welcome message
	LOG_DEBUG("allocate msg");
	delay(200);

	// set led on
	*pLED |= 0x01;

	LOG_DEBUG("pre while");
	delay(200);

	while(true)
	{
		LOG_DEBUG("loop %d",  (int) uiTries);
		LOG_DEBUG("Gen proto");
		
		// Put the WelcomeMessage into the protocol wrapper.
		if(pProtocol) delete(pProtocol);
		wMsg = new CWelcomeMessage(FIRMWARE_VERSION, COMPONENT_TYPE, COMPONENT_ID, uiAvailableOperations);
		pProtocol = new CCarProtocol(0, (CCarMessage **) &wMsg, 1);
		pProtocol->getBytes(cBuffer);

		LOG_DEBUG("cBuffer: '%c%c%c%c' 0x%02X%02X%02X%02X 0x%02X%02X%02X%02X", cBuffer[0], cBuffer[1],
				cBuffer[2], cBuffer[3], cBuffer[4], cBuffer[5], cBuffer[6], cBuffer[7],
				cBuffer[8], cBuffer[9], cBuffer[10], cBuffer[11]);

		// Send out the packet.
		if(uiTries % 100 == 0)
		{
			success = pSocket->Send(cBuffer, pProtocol->getLength());
		}
		LOG_DEBUG("sent? %x", success);

		// Receive bytes from socket (timed blocking)
		uiReceivedCount = pSocket->Receive(cBuffer, 128, 10);
		if(uiReceivedCount <= 0)
		{
			LOG_DEBUG("incomplete packet");
			delay(200);
			uiTries++;
			continue; // If nothing was received
		}
		
		// Is there a current protocol, delete it and generate a new one out of received data
		if(pProtocol) delete(pProtocol);
		pProtocol = new CCarProtocol(cBuffer, uiReceivedCount);

		// Was the protocol generation unsuccessful then count one more try and continue
		if(pProtocol == 0 || !pProtocol->isValid() || pProtocol->getMessageCount() < 1)
		{
			printf("invalid packet\n");
			delay(200);
			uiTries++;
			continue;
		}

		// Check if the first message was a WelcomeMessage then break
		pMessage = pProtocol->getNthMessage(0);
		if(pMessage->isValid() && pMessage->getType() == 0x01)
		{
			LOG_DEBUG("valid message");
			delay(200);
			*pLED &= 0xFE;
			if(pProtocol) delete(pProtocol);
			return true;
		}
		uiTries++;

	}


	return false;
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

		LOG_DEBUG("cBuffer: '%c%c%c%c' 0x%0X%0X%0X%0X 0x%0X%0X%0X%0X", cBuffer[0], cBuffer[1],
				cBuffer[2], cBuffer[3], cBuffer[4], cBuffer[5], cBuffer[6], cBuffer[7],
				cBuffer[8], cBuffer[9], cBuffer[10], cBuffer[11]);

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

	pProtocol->getBytes(cBuffer);
	pSocket->Send(cBuffer, pProtocol->getLength());

	if(pProtocol) delete(pProtocol);

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
