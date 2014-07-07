/*
* Documentation in header file!
* CarIP.cpp
*
* Created on: 17.11.2013
* Author: Florian
*/

// Export interface
#include "CarProtocol.h"

// Import interface
#include <stdio.h>
#include <stdlib.h>

#include "../etc/utility.h"
//Message imports
#include "WelcomeMessage.h"
#include "MotorMeasurementMessage.h"
#include "MotorVelocityMessage.h"
#include "UltrasoundDistanceMessage.h"
#include "AccelerationValuesMessage.h"
#include "ADCInfoMessage.h"
#include "ADCValuesMessage.h"
//Car2X Message imports
#include "CVelocityMessage.h"
#include "CEmergencyBrakeMessage.h"
#include "CControlMessage.h"
#include "CInfoStateMessage.h"
#include "CInfoSensorMessage.h"
#include "CRemoteControlMessage.h"
//end of includes

CCarProtocol::CCarProtocol(alt_u8 *pPacket, int iLength)
{
m_bValid = false;
m_bThereIsMore = false;

parsePacket(pPacket, iLength);
}

CCarProtocol::CCarProtocol(alt_u16 uiPacketNumber, CCarMessage **pMessages, alt_u32 uiMessageCount)
{
m_uiPacketNumber = uiPacketNumber;

for(alt_u32 i = 0; i < uiMessageCount; i++)
{
m_pMessages[i] = pMessages[i];
}

m_uiMessageCount = uiMessageCount;

m_bValid = true;
m_bThereIsMore = false;
}

CCarProtocol::~CCarProtocol()
{
for(alt_u32 i = 0; i < m_uiMessageCount; i++)
{
if(m_pMessages[i] != 0)
delete(m_pMessages[i]);
m_pMessages[i] = 0;
}
}

