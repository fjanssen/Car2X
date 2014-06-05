/*
 * MEM.c
 *
 *  Created on: May 22, 2014
 *      Author: wji
 */


/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "alt_types.h"
#include "MEM_Api.h"
#include "MEM_Internal.h"
#include "ERR_Api.h"
#include "altera_avalon_mutex.h"



/******************************************************************************
 * DEFINES
 *****************************************************************************/
#define MEM_MODULEINIT_NONE (1)
#define MEM_MODULEINIT_SUCCESS (0)

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 *****************************************************************************/
/** getSharedMemBuffer
 *
 * \brief Gets and locks a buffer located in the shared memory. This will
 * 		  blockingly wait for the hardware mutex. Release the mutex with a
 * 		  corresponding call to \ref releaseSharedMemBuffer()
 *
 * \param memArea_en identifier of shared memory buffer to query
 * \param[out] buffer_pst pointer to memory buffer
 */
enum CORE_ErrCode getSharedMemArea(enum sharedMemAreaIds memArea_en,
								   void * memArea_pv);

/** releaseSharedMemBuffer
 *
 * \brief releases the hardware mutex for a given buffer in shared memory
 *
 * \param memArea_en identifier of shared memory buffer to query
 */
enum CORE_ErrCode releaseSharedMemBuffer(enum sharedMemAreaIds memArea_en);

/******************************************************************************
 * GLOBAL VARIABLES
 *****************************************************************************/
// Mutexes to access different parts of the shared memory
static alt_mutex_dev * m_mutexMotorSpeed_p;
static alt_mutex_dev * m_mutexCarCommand_p;
static alt_mutex_dev * m_mutexUsSensor_p;
static alt_mutex_dev * m_mutexC2xRx_p;
static alt_mutex_dev * m_mutexC2xTx_p;

// Init flag, make sure the module is initialised before allowing API function
// calls other than MEM_ModuleInit()
static alt_u8 m_initFlag_u8 = MEM_MODULEINIT_NONE;

// Only allow the module to have one mutex at a time.
static alt_b m_hasmutex_b = FALSE;
/******************************************************************************
 * API IMPLEMENTATION
 *****************************************************************************/
/** MEM_ModuleInit
 *
 * \details */
enum CORE_ErrCode MEM_ModuleInit()
{
	/* --- local variables ---*/
	enum CORE_ErrCode retVal_en = ERR_NONE;

	/* --- function body ---*/
	m_mutexMotorSpeed_p = altera_avalon_mutex_open("");
	m_mutexCarCommand_p = altera_avalon_mutex_open("");
	m_mutexUsSensor_p = altera_avalon_mutex_open("");
	m_mutexC2xRx_p = altera_avalon_mutex_open("");
	m_mutexC2xTx_p = altera_avalon_mutex_open("");

	// make sure that all mutexes were acquired.
	if((m_mutexC2xRx_p == NULL) || (m_mutexC2xTx_p == NULL) ||
	   (m_mutexMotorSpeed_p == NULL) || (m_mutexCarCommand_p == NULL) ||
	   (m_mutexUsSensor_p == NULL))
	{
		LOG_ERROR_RETURN(ERR_MEM_OPENMUTEX, "Failed to acquire all hardware mutexes: " \
				"motor@%#x, carcontrol@%#x, ussensor@%#x, c2xrx@%#x, c2xtx@%#x",
				m_mutexMotorSpeed_p, m_mutexCarCommand_p, m_mutexUsSensor_p, m_mutexC2xRx_p, m_mutexC2xTx_p);
	}

	m_initFlag_u8 = MEM_MODULEINIT_SUCCESS;

	return retVal_en;
}

/** MEM_GetMemCopy
 *
 * \details */
enum CORE_ErrCode MEM_GetMemCopy(enum sharedMemAreaIds sourceMemArea_en,
								 alt_u32 * elementsCopied_pu32,
								 void * dest_pst,
								 alt_u32 destSize_u32)
{
	/* --- local variables ---*/
	struct SharedMemoryArea * sharedMem_pst;
	enum CORE_ErrCode retVal_en = ERR_NONE;

	/* --- validation ---*/
	if(m_initFlag_u8 != MEM_MODULEINIT_SUCCESS)
	{
		LOG_ERROR_RETURN(ERR_MEM_NOINIT, "Module not initialised.");
	}
	if(retVal_en != ERR_NONE, retVal_en = getSharedMemArea(sourceMemArea_en, sharedMem_pst))
	{
		LOG_DEBUG("Throwing error up.");
		return retVal_en;
	}
	if(destSize_u32 < sharedMem_pst->memBytesUsed_u32)
	{
		releaseSharedMemBuffer(sourceMemArea_en);
		LOG_ERROR_RETURN(ERR_MEM_DESTTOOSMALL, "The destination buffer is too small!" \
					     "Trying to copy %d Bytes into %d of memory.",
					     sharedMem_pst->memBytesUsed_u32, destSize_u32);
	}

	/* --- function body ---*/
	// copy the area definitions
	*dest_pst = *sharedMem_pst;

	// copy the actual data
	memcpy(sharedMem_pst->content_pv,
		   sharedMem_pst->memBytesUsed_u32,
		   dest_pst);

	*elementsCopied_pu32 = sharedMem_pst->memBytesUsed_u32 / sharedMem_pst->memElementSize_u32;

	// reset element count, flags
	sharedMem_pst->memBytesUsed_u32 = 0;
	sharedMem_pst->flags_u8 = MEM_BUFFERFLAGS_NONE;

	// Release the mutex for the source memory area, this is important!!!
	releaseSharedMemArea(sourceMemArea_en);

	return retVal_en;
}

