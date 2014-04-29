/*
 * accelerometer_interface.cpp
 *
 *  Created on: 27.01.2014
 *      Author: Florian
 */

#include "../terasic_lib/terasic_includes.h"
#include "../terasic_lib/accelerometer_adxl345_spi.h"
#include "../terasic_lib/I2C.h"
#include "../terasic_lib/adc_spi_read.h"

#include "accelerometer_interface.h"

// Local variables:
bool bSPIReady = false;

bool getAcceleration(alt_16 *iXYZ)
{
	bool bSuccess = false;

	if(!bSPIReady)
		bSPIReady = ADXL345_SPI_Init(GSENSOR_SPI_BASE);

	if(bSPIReady)
	{
		if (ADXL345_SPI_IsDataReady(GSENSOR_SPI_BASE))
		{
			bSuccess = ADXL345_SPI_XYZ_Read(GSENSOR_SPI_BASE, (unsigned short*) iXYZ);

			if (bSuccess)
			{
				iXYZ[0]*=4; iXYZ[1]*=4; iXYZ[2]*=4;
				//printf("X=%d mg, Y=%d mg, Z=%d mg\r\n", iXYZ[0], iXYZ[1], iXYZ[2]);
			}
		}

	}

	return bSuccess;

}


