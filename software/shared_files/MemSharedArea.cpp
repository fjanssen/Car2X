/*********************************************************************
 *
 * Shared Memory Areas
 * 
 * \brief definitions of the actual shared memory areas. Note that the
 *     __attribute__ ((section (".shared_memory"))) places these variables
 *     into the shared memory region.
 *
 * \author Johannes <jwindelen@gmail.com>
 * 
 *********************************************************************/

#include "MemSharedArea.h"

// allocate memory for area contents
CarState AreaCarStateBuffer[BUFFERSIZE_CARSTATE] __attribute__ ((section (".shared_memory")));

// allocate area container
struct MemSharedArea<CarState> AreaCarState __attribute__ ((section (".shared_memory"))) = {
    BUFFERSIZE_CARSTATE,
    AreaCarStateBuffer,
    0,
    MEM_BUFFERFLAGS_NONE,
};
