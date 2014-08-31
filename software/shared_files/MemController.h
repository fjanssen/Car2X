/*********************************************************************
 *
 * Memory Controller
 * 
 * \brief 
 *     The MemController Class facilitates using a shared memory
 *     from two different cores/threads. Safe accesses are guaranteed
 *     using a hardware mutex. 
 *
 * \author Johannes <jwindelen@gmail.com>
 * 
 * \details 
 *     The Memory Controller uses the shared memory content_a member
 *     as a circular buffer to push/get elements of the template type
 *     T.
 *     Since the MemController has been implemented as a template class, 
 *     it supports shared memory areas of any type. You must make sure,
 *     that the corresponding memory area has been declared in
 *     MemSharedAreas.c!
 *
 *     NB: it is very important that each core has a unique NIOS ID. 
 *     If not, the altera_avalon_mutex_is_mine() call will always 
 *     return true, even if the other core has the mutex!!
 * 
 *     NB: on function return codes: don't rely on them, they're not
 *     fully implemented unfortunately :(
 * 
 *********************************************************************/

#ifndef MEMCONTROLLER_H_
#define MEMCONTROLLER_H_

/* ===================================================================
 * Includes
 * ==================================================================*/
extern "C" {
#include "altera_avalon_mutex.h"
#include "ErrHandler.h"
#include "alt_types.h"
#include "altera_avalon_mutex.h"
#include <stdio.h>
}

#include "MemSharedArea.h"

/* ===================================================================
 * MemController
 * ==================================================================*/

template<typename T>
class MemController {
public:
    /* ===================================================================
     * Public enums/vars
     * ==================================================================*/
    /* -------------------------------------------------------------------
     * AreaId
     * 
     * \brief used to reference the different shared memory areas.
     * -----------------------------------------------------------------*/
	enum AreaId {
		AreaId_CarState
	};

    /* ===================================================================
     * Constructors/Deconstructors
     * ==================================================================*/
    /* -------------------------------------------------------------------
     * MemController
     * 
     * \brief
     *     Constructor for MemController of the CarState shared memory area.
     *     This mainly exists for backwards compatibility. Use the other
     *     constructor instead :)
     * -----------------------------------------------------------------*/
	MemController() {
        init(&AreaCarState);
	}

    /* -------------------------------------------------------------------
     * MemController
     *
     * \brief Constructor for MemController
     * \param areaId memory area to be accessed using this MemController
     *               instance. See SharedMemarea.h/c to add/remove areas
     * -----------------------------------------------------------------*/
    MemController(MemSharedArea<T> memArea) {
        init(memArea);
    }

    /* -------------------------------------------------------------------
     * init
     *
     * \brief Initialises the shared memory controller
     * -----------------------------------------------------------------*/
    void init(MemSharedArea<T> * memArea) {
		m_memArea_p = NULL;

        m_mutexArea_p = altera_avalon_mutex_open("/dev/shared_memory_mutex");
		m_memArea_p = memArea;

		if(m_memArea_p->content_a == NULL)
		{
			LOG_DEBUG("Initialising shared memory...");
			getSharedMemArea();
			m_memArea_p->index_u32 = 0;
			releaseSharedMemArea();
		}

		// make sure that all mutexes were acquired.
		if(m_mutexArea_p == NULL)
		{
			LOG_ERROR(ERR_MEM_OPENMUTEX, "Failed to acquire hardware mutex: " \
                      "@%#x", (unsigned int) m_mutexArea_p);
		}

		LOG_DEBUG("Memcontroller constructed. m_memArea_p: %#x, size: %d, index %d",
                  m_memArea_p, m_memArea_p->maxNumElements_u32, m_memArea_p->index_u32);
    }


    /* -------------------------------------------------------------------
     * ~MemController
     * -----------------------------------------------------------------*/
	~MemController() {
		altera_avalon_mutex_close(m_mutexArea_p);
	}

    /* ===================================================================
     * API Implementation
     * ==================================================================*/
    /* -------------------------------------------------------------------
     * getAll
     *
     * \brief returns all elements from the shared memory
     *
     * \param[out] elements - make sure that there is enough space to fit
     *     the entire shared memory area into elements.
     * \param[out] elementsCopied
     *
     * TODO: doesn't work with the circular buffer!
     * -----------------------------------------------------------------*/
	ErrCode getAll(
        T &elements,
        alt_u32 &elementsCopied)
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

		elementsCopied = m_memArea_p->index_u32;

		// reset element count, flags
		m_memArea_p->index_u32 = 0;
		m_memArea_p->flags_u32 = MEM_BUFFERFLAGS_NONE;

		// Release the mutex for the source memory area, this is important!!!
		releaseSharedMemArea();

