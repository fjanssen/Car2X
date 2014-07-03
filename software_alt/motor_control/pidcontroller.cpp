#include "pidcontroller.h"

CPIController::CPIController(alt_32 iPValue, alt_32 iIValue, alt_32 iMinimum, alt_32 iMaximum)
{
	m_iPValue = iPValue;
	m_iIValue = iIValue;

	m_iMinimum = iMinimum;
	m_iMaximum = iMaximum;

	m_iErrorSum = 0;
	m_iLastError = 0;
}


CPIController::~CPIController(void){}

alt_32 CPIController::control(alt_32 iError)
{
	alt_32 iResultP, iResultI, iResult;

	// Compute P Type:
	iResultP = iError / m_iPValue;

	// Compute I Type:
	m_iErrorSum += iError;
	iResultI = m_iErrorSum  / m_iIValue;
	m_iLastError = iError;

	// Complete Controller
	iResult = iResultP + iResultI;

	// Check for bounds
	if(iResult < m_iMinimum)
		iResult = m_iMinimum;
	else if(iResult > m_iMaximum)
		iResult = m_iMaximum;

	iResult  *= 100000;
	iResult  /= m_iMaximum;

	if(iResult < 10000 && iResult > -10000)
		iResult = 0;

	return iResult;
}

void CPIController::changeController(alt_32 iPValue, alt_32 iIValue)
{
	m_iPValue = iPValue;
	m_iIValue = iIValue;
}

void CPIController::getController(alt_32 *p_iPValue, alt_32 *p_iIValue)
{
	*p_iPValue = m_iPValue;
	*p_iIValue = m_iIValue;
}
