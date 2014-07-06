/*
 * MemSharedArea.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: wji
 */

#include "MemSharedArea.h"

CarState bufferCarState[BUFFERSIZE_CARSTATE] __attribute__ ((section (".shared_memory")));

struct MemSharedArea<CarState> AreaCarState __attribute__ ((section (".shared_memory"))) =
{
		BUFFERSIZE_CARSTATE,
		bufferCarState,
		0,
		MEM_BUFFERFLAGS_NONE
};

