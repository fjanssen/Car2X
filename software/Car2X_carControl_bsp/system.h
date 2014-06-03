/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_car_controll' in SOPC Builder design 'nios_system'
 * SOPC Builder design path: C:/Users/Florian/Documents/GitHub/Car2X/hardware/nios_system.sopcinfo
 *
 * Generated: Tue Jun 03 14:56:24 CEST 2014
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
#define ALT_CPU_BREAK_ADDR 0x41820
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "small"
#define ALT_CPU_DATA_ADDR_WIDTH 0x13
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x20020
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
#define ALT_CPU_INST_ADDR_WIDTH 0x13
#define ALT_CPU_NAME "nios2_car_controll"
#define ALT_CPU_RESET_ADDR 0x20000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x41820
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "small"
#define NIOS2_DATA_ADDR_WIDTH 0x13
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x20020
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
#define NIOS2_INST_ADDR_WIDTH 0x13
#define NIOS2_RESET_ADDR 0x20000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_MUTEX
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_TIMER
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
#define ALT_STDERR "/dev/jtag_uart_carControl"
#define ALT_STDERR_BASE 0x42000
#define ALT_STDERR_DEV jtag_uart_carControl
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_carControl"
#define ALT_STDIN_BASE 0x42000
#define ALT_STDIN_DEV jtag_uart_carControl
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_carControl"
#define ALT_STDOUT_BASE 0x42000
#define ALT_STDOUT_DEV jtag_uart_carControl
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
 * jtag_uart_carControl configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_carControl altera_avalon_jtag_uart
#define JTAG_UART_CARCONTROL_BASE 0x42000
#define JTAG_UART_CARCONTROL_IRQ 0
#define JTAG_UART_CARCONTROL_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_CARCONTROL_NAME "/dev/jtag_uart_carControl"
#define JTAG_UART_CARCONTROL_READ_DEPTH 64
#define JTAG_UART_CARCONTROL_READ_THRESHOLD 8
#define JTAG_UART_CARCONTROL_SPAN 8
#define JTAG_UART_CARCONTROL_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_CARCONTROL_WRITE_DEPTH 64
#define JTAG_UART_CARCONTROL_WRITE_THRESHOLD 8


/*
 * main_memory_car_controll configuration
 *
 */

#define ALT_MODULE_CLASS_main_memory_car_controll altera_avalon_onchip_memory2
#define MAIN_MEMORY_CAR_CONTROLL_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define MAIN_MEMORY_CAR_CONTROLL_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define MAIN_MEMORY_CAR_CONTROLL_BASE 0x20000
#define MAIN_MEMORY_CAR_CONTROLL_CONTENTS_INFO ""
#define MAIN_MEMORY_CAR_CONTROLL_DUAL_PORT 0
#define MAIN_MEMORY_CAR_CONTROLL_GUI_RAM_BLOCK_TYPE "Automatic"
#define MAIN_MEMORY_CAR_CONTROLL_INIT_CONTENTS_FILE "main_memory_car_controll"
#define MAIN_MEMORY_CAR_CONTROLL_INIT_MEM_CONTENT 1
#define MAIN_MEMORY_CAR_CONTROLL_INSTANCE_ID "NONE"
#define MAIN_MEMORY_CAR_CONTROLL_IRQ -1
#define MAIN_MEMORY_CAR_CONTROLL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MAIN_MEMORY_CAR_CONTROLL_NAME "/dev/main_memory_car_controll"
#define MAIN_MEMORY_CAR_CONTROLL_NON_DEFAULT_INIT_FILE_ENABLED 0
#define MAIN_MEMORY_CAR_CONTROLL_RAM_BLOCK_TYPE "Auto"
#define MAIN_MEMORY_CAR_CONTROLL_READ_DURING_WRITE_MODE "DONT_CARE"
#define MAIN_MEMORY_CAR_CONTROLL_SINGLE_CLOCK_OP 0
#define MAIN_MEMORY_CAR_CONTROLL_SIZE_MULTIPLE 1
#define MAIN_MEMORY_CAR_CONTROLL_SIZE_VALUE 102400u
#define MAIN_MEMORY_CAR_CONTROLL_SPAN 102400
#define MAIN_MEMORY_CAR_CONTROLL_TYPE "altera_avalon_onchip_memory2"
#define MAIN_MEMORY_CAR_CONTROLL_WRITABLE 1


/*
 * mutex_shared_memory configuration
 *
 */

#define ALT_MODULE_CLASS_mutex_shared_memory altera_avalon_mutex
#define MUTEX_SHARED_MEMORY_BASE 0x43480
#define MUTEX_SHARED_MEMORY_IRQ -1
#define MUTEX_SHARED_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MUTEX_SHARED_MEMORY_NAME "/dev/mutex_shared_memory"
#define MUTEX_SHARED_MEMORY_OWNER_INIT 0
#define MUTEX_SHARED_MEMORY_OWNER_WIDTH 16
#define MUTEX_SHARED_MEMORY_SPAN 8
#define MUTEX_SHARED_MEMORY_TYPE "altera_avalon_mutex"
#define MUTEX_SHARED_MEMORY_VALUE_INIT 0
#define MUTEX_SHARED_MEMORY_VALUE_WIDTH 16


/*
 * shared_memory configuration
 *
 */

#define ALT_MODULE_CLASS_shared_memory altera_avalon_onchip_memory2
#define SHARED_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define SHARED_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define SHARED_MEMORY_BASE 0x40000
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
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 1
#define TIMER_0_BASE 0x0
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 1
#define TIMER_0_FREQ 100000000u
#define TIMER_0_IRQ 1
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 999999ull
#define TIMER_0_MULT 0.0010
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 10
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 0
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 100u
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
