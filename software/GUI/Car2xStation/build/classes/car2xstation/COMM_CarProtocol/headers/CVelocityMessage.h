/*
* CVelocityMessage.h
*
* Created on: 06.01.2014
* Author: Florian
*/

#ifndef CREMOTECONTROLMESSAGE_H_
#define CREMOTECONTROLMESSAGE_H_
//struct for GUI:0x10060000XXXX
#include "CarMessage.h"

class CVelocityMessage: public CCarMessage {
public:
CVelocityMessage();
CVelocityMessage(alt_u8* pMessage, int iLength);
virtual ~CVelocityMessage();
void answerMessage(bool executed_b);
void doAction();
bool getBytes(alt_u8* pMessage);
alt_u32 getLength();

alt_16 get_extVelocity()
{
return m_extVelocity;	
}


private:
alt_16 m_extVelocity;
alt_u8	m_uiReserved;

void parseMessage(alt_u8 *pMessage, int iLength);
};

#endif /* CREMOTECONTROLMESSAGE_H_ */