#include "CRemoteControlMessage.h"
CRemoteControlMessage::CRemoteControlMessage()
{

}

CRemoteControlMessage::CRemoteControlMessage(alt_u8* pMessage, int iLength)
{
    parseHeader(pMessage, iLength);
    if(m_bValid)
    {
        m_bValid = false;
        parseMessage(pMessage+4, iLength-4);
    }}

CRemoteControlMessage::~CRemoteControlMessage()
{

}

void CRemoteControlMessage::answerMessage(bool executed_b)
{

}

void CRemoteControlMessage::doAction()
{

}

bool CRemoteControlMessage::getBytes(alt_u8* pMessage)
{
	return true;
}

alt_u32 CRemoteControlMessage::getLength()
{
	return 0;
}

void CRemoteControlMessage::parseMessage(alt_u8 *pMessage, int iLength)
{
	m_bValid = true;
}
