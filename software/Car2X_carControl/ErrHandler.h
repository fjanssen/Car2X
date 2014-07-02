/*
 * ErrHandler.h
 *
 *  Created on: Jun 17, 2014
 *      Author: wji
 */

#ifndef ERRHANDLER_H_
#define ERRHANDLER_H_

#include <iostream>
#include <string>

#define DEBUG

// Logging Macros
#ifdef DEBUG
// if the Debug flag is set, send out logging messages over stdout via printf.
#define LOG(fmt, ...)                printf(fmt "\n", ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) \
	do {LOG("DEBUG  %s:%d : " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_INFO(fmt, ...) \
	do {LOG("INFO   %s:%d : " fmt, __FILE__, __LINE__, ##__VA_ARGS__); } while(0)
#define LOG_ERROR(errcode, fmt, ...) \
	do {LOG("ERROR  %s:%d : Error ID %d; " fmt, __FILE__, __LINE__, errcode, ##__VA_ARGS__); } while(0)
#define LOG_ERROR_RETURN(errcode, fmt, ...) \
	do {LOG_ERROR(errcode, fmt, ##__VA_ARGS__); return errcode; } while(0)
#else
// otherwise, do nothing.
#define LOG_DEBUG(fmt, ...)          (;)
#define LOG_INFO(fmt, ...)           (;)
#define LOG_ERROR(errcode, fmt, ...) (;)
#define LOG_ERROR_RETURN(errcode, fmt, ...) (return errcode;)
#endif

enum ErrCode {
	ERR_NONE = 0,
	ERR_MEM_INVALIDAREA,
	ERR_MEM_OPENMUTEX,
	ERR_MEM_ONEMUTEXATATIME,
	ERR_MEM_NOINIT,
	ERR_MEM_DESTTOOSMALL,
};

#endif /* ERRHANDLER_H_ */
