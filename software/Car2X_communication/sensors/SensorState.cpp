/*
 * main.cpp
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

// Export interface
#include "SensorState.h"

// Import interface
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

CSensorState::CSensorState()
{
}

CSensorState::~CSensorState()
{

}


CCarMessage *CSensorState::getCarMessage()
{
	return 0;
}

bool CSensorState::updateSensorState(CCarMessage * p_message)
{
	return true;
}

alt_u8 CSensorState::getType()
{
	return m_uiType;
}

bool CSensorState::isValid()
{
	return m_bStateValid;
}

