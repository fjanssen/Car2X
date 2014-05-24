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

/** SharedMemoryArea
 *
 * \member memSize_u32 length of the memory area pointed to by content_pv
 * \member content_pv contents of the shared memory area
 * \member numElements_u32 number of Bytes used of the shared memory contents
 * \member flags_u8 keep track of state of the memory
 */
struct SharedMemoryArea{
	const alt_u32 memSize_u32;
	const alt_u32 memElementSize_u32;
	const void * content_pv;
	alt_u32 memBytesUsed_u32;
	enum bufferFlags flags_u8;
};

// External declarations of shared memory areas
// defined in MEM_SharedAlloc.c
extern static struct SharedMemoryArea m_memAreaMotorSpeed_st;
extern static struct SharedMemoryArea m_memAreaCarCommand_st;
extern static struct SharedMemoryArea m_memAreaC2xRx_st;
extern static struct SharedMemoryArea m_memAreaC2xTx_st;
extern static struct SharedMemoryArea m_memAreaUsSensor_st;


#endif /* MEM_INTERNAL_H_ */
