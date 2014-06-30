// Export interface
#include "ADCSensor.h"

// Import interface
#include "ADCValuesMessage.h"
#include "ADCInfoMessage.h"

CADCSensor::CADCSensor()
{
	m_uiType = 0x0A;

	m_bWasInitialised = false;
	m_uiNextToUpdate = 0;
	
	m_uiChannelCount = 0;
	m_uiChannelsConnected = 0;
}

CADCSensor::~CADCSensor()
{
}


CCarMessage *CADCSensor::getCarMessage()
{
	CCarMessage *p_carMessage = 0;

	if(!m_bWasInitialised)
	{
		alt_u8 uiChannelNumbers[2];
		uiChannelNumbers[0] = m_uiNextToUpdate;
		uiChannelNumbers[1] = m_uiNextToUpdate + 1;
		p_carMessage = (CCarMessage *) new CADCInfoMessage(uiChannelNumbers);
	}
	else
	{
		alt_u8 uiChannelNumbers[2];
		uiChannelNumbers[0] = m_uiChannelNumbers[m_uiNextToUpdate];
		uiChannelNumbers[1] = m_uiChannelNumbers[m_uiNextToUpdate + 1];
		
		p_carMessage = (CCarMessage *) new CADCValuesMessage(m_uiChannelNumbers, m_uiChannelsConnected);
	}

	return p_carMessage;
}

bool CADCSensor::updateSensorState(CCarMessage * p_message)
{
	// TODO: rewrite without threads
	// Get access to the state:
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
//		if(p_message->getSubType() == 0x00 && !m_bWasInitialised)
//		{
//			CADCInfoMessage *p_adcMessage = (CADCMessage *) p_message;
//
//			m_uiChannelCount = p_adcMessage->getUiChannelCount();
//
//			if(m_uiChannelCount > 0)
//			{
//				m_uiChannelNumbers[m_uiNextToUpdate] = getUiChannelNumbers()[0];
//				m_uiChannelValues[m_uiNextToUpdate] = 0;
//				m_uiChannelNumbers[m_uiNextToUpdate + 1] = getUiChannelNumbers()[1];
//				m_uiChannelValues[m_uiNextToUpdate + 1] = 0;
//
//				memcpy(m_uiChannelAliasStrings+7*m_uiNextToUpdate, p_adcMessage->getUiChannelAliasStrings(), sizeof(alt_u8) * 7);
//
//				memcpy(m_uiChannelAliasStrings+7*m_uiNextToUpdate+7, p_adcMessage->getUiChannelAliasStrings()+7, sizeof(alt_u8) * 7);
//
//				m_uiNextToUpdate += 2;
//
//				if(m_uiNextToUpdate >= m_uiChannelCount)
//				{
//					m_bWasInitialised = true;
//					m_uiNextToUpdate = 0;
//				}
//
//				m_uiNextToUpdate += 2;
//				if(m_uiNextToUpdate >= m_uiChannelCount)
//					m_uiNextToUpdate = 0;
//			}
//		}
//		else if(p_message->getSubType() == 0x01 && m_bWasInitialised)
//		{
//			CADCValuesMessage *p_adcvalueMessage = (CADCValuesMessage *) p_message;
//
//			m_uiChannelValues[m_uiNextToUpdate] = p_adcvalueMessage->getUiChannelValues()[0];
//			m_uiChannelValues[m_uiNextToUpdate+1] = p_adcvalueMessage->getUiChannelValues()[1];
//
//
//		}
//
//		m_bStateValid = true;
//	pthread_mutex_unlock(&m_accesssMutex);

	return true;
}


alt_u16 CADCSensor::getValueByChannel(alt_u8 uiChannel)
{
	if(!m_bWasInitialised || uiChannel > m_uiChannelCount)
		return -1;

	return m_uiChannelValues[uiChannel];
}


alt_u8 *CADCSensor::getChannelAliasStrings()
{
	return m_uiChannelAliasStrings;
}
