/*
 * MEM_Api.h
 *
 *  Created on: May 22, 2014
 *      Author: wji
 */

#ifndef MEM_API_H_
#define MEM_API_H_

/******************************************************************************
 * DEFINES
 *****************************************************************************/
// Memory Buffer Configuration
// Buffer lengths (number of elements)
#define MEM_BUFFERLEN_MOTORSPEED (100u)
#define MEM_BUFFERLEN_CARCOMMAND (100u)
#define MEM_BUFFERLEN_C2XRX      (100u)
#define MEM_BUFFERLEN_C2XTX      (100u)
#define MEM_BUFFERLEN_USSENSOR   (100u)


/******************************************************************************
 * ENUMS/TYPES
 *****************************************************************************/
// Memory area identifiers
enum sharedMemAreaIds {
	MEM_AREA_MOTORSPEED = 0,
	MEM_AREA_CARCOMMAND,
	MEM_AREA_C2XRX,
	MEM_AREA_C2XTX,
	MEM_AREA_USSENSOR,
};

// Buffer flag definitions
enum bufferFlags {
	MEM_BUFFERFLAGS_NONE = 0,
};

// Shared memory area definitions
struct SharedMemoryArea{
	alt_u32 numElements;
	alt_u8  flags;
	const alt_u32 elementSize;
	const alt_u32 maxNumElements;
	const void * elements;
};

/******************************************************************************
 * API FUNCTION PROTOTYPES
 *****************************************************************************/
/** MEM_Init
 *
 * \brief initialises the hardware mutexes to access shared memory. This function
 *        MUST be called once, before trying to access shared memory.
 *
 * \return ERR_MEM_OPENMUTEX
 */
extern enum CORE_ErrCode MEM_ModuleInit(void);

/** MEM_GetMemCopy
 *
 * \brief retrieves the contents of a memory area from shared memory by copying all
 *        data.
 *  NOTE: you must make sure that the memory space pointed at by dest_pv is
 *        large enough to accommodate the entire shared memory area!!
 *
 * \param source_en the identifier of the requested memory area in shared memory.
 * \param dest_pst a pointer to a struct where the data from shared memory will be
 * 	               copied to.
 *
 * \return ERR_MEM_
 */
extern enum CORE_ErrCode MEM_GetMemCopy(enum sharedMemAreaIds source_en,
		                                struct SharedMemoryArea * dest_pst);

/** MEM_SetMemBuffer
 *
 * \brief copies data into the shared memory.
 *
 * \param dest_en the identifier of the destination memory area in shared memory.
 * \param dest_pst pointer to a struct where the data will be copied from.
 */
extern enum CORE_ErrCode MEM_SetMem(enum sharedMemAreaIds dest_en,
									struct SharedMemoryArea * source_pst);

#endif /* MEM_API_H_ */
