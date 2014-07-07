/*
 * MotorVelocityMessage.cpp
 *
 *  Created on: 06.01.2014
 *      Author: Florian
 */

#include "MotorVelocityMessage.h"

CMotorVelocityMessage::CMotorVelocityMessage(alt_16 iDesiredSpeed)
{
	setHeader(4, getLength(), 0);

 	m_iDesiredSpeed = iDesiredSpeed;
	m_iCurrentSpeed = 0;

	m_bValid = true;

}


CMotorVelocityMessage::CMotorVelocityMessage(alt_u8 *pMessage, int iLength)
{
	parseHeader(pMessage, iLength);
	if(m_bValid)
	{
		m_bValid = false;
		parseMessage(pMessage+4, iLength-4);
	}
}

CMotorVelocityMessage::~CMotorVelocityMessage()
{
}

void CMotorVelocityMessage::doAction()
{

}

bool CMotorVelocityMessage::getBytes(alt_u8 *pMessage)
{
	CCarMessage::getBytes(pMessage);

	*((alt_16*) (pMessage+4)) = m_iDesiredSpeed;
	swapEndianess(pMessage+4, 2);

	*((alt_16*) (pMessage+6)) = m_iCurrentSpeed;
	swapEndianess(pMessage+6, 2);

	return m_bValid;
}


alt_u32 CMotorVelocityMessage::getLength()
{
	return 8;
}

void CMotorVelocityMessage::parseMessage(alt_u8 *pMessage, int iLength)
{
	if(iLength < 4)
		return;

	m_iDesiredSpeed = *((alt_16*) (pMessage));
	swapEndianess((alt_u8*) &m_iDesiredSpeed, 2);

	m_iCurrentSpeed = *((alt_16*) (pMessage+2));
	swapEndianess((alt_u8*) &m_iCurrentSpeed, 2);

	m_bValid = true;
}

void CMotorVelocityMessage::answerMessage(alt_16 iCurrentSpeed)
{
	m_iCurrentSpeed = iCurrentSpeed;

	m_uiFlags = m_uiFlags | 0x01; // Response-Flag setzen
}
