/*
 * properties.h
 *
 *  Created on: 07.01.2014
 *      Author: Florian
 */

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

// Version and ID
#define FIRMWARE_VERSION 		0x10
#define COMPONENT_TYPE			0x01
#define COMPONENT_ID			0x03

// Defines for Motor/Wheel
#define WHEEL_SCALE 371 // in mm
#define INVERTED 2 // 1: Not inverted, 2: inverted -- 1:right wheels, 2:left wheels

// Defines for Ultrasound-Sensor
#define ULTRASOUND_AVAILABLE    0x08

// Defines for ADC-Sensor
#define ADC_CHANNEL_COUNT 8
#define ADC_CONNECTED_CHANNELS 2
#define ADC_CHANNEL_NUMBERS {0x00, 0x02}
#define ADC_CHANNEL_ALIAS_STRINGS "BAT L  BAT S  "


// Lists the available operations/sensors
#define AVAILABLE_OPERATIONS 0x00, 0x00, 0x00, 0x00


#endif /* PROPERTIES_H_ */
