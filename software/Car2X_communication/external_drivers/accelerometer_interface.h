/*
 * accelerometer_interface.h
 *
 *  Created on: 27.01.2014
 *      Author: Florian
 */

#ifndef ACCELEROMETER_INTERFACE_H_
#define ACCELEROMETER_INTERFACE_H_

#include <alt_types.h>

// TODO: what's the actual address?
#define GSENSOR_SPI_BASE (1)

bool getAcceleration(alt_16 *iXYZ);


#endif /* ACCELEROMETER_INTERFACE_H_ */
