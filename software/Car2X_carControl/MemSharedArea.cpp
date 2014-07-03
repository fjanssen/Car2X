/*
 * MemSharedArea.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: wji
 */

#include "MemSharedArea.h"

using namespace c2x;

CarState bufferCarState[BUFFERSIZE_CARSTATE];

struct MemSharedArea<CarState> AreaCarState __attribute__ ((section (".shared.rwdata"))) =
{
		2,
		bufferCarState,
		0,
		MEM_BUFFERFLAGS_NONE
};

