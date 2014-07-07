/*
 * Documentation in header file!
 * CarMessage.cpp
 *
 *  Created on: 05.01.2014
 *      Author: Florian
 */

#include "CarProtocol.h"

CCarMessage::CCarMessage()
{
	m_bValid = false;

}

CCarMessage::CCarMessage(alt_u8 *pMessage, int iLength)
{
	m_bValid = false;
	parseHeader(pMessage, iLength);
}

CCarMessage::CCarMessage(alt_u8 uiType, alt_u8 uiLength, bool bResponse)
{
	setHeader(uiType, uiLength, bResponse);
}

CCarMessage::~CCarMessage()
{

}

void CCarMessage::doAction()
{
	// Do nothing!
}


bool CCarMessage::getBytes(alt_u8 *pMessage)
{
	pMessage[0] = m_uiType;
	pMessage[1] = getLength();
	pMessage[2] = m_uiSubType;
	pMessage[3] = m_uiFlags;

	return m_bValid;
}


alt_u32 CCarMessage::getLength()
{
	return 4;
}


alt_u8 CCarMessage::getType()
{
	return m_uiType;
}

alt_u8 CCarMessage::getSubType()
{
	return m_uiSubType;
}

bool CCarMessage::isValid()
{
	return m_bValid;
}

void CCarMessage::setHeader(alt_u8 uiType, alt_u8 uiLength, bool bResponse)
{
	m_uiType = uiType;
	m_uiLength = uiLength;
	m_uiSubType = 0;
	m_uiFlags = bResponse;

	m_bValid = true;
}

void CCarMessage::setHeader(alt_u8 uiType, alt_u8 uiLength, alt_u8 uiSubType, bool bResponse)
{
	m_uiType = uiType;
	m_uiLength = uiLength;
	m_uiSubType = uiSubType;
	m_uiFlags = bResponse;

	m_bValid = true;
}

void CCarMessage::parseHeader(alt_u8 *pMessage, int iLength)
{
	if(iLength < 3)
		return;

	m_uiType = pMessage[0];
	m_uiLength = pMessage[1];
	m_uiSubType = pMessage[2];
	m_uiFlags = pMessage[3];

	m_bValid = true;
}

alt_32 CCarMessage::writeHeaderToBuffer(alt_u8 *pMessage, int iLength)
{
	if(iLength < 4)
		return -1;

	pMessage[0] = m_uiType;
	pMessage[1] = m_uiLength;
	pMessage[2] = 0;
	pMessage[3] = m_uiFlags;

	return 4;
}

