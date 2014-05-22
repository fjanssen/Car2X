/*
 * MEM_Allocation.c
 *
 *  Created on: May 22, 2014
 *      Author: wji
 */


#include "MEM_Internal.h"
#include "COMM_Api.h"

// Physical location of shared memory buffers/areas.
// TODO: how to place them? #PRAGMA
static struct SharedMemoryArea motorSpeedShared_st = {0, 0, sizeof(MotorSpeedMsg), (void *)motorSpeedMsg_ast};
static struct SharedMemoryArea carCommandShared_st = {0, 0, sizeof(CarCommandMsg), (void *)carCommandMsg_ast};
static struct SharedMemoryArea c2xRxShared_st = {0, 0, sizeof(C2xMsg), (void *)c2xRxMsg_ast};
static struct SharedMemoryArea c2xTxShared_st = {0, 0, sizeof(C2xMsg), (void *)c2xTxMsg_ast};
static struct SharedMemoryArea usSensorShared_st = {0, 0, sizeof(UsSensorMsg), (void *)usSensorMsg_ast};


static struct MotorSpeedMsg motorSpeedMsg_ast[MEM_BUFFERLEN_MOTORSPEED];
static struct CarCommandMsg carCommandMsg_ast[MEM_BUFFERLEN_CARCOMMAND];
static struct C2xMsg c2xRxMsg_ast[MEM_BUFFERLEN_C2XRX];
static struct C2xMsg c2xTxMsg_ast[MEM_BUFFERLEN_C2XTX];
static struct UsSensorMsg usSensorMsg_ast[MEM_BUFFERLEN_USSENSOR];
