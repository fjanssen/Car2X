/*
 * ultrasound_interface.c
 *
 *  Created on: 17.01.2014
 *      Author: Florian
 */

#include "ultrasound_interface.h"

alt_32 measuredistance(const alt_u32 base_address)
{
	alt_u32 state;
	alt_u32 measure_data;
	alt_32 distance;
	alt_u32 iTimeout = 0;

	state = get_sensor_state(base_address);
	while (state == 1)
	{
		state = get_sensor_state(base_address);
		iTimeout++;
		//if(iTimeout > 20)
		//	return -1;
	}

	trigger_clear(base_address);
	trigger_sensor(base_address);
	trigger_clear(base_address);

	state = get_sensor_state(base_address);
	iTimeout = 0;
	while (state != 2)
	{
		state = get_sensor_state(base_address);
		iTimeout++;
		//if(iTimeout > 20)
		//	return -1;
	}

	measure_data = get_sensor_data(base_address);
	if (measure_data == -1)
		distance = -1;
	else
	{
		distance = measure_data / 588;
	}

	return distance;
}

