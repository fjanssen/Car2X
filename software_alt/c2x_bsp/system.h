/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'CPU0' in SOPC Builder design 'DE2_115_SOPC'
 * SOPC Builder design path: C:/Users/wji/car2x/repo/hardware/DE2_115_SOPC.sopcinfo
 *
 * Generated: Mon May 19 17:43:00 CEST 2014
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

#define ALT_CPU_ARCHITECTURE "altera_nios2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x42820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x0
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x13
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x20020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x13
#define ALT_CPU_NAME "CPU0"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x20000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x42820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x0
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x13
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
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
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x13
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x20000


/*
 * CPU0_JTAG_UART configuration
 *
 */

#define ALT_MODULE_CLASS_CPU0_JTAG_UART altera_avalon_jtag_uart
#define CPU0_JTAG_UART_BASE 0x43020
#define CPU0_JTAG_UART_IRQ 0
#define CPU0_JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define CPU0_JTAG_UART_NAME "/dev/CPU0_JTAG_UART"
#define CPU0_JTAG_UART_READ_DEPTH 64
#define CPU0_JTAG_UART_READ_THRESHOLD 8
#define CPU0_JTAG_UART_SPAN 8
#define CPU0_JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define CPU0_JTAG_UART_WRITE_DEPTH 64
#define CPU0_JTAG_UART_WRITE_THRESHOLD 8


/*
 * CPU0_memory configuration
 *
 */

#define ALT_MODULE_CLASS_CPU0_memory altera_avalon_onchip_memory2
#define CPU0_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define CPU0_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define CPU0_MEMORY_BASE 0x20000
#define CPU0_MEMORY_CONTENTS_INFO ""
#define CPU0_MEMORY_DUAL_PORT 0
#define CPU0_MEMORY_GUI_RAM_BLOCK_TYPE "Automatic"
#define CPU0_MEMORY_INIT_CONTENTS_FILE "CPU0_memory"
#define CPU0_MEMORY_INIT_MEM_CONTENT 1
#define CPU0_MEMORY_INSTANCE_ID "NONE"
#define CPU0_MEMORY_IRQ -1
#define CPU0_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CPU0_MEMORY_NAME "/dev/CPU0_memory"
#define CPU0_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define CPU0_MEMORY_RAM_BLOCK_TYPE "Auto"
#define CPU0_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define CPU0_MEMORY_SINGLE_CLOCK_OP 0
#define CPU0_MEMORY_SIZE_MULTIPLE 1
#define CPU0_MEMORY_SIZE_VALUE 131072u
#define CPU0_MEMORY_SPAN 131072
#define CPU0_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define CPU0_MEMORY_WRITABLE 1


/*
 * Comms_memory configuration
 *
 */

#define ALT_MODULE_CLASS_Comms_memory altera_avalon_onchip_memory2
#define COMMS_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define COMMS_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define COMMS_MEMORY_BASE 0x41000
#define COMMS_MEMORY_CONTENTS_INFO ""
#define COMMS_MEMORY_DUAL_PORT 0
#define COMMS_MEMORY_GUI_RAM_BLOCK_TYPE "Automatic"
#define COMMS_MEMORY_INIT_CONTENTS_FILE "Comms_memory"
#define COMMS_MEMORY_INIT_MEM_CONTENT 1
#define COMMS_MEMORY_INSTANCE_ID "NONE"
#define COMMS_MEMORY_IRQ -1
#define COMMS_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define COMMS_MEMORY_NAME "/dev/Comms_memory"
#define COMMS_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define COMMS_MEMORY_RAM_BLOCK_TYPE "Auto"
#define COMMS_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define COMMS_MEMORY_SINGLE_CLOCK_OP 0
#define COMMS_MEMORY_SIZE_MULTIPLE 1
#define COMMS_MEMORY_SIZE_VALUE 4096u
#define COMMS_MEMORY_SPAN 4096
#define COMMS_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define COMMS_MEMORY_WRITABLE 1


/*
 * Comms_mutex_rx configuration
 *
 */

#define ALT_MODULE_CLASS_Comms_mutex_rx altera_avalon_mutex
#define COMMS_MUTEX_RX_BASE 0x43018
#define COMMS_MUTEX_RX_IRQ -1
#define COMMS_MUTEX_RX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define COMMS_MUTEX_RX_NAME "/dev/Comms_mutex_rx"
#define COMMS_MUTEX_RX_OWNER_INIT 0
#define COMMS_MUTEX_RX_OWNER_WIDTH 16
#define COMMS_MUTEX_RX_SPAN 8
#define COMMS_MUTEX_RX_TYPE "altera_avalon_mutex"
#define COMMS_MUTEX_RX_VALUE_INIT 0
#define COMMS_MUTEX_RX_VALUE_WIDTH 16


/*
 * Comms_mutex_tx configuration
 *
 */

