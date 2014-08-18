#include "CEmergencyBrakeMessage.h"
CEmergencyBrakeMessage::CEmergencyBrakeMessage()
{

}

CEmergencyBrakeMessage::CEmergencyBrakeMessage(alt_u8* pMessage, int iLength)
{
	parseHeader(pMessage, iLength);
}

CEmergencyBrakeMessage::~CEmergencyBrakeMessage()
{

}

void CEmergencyBrakeMessage::answerMessage(bool executed_b)
{

}

void CEmergencyBrakeMessage::doAction()
{

}

bool CEmergencyBrakeMessage::getBytes(alt_u8* pMessage)
{
	return true;
}

alt_u32 CEmergencyBrakeMessage::getLength()
{
	return 0;
}

void CEmergencyBrakeMessage::parseMessage(alt_u8 *pMessage, int iLength)
{

}
