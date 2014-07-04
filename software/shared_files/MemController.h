/*
 * MemController.h
 *
 *  Created on: Jun 9, 2014
 *      Author: wji
 */

// TODO: place data structures in shared memory, not messages!!! car state struct!

#ifndef MEMCONTROLLER_H_
#define MEMCONTROLLER_H_

#include "altera_avalon_mutex.h"
#include "ErrHandler.h"
#include "MemSharedArea.h"


namespace c2x {

class MemController {
public:
	MemController();
	virtual ~MemController();

	enum AreaId {
		AreaId_CarState
	};

	template<typename T>
	ErrCode pushElement(MemController::AreaId areaId, T &element);

	template<typename T>
	T getLastElement(MemController::AreaId areaId);

	template<typename T>
	T getElement(MemController::AreaId areaId, alt_u32 negIndex, bool blocking);

	template<typename T>
	ErrCode getAllElements(
			MemController::AreaId areaId,
			T &elements,
			alt_u32 destSize_u32,
			alt_u32 &elementsCopied_u32);
	template<typename T> void clearElements(MemController::AreaId areaId);

private:
	template<typename T> T getLastElement(MemController::AreaId areaId, bool blocking);


	/* \brief Gets and locks a buffer located in the shared memory. This will
	 * 		  blockingly wait for the hardware mutex. Release the mutex with a
	 * 		  corresponding call to \ref releaseSharedMemBuffer()
	 * \param memArea_en identifier of shared memory buffer to query
	 * \param[out] memArea_p pointer to memory area */
	template<typename T> bool getSharedMemArea(MemController::AreaId area, MemSharedArea<T> * memArea_p);

	/* \brief releases the hardware mutex for a given buffer in shared memory
	 * \param memArea_en identifier of shared memory buffer to query */
	bool releaseSharedMemArea(MemController::AreaId area);

	// mutexes
	alt_mutex_dev * m_mutexCarState_p;

	// memory areas
	const MemSharedArea<CarState> * m_memAreaCarState_p;
};

}
#endif /* MEMCONTROLLER_H_ */
