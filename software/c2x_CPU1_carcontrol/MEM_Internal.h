/*
 * MEM_Internal.h
 *
 *  Created on: May 22, 2014
 *      Author: wji
 */

#ifndef MEM_INTERNAL_H_
#define MEM_INTERNAL_H_

#include "alt_types.h"
#include "MEM_Api.h"
#include "COMM_Api.h"

// Shared memory area definitions
struct SharedMemoryArea{
	alt_u32 numElements;
	alt_u8  flags;
	const alt_u32 elementSize;
	const alt_u32 maxNumElements;
	const void * elements;
};

// External declarations of shared memory areas
extern static struct SharedMemoryArea m_memAreaMotorSpeed_st;
extern static struct SharedMemoryArea m_memAreaCarCommand_st;
extern static struct SharedMemoryArea m_memAreaC2xRx_st;
extern static struct SharedMemoryArea m_memAreac2xTx_st;
extern static struct SharedMemoryArea m_memAreaUsSensor_st;


#endif /* MEM_INTERNAL_H_ */
