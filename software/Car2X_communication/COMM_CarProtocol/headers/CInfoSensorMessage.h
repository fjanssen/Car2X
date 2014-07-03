/*
* CEInfoSensorMessage.h
*
* Created on: 06.01.2014
* Author: Florian
*/

#ifndef CINFOSENSORMESSAGE_H_
#define CINFOSENSORMESSAGE_H_
//struct for GUI:0x50040000
#include "CarMessage.h"

class CInfoSensorMessage: public CCarMessage {
public:
CInfoSensorMessage();
CInfoSensorMessage(alt_u8* pMessage, int iLength);
virtual ~CInfoSensorMessage();
void answerMessage(bool executed_b);
void doAction();
bool getBytes(alt_u8* pMessage);
alt_u32 getLength();


private:
alt_u8	m_uiReserved;

void parseMessage(alt_u8 *pMessage, int iLength);


};

#endif /* CINFOSENSORMESSAGE_H_ */