		return retVal;
	}

    /* -------------------------------------------------------------------
     * clear
     *
     * \brief clears the contents of a shared memory area (writes 0s)
     * -----------------------------------------------------------------*/
	ErrCode clear() {
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(), retVal != ERR_NONE)
		{
			LOG_DEBUG("Throwing error up.");
			return retVal;
		}
        
        // set the entire contents array to 0
        memset(m_memArea_p->content_a, 0, 
               sizeof(T) * m_memArea_p->maxNumElements_u32);

        // reset index and flags
		m_memArea_p->index_u32 = 0;
		m_memArea_p->flags_u32 = MEM_BUFFERFLAGS_NONE;

        return retVal;
	}

    /* -------------------------------------------------------------------
     * push
     *
     * \brief pushes an element to the shared memory area
     *
     * \param element
     * -----------------------------------------------------------------*/
	ErrCode push(T &element) {
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;

		/* --- validation ---*/
		if(retVal = getSharedMemArea(), retVal != ERR_NONE) {
			LOG_DEBUG("Throwing error up.");
			return retVal;
		}

		// circular buffer, calculate the index to push to
		m_memArea_p->index_u32 = (m_memArea_p->index_u32 < (m_memArea_p->maxNumElements_u32 - 1)) ? 
            m_memArea_p->index_u32 + 1 : 0;

		LOG_DEBUG("push element to index %d", m_memArea_p->index_u32);
		m_memArea_p->content_a[m_memArea_p->index_u32] = element;

		releaseSharedMemArea();

		return retVal;
	}

    /* -------------------------------------------------------------------
     * get
     *
     * \brief gets an element from the shared memory area
     *
     * \param negIndex negatively indexes the shared memory area content_a
     * \param blocking keeps a lock on the mutex until released using a 
     *      push() call
     * \returns T element from the shared memory area
     * -----------------------------------------------------------------*/
	T get(alt_u32 negIndex, bool blocking)
	{
		/* --- local variables ---*/
		ErrCode retVal = ERR_NONE;
		T element; // TODO: should return some sort of error instaed of uninitialised element
		alt_u32 index;

		LOG_DEBUG("getElement, %d",blocking);
		
        /* --- validation ---*/
		if(retVal = getSharedMemArea(), retVal != ERR_NONE) {
			LOG_DEBUG("Throwing error up.");
			return element;
		}


		if(m_memArea_p->index_u32 - negIndex >= 0) {
			index = m_memArea_p->index_u32 - negIndex;
		}
		else {
			index = m_memArea_p->maxNumElements_u32 + (m_memArea_p->index_u32 - negIndex);
		}

		element = m_memArea_p->content_a[index];

		if(blocking == false) {
			releaseSharedMemArea();
		}

		return element;
	}

    /* -------------------------------------------------------------------
     * get
     *
     * \brief gets an element from the shared memory area. Overloaded call, 
     *     see details above
     * ------------------------------------------------------------------*/
	T get()	{
		return get(0, false);
	}

    /* -------------------------------------------------------------------
     * get
     *
     * \brief gets an element from the shared memory area. Overloaded call, 
     *     see details above
     * ------------------------------------------------------------------*/
	T get(bool blocking) {
		return get(0, blocking);
	}

private:
    /* ===================================================================
     * private variables
     * ==================================================================*/
	// mutex
	alt_mutex_dev * m_mutexArea_p;

	// memory area pointer
	MemSharedArea<T> * m_memArea_p;


    /* ===================================================================
     * private functions
     * ==================================================================*/
    /* -------------------------------------------------------------------
     * getSharedMemArea
     *
	 * \brief gets and locks a buffer located in the shared memory. This will
	 * 	  blockingly wait for the hardware mutex. Release the mutex with a
	 * 	  corresponding call to \ref releaseSharedMemBuffer()
     * ------------------------------------------------------------------*/
	ErrCode getSharedMemArea() {
		volatile bool isMine = altera_avalon_mutex_is_mine(m_mutexArea_p);

		LOG_DEBUG("m_mutexArea: %d",m_mutexArea_p->mutex_base);

		if(!isMine) {
			LOG_DEBUG("locking mutex");
			altera_avalon_mutex_lock(m_mutexArea_p, 1);
			LOG_DEBUG("Mutex locked!");
		}
		else {
			LOG_DEBUG("mutex already mine.");
		}

		isMine = altera_avalon_mutex_is_mine(m_mutexArea_p);
		LOG_DEBUG("isMine: %d",isMine);

		return ERR_NONE;
	}

    /* -------------------------------------------------------------------
     * releaseSharedMemArea
     *
	 * \brief unlocks the shared memory area mutex
     * ------------------------------------------------------------------*/
	ErrCode releaseSharedMemArea() {
		volatile bool isMine = altera_avalon_mutex_is_mine(m_mutexArea_p);

		if(isMine) {
			LOG_DEBUG("unlocking mutex");
			altera_avalon_mutex_unlock(m_mutexArea_p);
		}
		else {
			LOG_DEBUG("unlocking mutex failed, is not mine.");
		}

		return ERR_NONE;
	}

};

#endif /* MEMCONTROLLER_H_ */
