// Export interface
#include "UltrasoundSensor.h"

// Import interface
#include "UltrasoundDistanceMessage.h"
#include <stdio.h>

CUltrasoundSensor::CUltrasoundSensor()
{
	m_uiType = 0x08;
}

CUltrasoundSensor::~CUltrasoundSensor()
{

}


CCarMessage *CUltrasoundSensor::getCarMessage()
{
	CUltrasoundDistanceMessage *p_distanceMessage = new CUltrasoundDistanceMessage();

	return (CCarMessage *) p_distanceMessage;
}

bool CUltrasoundSensor::updateSensorState(CCarMessage * p_message)
{
	CUltrasoundDistanceMessage *p_distanceMessage;

	// TODO: fix pthread
//	// Get access to the state:
//	pthread_mutex_lock( &m_accesssMutex);
//
//		// Set current state to invalid:
//		m_bStateValid = false;
//
//		// Check if it is the right message type
//		if(m_uiType != p_message->getType())
//		{
//			pthread_mutex_unlock(&m_accesssMutex);
//			return false;
//		}
//
//		// Cast to UltrasoundMessage
//		p_distanceMessage = (CUltrasoundDistanceMessage*) p_message;
//
//		// Get the state:
//		m_uiDistance = p_distanceMessage->getUiDistance();
//		m_uiDistanceValid = (p_distanceMessage->getUiDistanceValid() > 0);
//
//		m_bStateValid = true;
//	pthread_mutex_unlock(&m_accesssMutex);

	return true;
}

alt_u16 CUltrasoundSensor::getDistance()
{
	return m_uiDistance;
}

bool CUltrasoundSensor::isDistanceValid()
{
	return (m_uiDistanceValid > 0);
}
