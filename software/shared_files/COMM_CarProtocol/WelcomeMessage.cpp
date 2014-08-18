/*
 * See header file for more comments.
 * WelcomeMessage.cpp
 *
 *  Created on: 05.01.2014
 *      Author: Florian
 */

#include "WelcomeMessage.h"

CWelcomeMessage::CWelcomeMessage(alt_u8 *pMessage, int iLength)
{
	parseHeader(pMessage, iLength);
	if(m_bValid)
	{
		m_bValid = false;
		parseMessage(pMessage+4, iLength-4);
	}
}

CWelcomeMessage::CWelcomeMessage(alt_u8 uiVersionComponent, alt_u8 uiComponentType, alt_u8 uiComponentID, alt_u8 *uiOperations)
{

	setHeader(1, getLength(), 0);

	m_uiVersionComponent = uiVersionComponent;
	m_uiComponentType = uiComponentType;
	m_uiComponentID = uiComponentID;

	for(alt_u32 i = 0; i < 4; i++)
		m_uiOperations[i] = uiOperations[i];

	m_bValid = true;
}

CWelcomeMessage::~CWelcomeMessage()
{

}

void CWelcomeMessage::doAction()
{
	// Do nothing!
}

bool CWelcomeMessage::getBytes(alt_u8 *pMessage)
{
	CCarMessage::getBytes(pMessage);

	pMessage[4] = m_uiVersionCentral;
	pMessage[5] = m_uiVersionComponent;
	pMessage[6] = m_uiComponentType;
	pMessage[7] = m_uiComponentID;

	for(alt_u32 i = 0; i < 4; i++)
		pMessage[i+8] = m_uiOperations[i];

	return m_bValid;
}


alt_u32 CWelcomeMessage::getLength()
{
	return 12;
}

void CWelcomeMessage::parseMessage(alt_u8 *pMessage, int iLength)
{
	if(iLength < 8)
		return;

	m_uiVersionCentral = pMessage[0];
	m_uiVersionComponent = pMessage[1];
	m_uiComponentType = pMessage[2];
	m_uiComponentID = pMessage[3];

	for(alt_u32 i = 0; i < 4; i++)
		m_uiOperations[i] = pMessage[i+4];

	m_bValid = true;
}

void CWelcomeMessage::answerMessage(alt_u8 uiVersionCentral)
{
	if(!m_bValid)
		return;

	m_uiVersionCentral = uiVersionCentral;
	m_uiVersionComponent = 0;
	m_uiComponentType = 0;
	m_uiComponentID = 0;

	for(alt_u32 i = 0; i < 4; i++)
		m_uiOperations[i] = 0;

	m_uiFlags = m_uiFlags | 0x01; // Set Response-Flag
}

