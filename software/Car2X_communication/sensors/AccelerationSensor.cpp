// Export interface
#include "AccelerationSensor.h"

// Import interface
#include <stdio.h>
#include "AccelerationValuesMessage.h"

CAccelerationSensor::CAccelerationSensor()
{
	m_uiType = 0x09;
	m_bAccelerationValid = false;
}

CAccelerationSensor::~CAccelerationSensor()
{

}


CCarMessage *CAccelerationSensor::getCarMessage()
{
	CAccelerationValuesMessage *p_gsensorMessage = new CAccelerationValuesMessage();

	return (CCarMessage *) p_gsensorMessage;
}

bool CAccelerationSensor::updateSensorState(CCarMessage * p_message)
{
	CAccelerationValuesMessage *p_gsensorMessage;

	// TODO: fix pthread stuff

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
//		p_gsensorMessage = (CAccelerationValuesMessage*) p_message;
//
//		// Get the state:
//		m_iXAcceleration = p_gsensorMessage->getIXAcceleration();
//		m_iYAcceleration = p_gsensorMessage->getIYAcceleration();
//		m_iZAcceleration = p_gsensorMessage->getIZAcceleration();
//
//		m_bAccelerationValid = (p_gsensorMessage->getUiAccelerationFlags() > 0);
//
//		/*
//		if(m_bAccelerationValid)
//			printf("   X=%d mg, Y=%d mg, Z=%d mg    ", m_iXAcceleration, m_iYAcceleration, m_iZAcceleration);
//		else
//			printf("     No G Sensor     ");
//			*/
//		m_bStateValid = true;
//	pthread_mutex_unlock(&m_accesssMutex);

	return true;
}

alt_16 CAccelerationSensor::getXAcceleration()
{
	return m_iXAcceleration;
}

alt_16 CAccelerationSensor::getYAcceleration()
{
	return m_iYAcceleration;
}

alt_16 CAccelerationSensor::getZAcceleration()
{
	return m_iZAcceleration;
}

bool CAccelerationSensor::isAccelerationValid()
{
	return m_bAccelerationValid;
}
