/*
 * linker.h - Linker script mapping information
 *
 * Machine generated for CPU 'com_nios' in SOPC Builder design 'nios_system'
 * SOPC Builder design path: ../../hardware/nios_system.sopcinfo
 *
 * Generated: Mon Aug 18 16:05:19 CEST 2014
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __LINKER_H_
#define __LINKER_H_


/*
 * BSP controls alt_load() behavior in crt0.
 *
 */

#define ALT_LOAD_EXPLICITLY_CONTROLLED


/*
 * Base address and span (size in bytes) of each linker region
 *
 */

#define COM_MEMORY_BEFORE_RESET_REGION_BASE 0x4000000
#define COM_MEMORY_BEFORE_RESET_REGION_SPAN 20480
#define COM_MEMORY_REGION_BASE 0x4005020
#define COM_MEMORY_REGION_SPAN 67088352
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_REGION_BASE 0x8000000
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_REGION_SPAN 8192
#define RESET_REGION_BASE 0x4005000
#define RESET_REGION_SPAN 32
#define SHARED_MEMORY_REGION_BASE 0x8002000
#define SHARED_MEMORY_REGION_SPAN 4096


/*
 * Devices associated with code sections
 *
 */

#define ALT_EXCEPTIONS_DEVICE COM_MEMORY
#define ALT_RESET_DEVICE COM_MEMORY
#define ALT_RODATA_DEVICE COM_MEMORY
#define ALT_RWDATA_DEVICE COM_MEMORY
#define ALT_TEXT_DEVICE COM_MEMORY


/*
 * Initialization code at the reset address is allowed (e.g. no external bootloader).
 *
 */

#define ALT_ALLOW_CODE_AT_RESET


/*
 * The alt_load() facility is called from crt0 to copy sections into RAM.
 *
 */

#define ALT_LOAD_COPY_RWDATA

#endif /* __LINKER_H_ */
