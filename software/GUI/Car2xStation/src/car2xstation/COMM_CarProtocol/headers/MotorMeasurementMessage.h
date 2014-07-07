/*
 * MotorMeasurementMessage.h
 *
 *  Created on: 06.01.2014
 *      Author: Florian
 */

#ifndef MOTORMEASUREMENTMESSAGE_H_
#define MOTORMEASUREMENTMESSAGE_H_

#include "CarMessage.h"

class CMotorMeasurementMessage: public CCarMessage {
public:
	CMotorMeasurementMessage();
	CMotorMeasurementMessage(alt_u8* pMessage, int iLength);
	virtual ~CMotorMeasurementMessage();
	void answerMessage(alt_16 iMaxSpeed, alt_u16 uiWheelCircumference,
			alt_16 iPType, alt_16 iIType, alt_16 iDType);
	void doAction();
	bool getBytes(alt_u8* pMessage);
	alt_u32 getLength();

	alt_16 getIDType() const {
		return m_iDType;
	}

	alt_16 getIIType() const {
		return m_iIType;
	}

	alt_16 getIMaxSpeed() const {
		return m_iMaxSpeed;
	}

	alt_16 getIPType() const {
		return m_iPType;
	}

	alt_u8 getUiCommand() const {
		return m_uiCommand;
	}

	alt_u16 getUiWheelCircumference() const {
		return m_uiWheelCircumference;
	}

private:
	alt_16 	m_iMaxSpeed;
	alt_u16	m_uiWheelCircumference;
	alt_16	m_iPType;
	alt_16	m_iIType;
	alt_16	m_iDType;
	alt_u8	m_uiReserved;
	alt_u8	m_uiCommand;

	void parseMessage(alt_u8 *pMessage, int iLength);


};

#endif /* MOTORMEASUREMENTMESSAGE_H_ */
