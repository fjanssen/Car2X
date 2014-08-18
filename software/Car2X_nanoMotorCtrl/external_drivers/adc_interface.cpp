/*
 * adc_interface.cpp
 *
 *  Created on: 27.01.2014
 *      Author: Florian
 */

#include "../terasic_lib/adc_spi_read.h"
#include "alt_types.h"

#include "adc_interface.h"

bool ReadADCChannels(alt_u8 *uiChannels, alt_u8 uiChannelCount, alt_u32 *uiValues)
{
	if(uiChannelCount < 1)
		return false;

	// Start Read for the first channel
	ADC_Read(uiChannels[0]);

	// Read rest
	for(int i = 0; i < uiChannelCount-1; i++)
	{
		uiValues[i] = ADC_Read(uiChannels[i+1]);
		uiValues[i] *= 100;
		uiValues[i] /= 1311;
	}

	// Read last
	uiValues[uiChannelCount-1] = ADC_Read(0);
	uiValues[uiChannelCount-1] *= 100;
	uiValues[uiChannelCount-1] /= 1311;

	return true;
}

