/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'carControl_nios' in SOPC Builder design 'nios_system'
 * SOPC Builder design path: ../../hardware/nios_system.sopcinfo
 *
 * Generated: Thu Aug 21 19:00:54 CEST 2014
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

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x100820
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000002
#define ALT_CPU_CPU_IMPLEMENTATION "small"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x80020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INST_ADDR_WIDTH 0x15
#define ALT_CPU_NAME "carControl_nios"
#define ALT_CPU_RESET_ADDR 0x80000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x100820
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000002
#define NIOS2_CPU_IMPLEMENTATION "small"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x80020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INST_ADDR_WIDTH 0x15
#define NIOS2_RESET_ADDR 0x80000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_MUTEX
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_NIOS2_QSYS


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtaguart_1"
#define ALT_STDERR_BASE 0x0
#define ALT_STDERR_DEV jtaguart_1
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtaguart_1"
#define ALT_STDIN_BASE 0x0
#define ALT_STDIN_DEV jtaguart_1
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtaguart_1"
#define ALT_STDOUT_BASE 0x0
#define ALT_STDOUT_DEV jtaguart_1
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "nios_system"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtaguart_1 configuration
 *
 */

#define ALT_MODULE_CLASS_jtaguart_1 altera_avalon_jtag_uart
#define JTAGUART_1_BASE 0x0
#define JTAGUART_1_IRQ 0
#define JTAGUART_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAGUART_1_NAME "/dev/jtaguart_1"
#define JTAGUART_1_READ_DEPTH 64
#define JTAGUART_1_READ_THRESHOLD 8
#define JTAGUART_1_SPAN 8
#define JTAGUART_1_TYPE "altera_avalon_jtag_uart"
#define JTAGUART_1_WRITE_DEPTH 64
#define JTAGUART_1_WRITE_THRESHOLD 8


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x80000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "Automatic"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "Auto"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 204800u
#define ONCHIP_MEMORY2_0_SPAN 204800
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * shared_memory configuration
 *
 */

#define ALT_MODULE_CLASS_shared_memory altera_avalon_onchip_memory2
#define SHARED_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define SHARED_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define SHARED_MEMORY_BASE 0x8002000
#define SHARED_MEMORY_CONTENTS_INFO ""
#define SHARED_MEMORY_DUAL_PORT 1
#define SHARED_MEMORY_GUI_RAM_BLOCK_TYPE "Automatic"
#define SHARED_MEMORY_INIT_CONTENTS_FILE "shared_memory"
#define SHARED_MEMORY_INIT_MEM_CONTENT 1
#define SHARED_MEMORY_INSTANCE_ID "NONE"
#define SHARED_MEMORY_IRQ -1
#define SHARED_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SHARED_MEMORY_NAME "/dev/shared_memory"
#define SHARED_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define SHARED_MEMORY_RAM_BLOCK_TYPE "Auto"
#define SHARED_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define SHARED_MEMORY_SINGLE_CLOCK_OP 1
#define SHARED_MEMORY_SIZE_MULTIPLE 1
#define SHARED_MEMORY_SIZE_VALUE 4096u
#define SHARED_MEMORY_SPAN 4096
#define SHARED_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define SHARED_MEMORY_WRITABLE 1


/*
 * shared_memory_mutex configuration
 *
 */

#define ALT_MODULE_CLASS_shared_memory_mutex altera_avalon_mutex
#define SHARED_MEMORY_MUTEX_BASE 0x8006830
#define SHARED_MEMORY_MUTEX_IRQ -1
#define SHARED_MEMORY_MUTEX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SHARED_MEMORY_MUTEX_NAME "/dev/shared_memory_mutex"
#define SHARED_MEMORY_MUTEX_OWNER_INIT 0
#define SHARED_MEMORY_MUTEX_OWNER_WIDTH 16
#define SHARED_MEMORY_MUTEX_SPAN 8
#define SHARED_MEMORY_MUTEX_TYPE "altera_avalon_mutex"
#define SHARED_MEMORY_MUTEX_VALUE_INIT 0
#define SHARED_MEMORY_MUTEX_VALUE_WIDTH 16

#endif /* __SYSTEM_H_ */