/** MEM_SetMem
 *
 * \details */
enum CORE_ErrCode MEM_SetMem(enum sharedMemAreaIds destMemArea_en,
							 void * source_pst,
							 alt_u32 sourceElements_u32)
{
	/* --- local variables ---*/
	struct SharedMemoryArea * dest_pst;
	enum CORE_ErrCode retVal_en;

	/* --- validation ---*/
	if(m_initFlag_u8 != MEM_MODULEINIT_SUCCESS)
	{
		LOG_ERROR_RETURN(ERR_MEM_NOINIT, "Module not initialised.");
	}
	if(retVal_en != ERR_NONE, retVal_en = getSharedMemBuffer(destMemArea_en, dest_pst))
	{
		LOG_DEBUG("Throwing error up.");
		return retVal_en;
	}
	if(dest_pst->memSize_u32 < sourceElements_u32 * dest_pst->memElementSize_u32)
	{
		releaseSharedMemBuffer(destMemArea_en);
		LOG_ERROR_RETURN(ERR_MEM_DESTTOOSMALL, "The destination buffer is too small!" \
					     "Trying to copy %d Bytes into %d of memory.",
					     sourceElements_u32, dest_pst->memSize_u32);
	}


	/* --- function body --- */
	// copy the area definitions
	*dest_pst = *source_pst;

	// copy the actual data
	memcpy(source_pst,
			sourceElements_u32*dest_pst->memElementSize_u32,
			dest_pst->content_pv);

	dest_pst->memBytesUsed_u32 = sourceElements_u32 * dest_pst->memElementSize_u32;

	// Release the mutex for the source memory area, this is important!!!
	releaseSharedMemArea(destMemArea_en);

	return retVal_en;
}


/******************************************************************************
 * LOCAL FUNCTION IMPLEMENTATION
 *****************************************************************************/
/** getSharedMemArea
 *
 * \details */
enum CORE_ErrCode getSharedMemArea(enum sharedMemAreaIds memArea_en,
								   struct SharedMemoryArea * memArea_pv)
{
	/* --- local variables --- */
	memArea_pv = NULL;
	alt_mutex_dev * mutex_p = NULL;

	/* --- validation --- */
	// only allow one memory area to be accessed from one CPU at a time, to avoid
	// more complicated deadlock handling
	if(m_hasmutex_b == TRUE)
	{
		LOG_INFO("Cannot acquire new mutex, as module already has another mutex!");
		return ERR_MEM_ONEMUTEXATATIME;
	}

	/* --- function body --- */
	// TODO: disable interrupts

	switch (memArea_en)
	{
	case MEM_AREA_MOTORSPEED:
		memArea_pv = &m_memAreaMotorSpeed_st;
		mutex_p = m_mutexMotorSpeed_p;
		break;
	case MEM_AREA_CARCOMMAND:
		memArea_pv = &m_memAreaCarCommand_st;
		mutex_p = m_mutexCarCommand_p;
		break;
	case MEM_AREA_C2XRX:
		memArea_pv = &m_memAreaC2xRx_st;
		mutex_p = m_mutexC2xRx_p;
		break;
	case MEM_AREA_C2XTX:
		memArea_pv = &m_memAreaC2xTx_st;
		mutex_p = m_mutexC2xTx_p;
		break;
	case MEM_AREA_USSENSOR:
		memArea_pv = &m_memAreaUsSensor_st;
		mutex_p = m_mutexUsSensor_p;
		break;
	default:
		LOG_ERROR_RETURN(ERR_MEM_INVALIDAREA, "memory area ID %d is not valid.", memArea_en);
		break;
	}

	altera_avalon_mutex_lock(mutex_p);

	// TODO: reenable interrupts
	return ERR_NONE;
}

/** releaseSharedMemBuffer
 *
 * \details */
void releaseSharedMemBuffer(enum sharedMemAreaIds memArea_en)
{
	/* --- local variables --- */
	alt_mutex_dev * mutex_p = NULL;

	/* --- function body --- */
	switch (memArea_en)
	{
	case MEM_AREA_MOTORSPEED:
		mutex_p = m_mutexMotorSpeed_p; break;
	case MEM_AREA_CARCOMMAND:
		mutex_p = m_mutexCarCommand_p; break;
	case MEM_AREA_C2XRX:
		mutex_p = m_mutexC2xRx_p; break;
	case MEM_AREA_C2XTX:
		mutex_p = m_mutexC2xTx_p; break;
	case MEM_AREA_USSENSOR:
		mutex_p = m_mutexUsSensor_p; break;
	default:
		LOG_ERROR(ERR_MEM_INVALIDAREA, "memory area ID %d is not valid.", memArea_en); break;
	}

	// if a valid flash area has been found, unlock the mutex.
	altera_avalon_mutex_unlock(mutex_p);
}
