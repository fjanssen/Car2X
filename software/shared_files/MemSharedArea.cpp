/*
 * MemSharedArea.cpp
 *
 *  Created on: Jun 9, 2014
 *      Author: wji
 */

#include "MemSharedArea.h"

CarState AreaCarStateBuffer[BUFFERSIZE_CARSTATE] __attribute__ ((section (".shared_memory")));

struct MemSharedArea<CarState> AreaCarState __attribute__ ((section (".shared_memory")));

