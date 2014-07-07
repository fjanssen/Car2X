/*
 * MotorMeasurementMessage.cpp
 *
 *  Created on: 06.01.2014
 *      Author: Florian
 */

#include "MotorMeasurementMessage.h"

CMotorMeasurementMessage::CMotorMeasurementMessage()
{
	setHeader(5, getLength(), 0);

 	m_iMaxSpeed = 0;
	m_uiWheelCircumference = 0;
	m_iPType = 0;
	m_iIType = 0;
	m_iDType = 0;
	m_uiCommand = 0;

	m_bValid = true;
}

CMotorMeasurementMessage::CMotorMeasurementMessage(alt_u8 *pMessage, int iLength)
{
	parseHeader(pMessage, iLength);
	if(m_bValid)
	{
		m_bValid = false;
		parseMessage(pMessage+4, iLength-4);
	}
}

CMotorMeasurementMessage::~CMotorMeasurementMessage()
{
}

void CMotorMeasurementMessage::doAction()
{

}

void CMotorMeasurementMessage::parseMessage(alt_u8 *pMessage, int iLength)
{
	if(iLength < 12)
		return;

	m_iMaxSpeed = *((alt_16*) (pMessage));
	swapEndianess((alt_u8*) &m_iMaxSpeed, 2);

	m_uiWheelCircumference = *((alt_16*) (pMessage+2));
	swapEndianess((alt_u8*) &m_uiWheelCircumference, 2);

	m_iPType = *((alt_16*) (pMessage+4));
	swapEndianess((alt_u8*) &m_iPType, 2);

	m_iIType = *((alt_16*) (pMessage+6));
	swapEndianess((alt_u8*) &m_iIType, 2);

	m_iDType = *((alt_16*) (pMessage+8));
	swapEndianess((alt_u8*) &m_iDType, 2);

	m_uiReserved = pMessage[10];
	m_uiCommand = pMessage[11];

	m_bValid = true;

}

bool CMotorMeasurementMessage::getBytes(alt_u8 *pMessage)
{
	CCarMessage::getBytes(pMessage);

	*((alt_16*) (pMessage+4)) = m_iMaxSpeed;
	swapEndianess(pMessage+4, 2);

	*((alt_16*) (pMessage+6)) = m_uiWheelCircumference;
	swapEndianess(pMessage+6, 2);

	*((alt_16*) (pMessage+8)) = m_iPType;
	swapEndianess(pMessage+8, 2);

	*((alt_16*) (pMessage+10)) = m_iIType;
	swapEndianess(pMessage+10, 2);

	*((alt_16*) (pMessage+12)) = m_iDType;
	swapEndianess(pMessage+12, 2);

	pMessage[14] = m_uiReserved;
	pMessage[15] = m_uiCommand;

	return m_bValid;
}


alt_u32 CMotorMeasurementMessage::getLength()
{
	return 16;
}


void CMotorMeasurementMessage::answerMessage(alt_16 iMaxSpeed, alt_u16 uiWheelCircumference, alt_16 iPType, alt_16 iIType, alt_16 iDType)
{
	m_iMaxSpeed = iMaxSpeed;

	m_uiWheelCircumference = uiWheelCircumference;

	m_iPType = iPType;

	m_iIType = iIType;

	m_iDType = iDType;

	m_uiFlags = m_uiFlags | 0x01; // Response-Flag setzen

}

