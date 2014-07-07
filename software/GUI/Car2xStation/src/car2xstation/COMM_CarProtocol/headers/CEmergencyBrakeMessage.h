/*
* CEmergencyBrakeMessage.h
*
* Created on: 06.01.2014
* Author: Florian
*/

#ifndef CEMERGENCYBRAKEMESSAGE_H_
#define CEMERGENCYBRAKEMESSAGE_H_
//struct for GUI:0x20040000
#include "CarMessage.h"

class CEmergencyBrakeMessage: public CCarMessage {
public:
CEmergencyBrakeMessage();
CEmergencyBrakeMessage(alt_u8* pMessage, int iLength);
virtual ~CEmergencyBrakeMessage();
void answerMessage(bool executed_b);
void doAction();
bool getBytes(alt_u8* pMessage);
alt_u32 getLength();


private:
alt_u8	m_uiReserved;

void parseMessage(alt_u8 *pMessage, int iLength);


};

#endif /* CEMERGENCYBRAKEMESSAGE_H_ */