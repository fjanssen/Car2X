#include "CInfoSensorMessage.h"
CInfoSensorMessage::CInfoSensorMessage()
{

}

CInfoSensorMessage::CInfoSensorMessage(alt_u8* pMessage, int iLength)
{
	parseHeader(pMessage, iLength);
}

CInfoSensorMessage::~CInfoSensorMessage()
{

}

void CInfoSensorMessage::answerMessage(bool executed_b)
{

}

void CInfoSensorMessage::doAction()
{

}

bool CInfoSensorMessage::getBytes(alt_u8* pMessage)
{
	return true;
}

alt_u32 CInfoSensorMessage::getLength()
{
	return 0;
}

void CInfoSensorMessage::parseMessage(alt_u8 *pMessage, int iLength)
{

}
