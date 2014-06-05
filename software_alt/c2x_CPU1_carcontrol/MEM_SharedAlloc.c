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
static struct SharedMemoryArea m_memAreaMotorSpeed_st = {
		sizeof(motorSpeedMsg_ast),
		sizeof(struct MotorSpeedMsg),
		(void *)motorSpeedMsg_ast,
		0,
		MEM_BUFFERFLAGS_NONE
};
static struct SharedMemoryArea m_memAreaCarCommand_st = {
		sizeof(carCommandMsg_ast),
		sizeof(struct CarCommandMsg),
		(void *)carCommandMsg_ast,
		0,
		MEM_BUFFERFLAGS_NONE
};
static struct SharedMemoryArea m_memAreaC2xRx_st = {
		sizeof(c2xRxMsg_ast),
		sizeof(struct C2xMsg),
		(void *)c2xRxMsg_ast,
		0,
		MEM_BUFFERFLAGS_NONE
};
static struct SharedMemoryArea m_memAreaC2xTx_st = {
		sizeof(c2xTxMsg_ast),
		sizeof(struct C2xMsg),
		(void *)c2xTxMsg_ast,
		0,
		MEM_BUFFERFLAGS_NONE
};
static struct SharedMemoryArea m_memAreaUsSensor_st = {
		sizeof(usSensorMsg_ast),
		sizeof(struct UsSensorMsg),
		(void *)usSensorMsg_ast,
		0,
		MEM_BUFFERFLAGS_NONE
};

static struct MotorSpeedMsg motorSpeedMsg_ast[MEM_BUFFERLEN_MOTORSPEED];
static struct CarCommandMsg carCommandMsg_ast[MEM_BUFFERLEN_CARCOMMAND];
static struct C2xMsg c2xRxMsg_ast[MEM_BUFFERLEN_C2XRX];
static struct C2xMsg c2xTxMsg_ast[MEM_BUFFERLEN_C2XTX];
static struct UsSensorMsg usSensorMsg_ast[MEM_BUFFERLEN_USSENSOR];
