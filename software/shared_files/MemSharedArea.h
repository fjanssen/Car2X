/*
 * MemSharedArea.h
 *
 *  Created on: Jun 9, 2014
 *      Author: wji
 */

#ifndef MEMSHAREDAREA_H_
#define MEMSHAREDAREA_H_

#include <stdint.h>
#include "CarState.h"

namespace c2x {

#define BUFFERSIZE_CARSTATE (10u)

enum Bufferflags {
	MEM_BUFFERFLAGS_NONE,
};


template<typename T>
struct MemSharedArea {
	const alt_u32 maxNumElements_u32;
	T * content_a;
	alt_u32 index_u32;
	enum Bufferflags flags_u32;
};

extern struct MemSharedArea<CarState> AreaCarState;


} /* namespace c2x */

#endif /* MEMSHAREDAREA_H_ */
