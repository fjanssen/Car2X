/*********************************************************************
 *
 * Shared Memory Areas
 * 
 * \brief this is the definition for the "shared memory areas" that
 *     reside in the shared memory.
 *
 * \details
 *     please do not use these direcly, instead access them through
 *     a MemController instance pointing to the correct shared memory
 *     area.
 *
 * \author Johannes <jwindelen@gmail.com>
 * 
 *********************************************************************/

#ifndef MEMSHAREDAREA_H_
#define MEMSHAREDAREA_H_
/* ===================================================================
 * Includes
 * ==================================================================*/
#include <stdint.h>
#include "CarState.h"

/* ===================================================================
 * Configuration defines
 * ==================================================================*/
#define BUFFERSIZE_CARSTATE (10u)

/* ===================================================================
 * Enums
 * ==================================================================*/
enum Bufferflags {
	MEM_BUFFERFLAGS_NONE,
};

/* ===================================================================
 * Struct
 * ==================================================================*/
// TODO: all but the index and flags should be const!
template<typename T>
struct MemSharedArea {
	alt_u32 maxNumElements_u32;
	T * content_a;
	alt_u32 index_u32;
	enum Bufferflags flags_u32;
};

/* ===================================================================
 * Extern references for actual shared memory areas.
 * ==================================================================*/
extern struct MemSharedArea<CarState> AreaCarState;
extern CarState AreaCarStateBuffer[BUFFERSIZE_CARSTATE];



#endif /* MEMSHAREDAREA_H_ */
