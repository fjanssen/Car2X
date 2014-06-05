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
	MEM_BUFFERFLAGS_OVERFLOW,
	MEM_BUFFERFLAGS_CORRUPT,
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
 * \param sourceMemArea_en the identifier of the requested memory area in shared memory.
 * \param[out] elementsCopied_pu32 number of elements copied into the destination.
 * \param dest_pst a pointer to a struct where the contents from the shared memory
 * 				   will be copied to.
 * \param destSize_u32 size of the memory pointed to by dest_pst.
 *
 * \return ERR_MEM_
 */
extern enum CORE_ErrCode MEM_GetMemCopy(enum sharedMemAreaIds sourceMemArea_en,
										alt_u32 * elementsCopied_pu32,
		                                void * dest_pst,
		                                alt_u32 destSize_u32);

/** MEM_SetMemBuffer
 *
 * \brief copies data into the shared memory.
 *
 * \param destMemArea_en the identifier of the destination memory area in shared memory.
 * \param source_pst pointer to a struct where the data will be copied from.
 * \param sourceElements_u32 number of elements in the source data structure.
 */
extern enum CORE_ErrCode MEM_SetMem(enum sharedMemAreaIds destMemArea_en,
									void * source_pst,
									alt_u32 sourceElements_u32);

#endif /* MEM_API_H_ */
