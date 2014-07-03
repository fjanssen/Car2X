/*
* CControlMessage.h
*
* Created on: 06.01.2014
* Author: Florian
*/

#ifndef CCONTROLMESSAGE_H_
#define CCONTROLMESSAGE_H_
//struct for GUI:0x30080000XXXXXXXX
#include "CarMessage.h"

class CControlMessage: public CCarMessage {
public:
CControlMessage();
CControlMessage(alt_u8* pMessage, int iLength);
virtual ~CControlMessage();
void answerMessage(bool executed_b);
void doAction();
bool getBytes(alt_u8* pMessage);
alt_u32 getLength();

alt_16 get_iVelocity()
{
return m_siVelocity;
}

alt_16 get_iSteeringAngle()
{
return m_siSteeringAngle;
}

private:
alt_16 m_siVelocity;
alt_16 m_siSteeringAngle;
alt_u8	m_uiReserved;

void parseMessage(alt_u8 *pMessage, int iLength);
};

#endif /* CCONTROLMESSAGE_H_ */