/*
 * MotorVelocityMessage.h
 *
 *  Created on: 06.01.2014
 *      Author: Florian
 */

#ifndef MOTORVELOCITYMESSAGE_H_
#define MOTORVELOCITYMESSAGE_H_

#include "../etc/utility.h"
#include "CarMessage.h"

class CMotorVelocityMessage: public CCarMessage {
public:
	CMotorVelocityMessage(alt_16 iDesiredSpeed);
	CMotorVelocityMessage(alt_u8* pMessage, int iLength);
	virtual ~CMotorVelocityMessage();
	void answerMessage(alt_16 iCurrentSpeed);
	void doAction();
	bool getBytes(alt_u8* pMessage);
	alt_u32 getLength();

	alt_16 getICurrentSpeed() const {
		return m_iCurrentSpeed;
	}

	alt_16 getIDesiredSpeed() const {
		return m_iDesiredSpeed;
	}

private:
	alt_16 m_iDesiredSpeed;
	alt_16 m_iCurrentSpeed;


	void parseMessage(alt_u8 *pMessage, int iLength);

};

#endif /* MOTORVELOCITYMESSAGE_H_ */
