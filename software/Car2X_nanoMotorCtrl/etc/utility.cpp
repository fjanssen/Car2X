/*
 * utility.cpp
 *
 *  Created on: 11.11.2013
 *      Author: Florian
 */

#include "utility.h"


void delay (unsigned int seconds)
{
	// TODO: is this even accurate?
	seconds *= 444;

	while (seconds != 0)
	{
		seconds --;
	}
}

void swapEndianess(alt_u8 *pArray, alt_u32 iLength)
{
	alt_u8 buffer;
	alt_u32 middle = iLength / 2;

	iLength--;
	for(alt_u32 i = 0; i < middle; )
	{
		buffer = pArray[i];
		pArray[i] = pArray[iLength];
		pArray[iLength] = buffer;
		i++;
		iLength--;
	}
}
