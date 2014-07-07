/*
* CRemoteControlMessage.h
*
* Created on: 06.01.2014
* Author: Florian
*/

#ifndef CREMOTECONTROLMESSAGE_H_
#define CREMOTECONTROLMESSAGE_H_
//struct for GUI:0x60080000XXXXXXXX
#include "CarMessage.h"

class CRemoteControlMessage: public CCarMessage {
public:
CRemoteControlMessage();
CRemoteControlMessage(alt_u8* pMessage, int iLength);
virtual ~CRemoteControlMessage();
void answerMessage(bool executed_b);
void doAction();
bool getBytes(alt_u8* pMessage);
alt_u32 getLength();

//TODO: change to string representation of m_ip as return
alt_16 get_ip()
{
return m_ip;	//m_ip = "m_ipPart1"+"."+"alt_8 m_ipPart2"+...
}


private:
alt_8 m_ipPart1;
alt_8 m_ipPart2;
alt_8 m_ipPart3;
alt_8 m_ipPart4;
alt_u8	m_uiReserved;

void parseMessage(alt_u8 *pMessage, int iLength);
};

#endif /* CREMOTECONTROLMESSAGE_H_ */