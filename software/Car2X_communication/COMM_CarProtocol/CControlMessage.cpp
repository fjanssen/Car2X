#include "CControlMessage.h"

CControlMessage::CControlMessage()
{

}

CControlMessage::CControlMessage(alt_u8 * pMessage, int iLength)
{
	parseMessage(pMessage, iLength);
}

CControlMessage::~CControlMessage()
{

}

void CControlMessage::answerMessage(bool executed_b)
{

}

void CControlMessage::doAction()
{

}

bool CControlMessage::getBytes(alt_u8* pMessage)
{
	return true;
}

alt_u32 CControlMessage::getLength()
{
	return 0;
}


void CControlMessage::parseMessage(alt_u8 *pMessage, int iLength)
{
	m_siVelFrontRight = pMessage[0];
	m_siVelFrontLeft  = pMessage[1];
	m_siVelRearRight  = pMessage[2];
	m_siVelRearLeft   = pMessage[3];
}
