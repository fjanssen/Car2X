/*
 * CControlMessage.h
 *
 * Created on: 06.01.2014
 * Author: Florian
 */

#ifndef CCONTROLMESSAGE_H_
#define CCONTROLMESSAGE_H_
//struct for GUI:0x30120000XXXXXXXX
#include "CarMessage.h"
#include <alt_types.h>

class CControlMessage: public CCarMessage {
public:
	CControlMessage();
	CControlMessage(alt_u8 * pMessage, int iLength);
	virtual ~CControlMessage();
	void answerMessage(bool executed_b);
	void doAction();
	bool getBytes(alt_u8* pMessage);
	alt_u32 getLength();

	alt_16 get_siVelFrontRight() { return m_siVelFrontRight; }
	alt_16 get_siVelFrontLeft()  { return m_siVelFrontLeft; }
	alt_16 get_siVelRearRight()  { return m_siVelRearRight; }
	alt_16 get_siVelRearLeft()   { return m_siVelRearLeft; }

private:
	alt_16 m_siVelFrontLeft;
	alt_16 m_siVelFrontRight;
	alt_16 m_siVelRearLeft;
	alt_16 m_siVelRearRight;

	void parseMessage(alt_u8 *pMessage, int iLength);
};

#endif /* CCONTROLMESSAGE_H_ */
