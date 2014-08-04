#include "CInfoStateMessage.h"
CInfoStateMessage::CInfoStateMessage()
{

}

CInfoStateMessage::CInfoStateMessage(alt_u8* pMessage, int iLength)
{
	parseHeader(pMessage, iLength);
}

CInfoStateMessage::~CInfoStateMessage()
{

}

void CInfoStateMessage::answerMessage(bool executed_b)
{

}

void CInfoStateMessage::doAction()
{

}

bool CInfoStateMessage::getBytes(alt_u8* pMessage)
{
	return true;
}

alt_u32 CInfoStateMessage::getLength()
{
	return 0;
}

void CInfoStateMessage::parseMessage(alt_u8 *pMessage, int iLength)
{

}
