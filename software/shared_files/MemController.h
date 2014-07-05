/*
 * MemController.h
 *
 *  Created on: Jun 9, 2014
 *      Author: wji
 */

#ifndef MEMCONTROLLER_H_
#define MEMCONTROLLER_H_

extern "C" {
#include "altera_avalon_mutex.h"
#include "ErrHandler.h"
#include "alt_types.h"
#include "altera_avalon_mutex.h"
#include <stdio.h>
}

#include "MemSharedArea.h"


template<typename T>
class MemController {
public:
	enum AreaId {
		AreaId_CarState
	};

//	MemController();
//	virtual ~MemController();
//
//	ErrCode pushElement(T &element);
//
//	T getLastElement();
//
//	T getLastElement(bool blocking);
//
//	T getElement(alt_u32 negIndex, bool blocking);
//
//	ErrCode getAllElements(
//			T &elements,
//			alt_u32 destSize_u32,
//			alt_u32 &elementsCopied_u32);
//	void clearElements();


	MemController() {
		m_memArea_p = NULL;
		m_mutexArea_p = NULL;

	//	switch (areaId)
	//	{
	//	case MemController::AreaId_CarState:
	//		m_memArea_p = &AreaCarState;
	//		m_mutexArea_p = altera_avalon_mutex_open("");
	//		break;
	//	default:
	//		LOG_ERROR_RETURN(ERR_MEM_INVALIDAREA, "memory area ID %d is not valid.", areaId);
	//		break;
	//	}


		m_memArea_p = &AreaCarState;
		m_mutexArea_p = altera_avalon_mutex_open("");

		// make sure that all mutexes were acquired.
		if(m_mutexArea_p == NULL)
		{
			LOG_ERROR(ERR_MEM_OPENMUTEX, "Failed to acquire all hardware mutexes: " \
					"carMsgRx@%#x", (unsigned int) m_mutexArea_p);
		}
	}

	~MemController() {
		altera_avalon_mutex_close(m_mutexArea_p);
	}

	ErrCode getAllElements(
			T &elements,
			alt_u32 destSize_u32,
			alt_u32 &elementsCopied_u32)
	{
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;
		MemSharedArea<T> * memArea;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(memArea), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return retVal;
		}
		if(destSize_u32 < memArea->maxNumElements_u32)
		{
			releaseSharedMemArea();
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
		releaseSharedMemArea();

		return retVal;
	}

	void clearElements()
	{
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;
		MemSharedArea<T> * memArea;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(memArea), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return;
		}

		memArea->index_u32 = 0;
		memArea->flags_u32 = MEM_BUFFERFLAGS_NONE;
	}

	ErrCode pushElement(T &element)
	{
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;
		MemSharedArea<T> * memArea;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(memArea), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return retVal;
		}
		if(memArea->index_u32 == memArea->maxNumElements_u32)
		{
			releaseSharedMemArea();
			LOG_ERROR_RETURN(ERR_MEM_DESTTOOSMALL, "The destination buffer is full, contains %u elements.",
					(unsigned int)memArea->index_u32);
		}

		// circular buffer
		memArea->index_u32 = (memArea->index_u32 < (memArea->maxNumElements_u32 - 1)) ? memArea->index_u32 + 1 : 0;
		memArea->content_a[memArea->index_u32] = element;

		releaseSharedMemArea();

		return retVal;
	}

	T getElement(alt_u32 negIndex, bool blocking)
	{
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;
		MemSharedArea<T> * memArea;
		T element; // TODO: should return some sort of error instaed of uninitialised element
		alt_u32 index;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(memArea), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return element;
		}
		if(memArea->index_u32 == memArea->maxNumElements_u32)
		{
			releaseSharedMemArea();
			LOG_ERROR(ERR_MEM_DESTTOOSMALL, "The destination buffer is full, contains %d elements.",
					memArea->index_u32);
			return element;
		}

		if(memArea->index_u32 - negIndex < 0)
		{
			index = memArea->index_u32 - negIndex;
		}
		else
		{
			index = memArea->maxNumElements_u32 + (memArea->index_u32 - negIndex);
		}

		element = memArea->content_a[index];

		if(blocking == false)
		{
			releaseSharedMemArea();
		}

		return element;
	}

	T getLastElement()
	{
		return getElement(0, false);
	}

	T getLastElement(bool blocking)
	{
		return getElement(0, blocking);
	}

private:
	/* \brief Gets and locks a buffer located in the shared memory. This will
	 * 		  blockingly wait for the hardware mutex. Release the mutex with a
	 * 		  corresponding call to \ref releaseSharedMemBuffer()
	 * \param memArea_en identifier of shared memory buffer to query
	 * \param[out] memArea_p pointer to memory area */
//	bool getSharedMemArea(MemSharedArea<T> * memArea_p);

	/* \brief releases the hardware mutex for a given buffer in shared memory
	 * \param memArea_en identifier of shared memory buffer to query */
//	bool releaseSharedMemArea();

	// mutexes
	alt_mutex_dev * m_mutexArea_p;

	// memory areas
	const MemSharedArea<T> * m_memArea_p;


	/** getSharedMemArea
	 *
	 * \details */
	ErrCode getSharedMemArea(MemSharedArea<T> * memArea_p)
	{
		// TODO: conditional lock, only if we don't currently have it.
		altera_avalon_mutex_lock(m_mutexArea_p, 1); //TODO: ??? 1

		return ERR_NONE;
	}

	/** releaseSharedMemBuffer
	 *
	 * \details */
	bool releaseSharedMemArea()
	{
		altera_avalon_mutex_unlock(m_mutexArea_p);

		return 0;
	}

};

#endif /* MEMCONTROLLER_H_ */
