/*
* CInfoStateMessage.h
*
* Created on: 06.01.2014
* Author: Florian
*/

#ifndef CINFOSTATEMESSAGE_H_
#define CINFOSTATEMESSAGE_H_
//struct for GUI:0x40040000
#include "CarMessage.h"

class CInfoStateMessage: public CCarMessage {
public:
CInfoStateMessage();
CInfoStateMessage(alt_u8* pMessage, int iLength);
virtual ~CInfoStateMessage();
void answerMessage(bool executed_b);
void doAction();
bool getBytes(alt_u8* pMessage);
alt_u32 getLength();


private:
alt_u8	m_uiReserved;

void parseMessage(alt_u8 *pMessage, int iLength);


};

#endif /* CINFOSTATEMESSAGE_H_ */