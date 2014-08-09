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
		m_mutexArea_p = altera_avalon_mutex_open("/dev/shared_memory_mutex");

		if(m_memArea_p->content_a == NULL)
		{
			LOG_DEBUG("Initialising shared memory...");
			getSharedMemArea();
			m_memArea_p->content_a = AreaCarStateBuffer;
			m_memArea_p->index_u32 = 0;
			m_memArea_p->maxNumElements_u32 = BUFFERSIZE_CARSTATE;
			releaseSharedMemArea();
		}

		// make sure that all mutexes were acquired.
		if(m_mutexArea_p == NULL)
		{
			LOG_ERROR(ERR_MEM_OPENMUTEX, "Failed to acquire all hardware mutexes: " \
					"carMsgRx@%#x", (unsigned int) m_mutexArea_p);
		}

		LOG_DEBUG("Memcontroller constructed. m_memArea_p: %#x, size: %d, index %d",
				m_memArea_p, m_memArea_p->maxNumElements_u32, m_memArea_p->index_u32);
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

		/* --- validation ---*/
		if(retVal = getSharedMemArea(), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return retVal;
		}

		/* --- function body ---*/
		// copy the actual data
		memcpy(&(m_memArea_p->content_a),
			   m_memArea_p->index * sizeof(*(m_memArea_p->content_a)),
			   &elements);

		elementsCopied_u32 = m_memArea_p->index_u32;

		// reset element count, flags
		m_memArea_p->index_u32 = 0;
		m_memArea_p->flags_u32 = MEM_BUFFERFLAGS_NONE;

		// Release the mutex for the source memory area, this is important!!!
		releaseSharedMemArea();

		return retVal;
	}

	void clearElements()
	{
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return;
		}

		m_memArea_p->index_u32 = 0;
		m_memArea_p->flags_u32 = MEM_BUFFERFLAGS_NONE;
	}

	ErrCode pushElement(T &element)
	{
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return retVal;
		}

		// circular buffer
		LOG_DEBUG("push element to index %d", m_memArea_p->index_u32);

		m_memArea_p->index_u32 = (m_memArea_p->index_u32 < (m_memArea_p->maxNumElements_u32 - 1)) ? m_memArea_p->index_u32 + 1 : 0;
		m_memArea_p->content_a[m_memArea_p->index_u32] = element;

		releaseSharedMemArea();

		return retVal;
	}

	T getElement(alt_u32 negIndex, bool blocking)
	{
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;
		T element; // TODO: should return some sort of error instaed of uninitialised element
		alt_u32 index;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return element;
		}


		if(m_memArea_p->index_u32 - negIndex >= 0)
		{
			index = m_memArea_p->index_u32 - negIndex;
		}
		else
		{
			index = m_memArea_p->maxNumElements_u32 + (m_memArea_p->index_u32 - negIndex);
		}

		element = m_memArea_p->content_a[index];

		if(blocking == false)
		{
			releaseSharedMemArea();
		}

		LOG_DEBUG("get last element.");

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
	MemSharedArea<T> * m_memArea_p;

	/** getSharedMemArea
	 *
	 * \details */
	ErrCode getSharedMemArea()
	{
		bool isMine = altera_avalon_mutex_is_mine(m_mutexArea_p);

		if(!isMine)
		{
			LOG_DEBUG("locking mutex");
			altera_avalon_mutex_lock(m_mutexArea_p, 1);
		}
		else
		{
			LOG_DEBUG("mutex already mine.");
		}
		return ERR_NONE;
	}

	/** releaseSharedMemBuffer
	 *
	 * \details */
	bool releaseSharedMemArea()
	{
		bool isMine = altera_avalon_mutex_is_mine(m_mutexArea_p);

		if(isMine)
		{
			LOG_DEBUG("unlocking mutex");
			altera_avalon_mutex_unlock(m_mutexArea_p);
		}
		else
		{
			LOG_DEBUG("unlocking mutex failed, is not mine.");
		}

		return 0;
	}

};

#endif /* MEMCONTROLLER_H_ */
