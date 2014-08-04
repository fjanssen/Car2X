#include "CVelocityMessage.h"
CVelocityMessage::CVelocityMessage()
{

}

CVelocityMessage::CVelocityMessage(alt_u8* pMessage, int iLength)
{
	parseHeader(pMessage, iLength);
}

CVelocityMessage::~CVelocityMessage()
{

}

void CVelocityMessage::answerMessage(bool executed_b)
{

}

void CVelocityMessage::doAction()
{

}

bool CVelocityMessage::getBytes(alt_u8* pMessage)
{
	return true;
}

alt_u32 CVelocityMessage::getLength()
{
	return 0;
}

void CVelocityMessage::parseMessage(alt_u8 *pMessage, int iLength)
{

}
