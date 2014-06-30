#ifndef ADC_SPI_READ_H_
#define ADC_SPI_READ_H_

#include <alt_types.h>

// TODO: find out actual address base
#define ADC_SPI_READ_BASE (1)

alt_u16 ADC_Read(alt_u8 NextChannel);

#endif /*ADC_SPI_READ_H_*/
