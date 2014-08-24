#include "CControlMessage.h"
#include "ErrHandler.h"

CControlMessage::CControlMessage()
{

}

CControlMessage::CControlMessage(alt_u8 * pMessage, int iLength)
{
    parseHeader(pMessage, iLength);
    if(m_bValid)
    {
        m_bValid = false;
        parseMessage(pMessage+4, iLength-4);
    }
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
	return 12;
}


void CControlMessage::parseMessage(alt_u8 *pMessage, int iLength)
{
	if(iLength < 8){
		return;
	}


	m_siVelFrontLeft  = *((alt_16*) (pMessage));
	swapEndianess((alt_u8*) &m_siVelFrontLeft, 2);
	m_siVelRearLeft   = *((alt_16*) (pMessage+2));
	swapEndianess((alt_u8*) &m_siVelRearLeft, 2);
	m_siVelFrontRight = *((alt_16*) (pMessage+4));
	swapEndianess((alt_u8*) &m_siVelFrontRight, 2);
	m_siVelRearRight  = *((alt_16*) (pMessage+6));
	swapEndianess((alt_u8*) &m_siVelRearRight, 2);

	m_bValid = true;
}
