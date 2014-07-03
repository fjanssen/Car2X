/*
 * MemController.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: wji
 */

/******************************************************************************
 * INCLUDES
 *****************************************************************************/
#include "alt_types.h"
#include "altera_avalon_mutex.h"
#include "MemController.h"
#include "MemSharedArea.h"
#include "ErrHandler.h"
#include <stdio.h>


using namespace c2x;

MemController::MemController() {
	m_mutexCarState_p = altera_avalon_mutex_open("");

	// make sure that all mutexes were acquired.
	if(m_mutexCarState_p == NULL)
	{
		LOG_ERROR(ERR_MEM_OPENMUTEX, "Failed to acquire all hardware mutexes: " \
				"carMsgRx@%#x", (unsigned int) m_mutexCarState_p);
	}

	m_memAreaCarState_p = &AreaCarState;
}

MemController::~MemController() {
	altera_avalon_mutex_close(m_mutexCarState_p);
}

template<typename T> ErrCode MemController::getAllElements(
		MemController::AreaId areaId,
		T &elements,
		uint32_t destSize_u32,
		uint32_t &elementsCopied_u32)
{
	/* --- local variables ---*/
	ErrCode retVal = ERR_NONE;
	const MemSharedArea<T> * memArea;

	/* --- validation ---*/
	if(retVal = getSharedMemArea(areaId, memArea), retVal != ERR_NONE)
	{
		LOG_DEBUG("Throwing error up.");
		return retVal;
	}
	if(destSize_u32 < memArea->maxNumElements_u32)
	{
		releaseSharedMemArea(memArea);
		LOG_ERROR_RETURN(ERR_MEM_DESTTOOSMALL, "The destination buffer is too small!" \
					     "Trying to copy %d Elements into buffer of size %d .",
					     memArea->index_u32, destSize_u32);
	}

	/* --- function body ---*/
	// copy the actual data
	memcpy(&(memArea->content_a),
		   memArea->index * sizeof(*(memArea->content_a)),
		   &elements);

	elementsCopied_u32 = memArea->index_u32;

	// reset element count, flags
	memArea->index_u32 = 0;
	memArea->flags_u32 = MEM_BUFFERFLAGS_NONE;

	// Release the mutex for the source memory area, this is important!!!
	releaseSharedMemArea(memArea);

	return retVal;
}

template<typename T> void MemController::clearElements(MemController::AreaId areaId)
{
	/* --- local variables ---*/
	ErrCode retVal = ERR_NONE;
	const MemSharedArea<T> * memArea;

	/* --- validation ---*/
	if(retVal = getSharedMemArea(areaId, memArea), retVal != ERR_NONE)
	{
		LOG_DEBUG("Throwing error up.");
		return;
	}

	memArea->index_u32 = 0;
	memArea->flags_u32 = MEM_BUFFERFLAGS_NONE;
}


template<typename T> ErrCode MemController::pushElement(MemController::AreaId areaId, T &element)
{
	/* --- local variables ---*/
	ErrCode retVal = ERR_NONE;
	const MemSharedArea<T> * memArea;

	/* --- validation ---*/
	if(retVal = getSharedMemArea(areaId, memArea), retVal != ERR_NONE)
	{
		LOG_DEBUG("Throwing error up.");
		return retVal;
	}
	if(memArea->index_u32 == memArea->maxNumElements_u32)
	{
		releaseSharedMemArea(memArea);
		LOG_ERROR_RETURN(ERR_MEM_DESTTOOSMALL, "The destination buffer is full, contains %d elements.",
				memArea->index_u32);
	}

	// circular buffer
	memArea->index_u32 = (memArea->index_u32 < (memArea->maxNumElements_u32 - 1)) ? memArea->index_u32 + 1 : 0;
	memArea->content_a[memArea->index_u32] = element;

	return retVal;
}

template<typename T> T MemController::getElement(MemController::AreaId areaId, uint32_t negIndex)
{
	/* --- local variables ---*/
	ErrCode retVal = ERR_NONE;
	const MemSharedArea<T> * memArea;
	T element;
	uint32_t index;

	/* --- validation ---*/
	if(retVal = getSharedMemArea(areaId, memArea), retVal != ERR_NONE)
	{
		LOG_DEBUG("Throwing error up.");
		return NULL;
	}
	if(memArea->index_u32 == memArea->maxNumElements_u32)
	{
		releaseSharedMemArea(memArea);
		LOG_ERROR(ERR_MEM_DESTTOOSMALL, "The destination buffer is full, contains %d elements.",
				memArea->index_u32);
		return NULL;
	}

	if(memArea->index - negIndex < 0)
	{
		index = memArea->index_u32 - negIndex;
	}
	else
	{
		index = memArea->maxNumElements_u32 + (memArea->index_u32 - negIndex);
	}

	element = memArea->content_a[index];

	return element;
}



template<typename T> T MemController::getLastElement(MemController::AreaId areaId)
{
	return getElement<T>(areaId, 0);
}

/******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATION
 *****************************************************************************/
/** getSharedMemArea
 *
 * \details */
template<typename T> bool MemController::getSharedMemArea(MemController::AreaId areaId, MemSharedArea<T> * memArea_p)
{
	/* --- local variables --- */
	MemSharedArea<T> * memArea_pv = NULL;
	alt_mutex_dev * mutex_p = NULL;

	/* --- function body --- */

	switch (areaId)
	{
	case MemController::AreaId_CarState:
		memArea_p = m_memAreaCarState_p;
		mutex_p = m_mutexCarState_p;
		break;
	default:
		LOG_ERROR_RETURN(ERR_MEM_INVALIDAREA, "memory area ID %d is not valid.", areaId);
		break;
	}

	altera_avalon_mutex_lock(mutex_p, 1); //TODO: ??? 1

	return ERR_NONE;
}

/** releaseSharedMemBuffer
 *
 * \details */
bool MemController::releaseSharedMemArea(MemController::AreaId areaId)
{
	/* --- local variables --- */
	alt_mutex_dev * mutex_p = NULL;

	/* --- function body --- */

	switch (areaId)
	{
	case MemController::AreaId_CarState:
		mutex_p = m_mutexCarState_p; break;
	default:
		LOG_ERROR(ERR_MEM_INVALIDAREA, "memory area ID %d is not valid.", areaId); break;
	}

	// if a valid flash area has been found, unlock the mutex.
	altera_avalon_mutex_unlock(mutex_p);

	return 0;
}

