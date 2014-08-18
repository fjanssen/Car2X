/*
 * utility.h
 *
 *  Created on: 11.11.2013
 *      Author: Florian
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <alt_types.h>

/*
 * Function blocks for the given time in ms.
 * Note this time can be +- some clk cycles and is so said not accurate!
 * Maybe someone can find a better conversion between ms and clock cycles.
 * Yet 444 while loop runs make 1 ms.
 */
void delay (unsigned int del);

/*
 * Reverse the order of the given byte array of the given length.
 * This can be used to change between the Endianess of a simple type (such as int).
 * Simply call this function with a (byte) pointer to the type and the length of the type.
 *
 * Example:
 *
 *      byte pArray[128];
 *      alt_16 short_integer = 100;
 *
 *      *((alt_16*) (pByteArray)) = short_integer;
 *      swapEndianess(pByteArray, sizeof(alt_16));
 */
void swapEndianess(alt_u8 *pArray, alt_u32 iLength);


#endif /* UTILITY_H_ */