#define ALT_MODULE_CLASS_Comms_mutex_tx altera_avalon_mutex
#define COMMS_MUTEX_TX_BASE 0x43010
#define COMMS_MUTEX_TX_IRQ -1
#define COMMS_MUTEX_TX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define COMMS_MUTEX_TX_NAME "/dev/Comms_mutex_tx"
#define COMMS_MUTEX_TX_OWNER_INIT 0
#define COMMS_MUTEX_TX_OWNER_WIDTH 16
#define COMMS_MUTEX_TX_SPAN 8
#define COMMS_MUTEX_TX_TYPE "altera_avalon_mutex"
#define COMMS_MUTEX_TX_VALUE_INIT 0
#define COMMS_MUTEX_TX_VALUE_WIDTH 16


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_MUTEX
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "CYCLONEIVE"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/CPU0_JTAG_UART"
#define ALT_STDERR_BASE 0x43020
#define ALT_STDERR_DEV CPU0_JTAG_UART
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/CPU0_JTAG_UART"
#define ALT_STDIN_BASE 0x43020
#define ALT_STDIN_DEV CPU0_JTAG_UART
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/CPU0_JTAG_UART"
#define ALT_STDOUT_BASE 0x43020
#define ALT_STDOUT_DEV CPU0_JTAG_UART
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "DE2_115_SOPC"


/*
 * altera_iniche configuration
 *
 */

#define DHCP_CLIENT
#define INCLUDE_TCP
#define INICHE_DEFAULT_IF "NOT_USED"
#define IP_FRAGMENTS


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * pio_LED configuration
 *
 */

#define ALT_MODULE_CLASS_pio_LED altera_avalon_pio
#define PIO_LED_BASE 0x43000
#define PIO_LED_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_LED_CAPTURE 0
#define PIO_LED_DATA_WIDTH 8
#define PIO_LED_DO_TEST_BENCH_WIRING 0
#define PIO_LED_DRIVEN_SIM_VALUE 0x0
#define PIO_LED_EDGE_TYPE "NONE"
#define PIO_LED_FREQ 50000000u
#define PIO_LED_HAS_IN 0
#define PIO_LED_HAS_OUT 1
#define PIO_LED_HAS_TRI 0
#define PIO_LED_IRQ -1
#define PIO_LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_LED_IRQ_TYPE "NONE"
#define PIO_LED_NAME "/dev/pio_LED"
#define PIO_LED_RESET_VALUE 0x0
#define PIO_LED_SPAN 16
#define PIO_LED_TYPE "altera_avalon_pio"


/*
 * ucosii configuration
 *
 */

#define OS_ARG_CHK_EN 1
#define OS_CPU_HOOKS_EN 1
#define OS_DEBUG_EN 1
#define OS_EVENT_NAME_SIZE 32
#define OS_FLAGS_NBITS 16
#define OS_FLAG_ACCEPT_EN 1
#define OS_FLAG_DEL_EN 1
#define OS_FLAG_EN 1
#define OS_FLAG_NAME_SIZE 32
#define OS_FLAG_QUERY_EN 1
#define OS_FLAG_WAIT_CLR_EN 1
#define OS_LOWEST_PRIO 20
#define OS_MAX_EVENTS 60
#define OS_MAX_FLAGS 20
#define OS_MAX_MEM_PART 60
#define OS_MAX_QS 20
#define OS_MAX_TASKS 10
#define OS_MBOX_ACCEPT_EN 1
#define OS_MBOX_DEL_EN 1
#define OS_MBOX_EN 1
#define OS_MBOX_POST_EN 1
#define OS_MBOX_POST_OPT_EN 1
#define OS_MBOX_QUERY_EN 1
#define OS_MEM_EN 1
#define OS_MEM_NAME_SIZE 32
#define OS_MEM_QUERY_EN 1
#define OS_MUTEX_ACCEPT_EN 1
#define OS_MUTEX_DEL_EN 1
#define OS_MUTEX_EN 1
#define OS_MUTEX_QUERY_EN 1
#define OS_Q_ACCEPT_EN 1
#define OS_Q_DEL_EN 1
#define OS_Q_EN 1
#define OS_Q_FLUSH_EN 1
#define OS_Q_POST_EN 1
#define OS_Q_POST_FRONT_EN 1
#define OS_Q_POST_OPT_EN 1
#define OS_Q_QUERY_EN 1
#define OS_SCHED_LOCK_EN 1
#define OS_SEM_ACCEPT_EN 1
#define OS_SEM_DEL_EN 1
#define OS_SEM_EN 1
#define OS_SEM_QUERY_EN 1
#define OS_SEM_SET_EN 1
#define OS_TASK_CHANGE_PRIO_EN 1
#define OS_TASK_CREATE_EN 1
#define OS_TASK_CREATE_EXT_EN 1
#define OS_TASK_DEL_EN 1
#define OS_TASK_IDLE_STK_SIZE 512
#define OS_TASK_NAME_SIZE 32
#define OS_TASK_PROFILE_EN 1
#define OS_TASK_QUERY_EN 1
#define OS_TASK_STAT_EN 1
#define OS_TASK_STAT_STK_CHK_EN 1
#define OS_TASK_STAT_STK_SIZE 512
#define OS_TASK_SUSPEND_EN 1
#define OS_TASK_SW_HOOK_EN 1
#define OS_TASK_TMR_PRIO 0
#define OS_TASK_TMR_STK_SIZE 512
#define OS_THREAD_SAFE_NEWLIB 1
#define OS_TICK_STEP_EN 1
#define OS_TIME_DLY_HMSM_EN 1
#define OS_TIME_DLY_RESUME_EN 1
#define OS_TIME_GET_SET_EN 1
#define OS_TIME_TICK_HOOK_EN 1
#define OS_TMR_CFG_MAX 16
#define OS_TMR_CFG_NAME_SIZE 16
#define OS_TMR_CFG_TICKS_PER_SEC 10
#define OS_TMR_CFG_WHEEL_SIZE 2
#define OS_TMR_EN 0

#endif /* __SYSTEM_H_ */