/*
* Parsing method called by the constructors.
* Important note:
* >>>>>> You have to edit this method if there are new sensors / messages <<<<<
*
* Additional note:
* Even if there are more packets in the byte stream, only the first occurrence is used. All other
* packets will be ignored!
*
* pPacket: byte array containing the byte (network) representation of the packet.
* iLength: length of the byte stream.
*/
void CCarProtocol::parsePacket(alt_u8 *pPacket, int iLength)
{
alt_u16 uiStartIdx;	// Index of the 'C' (start of the packet) in byte array
// Will be increment to the current working point!
alt_u16 uiPayloadLength;	// Payload length as read out of the byte array
alt_u16 uiPayloadOffset;	// Current working point for parsing of the next message
// Will be increment along the message lengths!

// Check Minimum Length 8 (which is the packet-header)
if(iLength < 8)
return;

// Search for 'C' 'A' 'R' 'P'
for(uiStartIdx = 0; uiStartIdx < iLength; uiStartIdx++)
{
if(pPacket[uiStartIdx] == 'C' && pPacket[uiStartIdx+1] == 'A' && pPacket[uiStartIdx+2] == 'R' && pPacket[uiStartIdx+3] == 'P')
break;
}

// Enough space for the header?
if(uiStartIdx + 8 > iLength)
return;

// Here starts the parsing:
// Parse the payload-Length
uiPayloadLength = *((alt_u16*) (pPacket+uiStartIdx+6));
swapEndianess((alt_u8*) &uiPayloadLength, 2);

// Parse the PacketNumber
m_uiPacketNumber = *((alt_u16*) (pPacket+uiStartIdx+4));
swapEndianess((alt_u8*) &m_uiPacketNumber, 2);

// Set the initial member values
m_bValid = true;
m_uiMessageCount = 0;

// Is there a payload?
if(uiPayloadLength > 0)
{
// Enough space for the payload?
if(uiStartIdx+8+uiPayloadLength > iLength)
{
m_bThereIsMore = true;
m_bValid = false;
return;
}

// Increment uiStartIdx to the working point (the first message position)
uiStartIdx += 8;

// Initialize uiPayloadOffset to 0
uiPayloadOffset = 0;

// Do as long there are messages (payload bytes) left and the count of messages dont exceeds 8.
while(uiPayloadOffset < uiPayloadLength && m_uiMessageCount < 8)
{
// Parse the message type and switch along it
switch(pPacket[uiStartIdx + uiPayloadOffset])
{
// The following cases parse the message along there type in different classes.
// TODO: Add new message classes here!!!!!

// WelcomeMessage
case 0x01:
m_pMessages[m_uiMessageCount] = new CWelcomeMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 12;
m_uiMessageCount++;
break;

// MotorVelocity
case 0x04:
m_pMessages[m_uiMessageCount] = new CMotorVelocityMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 8;
m_uiMessageCount++;
break;

// MotorMeasurement
case 0x05:
m_pMessages[m_uiMessageCount] = new CMotorMeasurementMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 16;
m_uiMessageCount++;
break;

// Ultrasound-Sensor
case 0x08:
m_pMessages[m_uiMessageCount] = new CUltrasoundDistanceMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 8;
m_uiMessageCount++;
break;

// Acceleration-Sensor
case 0x09:
m_pMessages[m_uiMessageCount] = new CAccelerationValuesMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 12;
m_uiMessageCount++;
break;

// ADC-Sensor
case 0x0A:
// If subtype is 0 then it's a InfoMessage otherwise a ValuesMessage
if(pPacket[uiStartIdx + uiPayloadOffset+2] == 0)
m_pMessages[m_uiMessageCount] = new CADCInfoMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
else
m_pMessages[m_uiMessageCount] = new CADCValuesMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);

// Make sure you add the right length to the offset!
uiPayloadOffset += m_pMessages[m_uiMessageCount]->getLength();
m_uiMessageCount++;
break;

// Velocity msg (incoming)-->other car tells us his velocity
case 0x10: // TODO
{
m_pMessages[m_uiMessageCount] = new CVelocityMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 12;
m_uiMessageCount++;
break;
}
	
//do emergency braking
case C2X_MSGID_EMERGENCY_BRAKE:
{
m_pMessages[m_uiMessageCount] = new CEmergencyBrakeMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 12;
m_uiMessageCount++;
break;
}

//set motor speeds from external source
case C2X_MSGID_CONTROL: // remote control/autonomous driving mode TODO: implement control function somewhere
{
m_pMessages[m_uiMessageCount] = new CControlMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 12;
m_uiMessageCount++;
break;
}

//tell our state
case C2X_MSGID_INFO_STATE:
{
m_pMessages[m_uiMessageCount] = new CInfoStateMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 12;
m_uiMessageCount++;
break;
}

//tell our sensor data
case C2X_MSGID_INFO_SENSORS:
{
m_pMessages[m_uiMessageCount] = new CInfoSensorMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 12;
m_uiMessageCount++;
break;
}

//set external source as controlling unit
case C2X_MSGID_REMOTE_CONTROL:
{
m_pMessages[m_uiMessageCount] = new CRemoteControlMessage(pPacket+uiStartIdx+uiPayloadOffset, uiPayloadLength-uiPayloadOffset);
uiPayloadOffset += 12;
m_uiMessageCount++;
break;
}

// Message ID is not known, so we also don't know the length of this message.
// We can't parse further, as we don't know the starting point of the next message.
// Set m_bValid false and return immediate!
default:
m_bValid = false;
return;
}
}
}

}

bool CCarProtocol::isValid()
{
return m_bValid;
}

bool CCarProtocol::getBytes(alt_u8 *pPacket)
{
alt_u16 uiLength = (alt_u16) getLength();
alt_u16 uiOffset = 8;

if(!m_bValid)
return m_bValid;

pPacket[0] = 'C'; pPacket[1] = 'A'; pPacket[2] = 'R'; pPacket[3] = 'P';

*((alt_u16*) (pPacket+4)) = m_uiPacketNumber;
swapEndianess(pPacket+4, 2);

*((alt_u16*) (pPacket+6)) = uiLength-8;
swapEndianess(pPacket+6, 2);

for(alt_u32 i = 0; i < m_uiMessageCount; i++)
{
m_bValid &= m_pMessages[i]->getBytes(pPacket+uiOffset);
uiOffset += m_pMessages[i]->getLength();
}

return m_bValid;
}


alt_u32 CCarProtocol::getLength()
{
alt_u32 uiLength = 8;

for(alt_u32 i = 0; i < m_uiMessageCount; i++)
{
uiLength += m_pMessages[i]->getLength();
}

return uiLength;
}


CCarMessage *CCarProtocol::getNthMessage(alt_u32 uiIdx)
{
if(uiIdx >= m_uiMessageCount)
return 0;

return m_pMessages[uiIdx];
}


alt_u32 CCarProtocol::getMessageCount()
{
return m_uiMessageCount;
}