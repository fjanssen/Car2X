/*
 * ultrasound_interface.h
 *
 *  Created on: 17.01.2014
 *      Author: Florian
 */

#ifndef ULTRASOUND_INTERFACE_H_
#define ULTRASOUND_INTERFACE_H_

#include <io.h>
#include <alt_types.h>

// TODO: fix :D
#define CENTRAL_ECU_BUILD

#ifndef CENTRAL_ECU_BUILD
#include "properties.h"
#endif

//write_operation
#define trigger_sensor(base_addr)	 IOWR(base_addr+(0<<2), 0, 1)
#define trigger_clear(base_addr)	 IOWR(base_addr+(0<<2), 0, 0)
//read operation
#define get_sensor_control(base_addr)	 IORD(base_addr+(0<<2), 0)
#define get_sensor_data(base_addr)	 IORD(base_addr+(1<<2), 0)
#define get_sensor_state(base_addr)	 IORD(base_addr+(2<<2), 0)

alt_32 measuredistance(const alt_u32 base_address);


#endif /* ULTRASOUND_INTERFACE_H_ */
