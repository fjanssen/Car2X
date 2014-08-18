/*
 * adc_interface.h
 *
 *  Created on: 27.01.2014
 *      Author: Florian
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include <alt_types.h>

bool ReadADCChannels(alt_u8 *uiChannels, alt_u8 uiChannelCount, alt_u32 *uiValues);

#endif /* ADC_INTERFACE_H_ */
