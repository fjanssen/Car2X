/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'com_nios' in SOPC Builder design 'nios_system'
 * SOPC Builder design path: ../../hardware/nios_system.sopcinfo
 *
 * Generated: Thu Aug 21 18:58:57 CEST 2014
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
#define ALT_CPU_BREAK_ADDR 0x8006020
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000001
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 4096
#define ALT_CPU_EXCEPTION_ADDR 0x4005020
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
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "com_nios"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x4005000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x8006020
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000001
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 4096
#define NIOS2_EXCEPTION_ADDR 0x4005020
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
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x4005000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_MUTEX
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_SGDMA
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS
#define __TRIPLE_SPEED_ETHERNET


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
#define ALT_STDERR "/dev/jtaguart_0"
#define ALT_STDERR_BASE 0x8006838
#define ALT_STDERR_DEV jtaguart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtaguart_0"
#define ALT_STDIN_BASE 0x8006838
#define ALT_STDIN_DEV jtaguart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtaguart_0"
#define ALT_STDOUT_BASE 0x8006838
#define ALT_STDOUT_DEV jtaguart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "nios_system"


/*
 * altera_iniche configuration
 *
 */

#define INCLUDE_TCP
#define INICHE_DEFAULT_IF "NOT_USED"
#define IP_FRAGMENTS


/*
 * com_memory configuration
 *
 */

#define ALT_MODULE_CLASS_com_memory altera_avalon_new_sdram_controller
#define COM_MEMORY_BASE 0x4000000
#define COM_MEMORY_CAS_LATENCY 3
#define COM_MEMORY_CONTENTS_INFO ""
#define COM_MEMORY_INIT_NOP_DELAY 0.0
#define COM_MEMORY_INIT_REFRESH_COMMANDS 2
#define COM_MEMORY_IRQ -1
#define COM_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define COM_MEMORY_IS_INITIALIZED 1
#define COM_MEMORY_NAME "/dev/com_memory"
#define COM_MEMORY_POWERUP_DELAY 200.0
#define COM_MEMORY_REFRESH_PERIOD 7.8125
#define COM_MEMORY_REGISTER_DATA_IN 1
#define COM_MEMORY_SDRAM_ADDR_WIDTH 0x18
#define COM_MEMORY_SDRAM_BANK_WIDTH 2
#define COM_MEMORY_SDRAM_COL_WIDTH 10
#define COM_MEMORY_SDRAM_DATA_WIDTH 32
#define COM_MEMORY_SDRAM_NUM_BANKS 4
#define COM_MEMORY_SDRAM_NUM_CHIPSELECTS 1
#define COM_MEMORY_SDRAM_ROW_WIDTH 12
#define COM_MEMORY_SHARED_DATA 0
#define COM_MEMORY_SIM_MODEL_BASE 0
#define COM_MEMORY_SPAN 67108864
#define COM_MEMORY_STARVATION_INDICATOR 0
#define COM_MEMORY_TRISTATE_BRIDGE_SLAVE ""
#define COM_MEMORY_TYPE "altera_avalon_new_sdram_controller"
#define COM_MEMORY_T_AC 5.5
#define COM_MEMORY_T_MRD 3
#define COM_MEMORY_T_RCD 20.0
#define COM_MEMORY_T_RFC 70.0
#define COM_MEMORY_T_RP 20.0
#define COM_MEMORY_T_WR 14.0


/*
 * com_memory configuration as viewed by ethernet_subsystem_sgdma_rx_m_write
 *
 */

#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_BASE 0x4000000
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_CAS_LATENCY 3
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_CONTENTS_INFO ""
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_INIT_NOP_DELAY 0.0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_INIT_REFRESH_COMMANDS 2
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_IRQ -1
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_IS_INITIALIZED 1
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_NAME "/dev/com_memory"
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_POWERUP_DELAY 200.0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_REFRESH_PERIOD 7.8125
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_REGISTER_DATA_IN 1
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SDRAM_ADDR_WIDTH 0x18
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SDRAM_BANK_WIDTH 2
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SDRAM_COL_WIDTH 10
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SDRAM_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SDRAM_NUM_BANKS 4
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SDRAM_NUM_CHIPSELECTS 1
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SDRAM_ROW_WIDTH 12
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SHARED_DATA 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SIM_MODEL_BASE 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_SPAN 67108864
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_STARVATION_INDICATOR 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_TRISTATE_BRIDGE_SLAVE ""
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_TYPE "altera_avalon_new_sdram_controller"
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_T_AC 5.5
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_T_MRD 3
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_T_RCD 20.0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_T_RFC 70.0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_T_RP 20.0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_M_WRITE_COM_MEMORY_T_WR 14.0


/*
 * com_memory configuration as viewed by ethernet_subsystem_sgdma_tx_m_read
 *
 */

#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_BASE 0x4000000
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_CAS_LATENCY 3
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_CONTENTS_INFO ""
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_INIT_NOP_DELAY 0.0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_INIT_REFRESH_COMMANDS 2
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_IRQ -1
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_IS_INITIALIZED 1
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_NAME "/dev/com_memory"
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_POWERUP_DELAY 200.0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_REFRESH_PERIOD 7.8125
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_REGISTER_DATA_IN 1
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SDRAM_ADDR_WIDTH 0x18
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SDRAM_BANK_WIDTH 2
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SDRAM_COL_WIDTH 10
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SDRAM_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SDRAM_NUM_BANKS 4
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SDRAM_NUM_CHIPSELECTS 1
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SDRAM_ROW_WIDTH 12
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SHARED_DATA 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SIM_MODEL_BASE 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_SPAN 67108864
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_STARVATION_INDICATOR 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_TRISTATE_BRIDGE_SLAVE ""
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_TYPE "altera_avalon_new_sdram_controller"
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_T_AC 5.5
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_T_MRD 3
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_T_RCD 20.0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_T_RFC 70.0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_T_RP 20.0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_M_READ_COM_MEMORY_T_WR 14.0


/*
 * com_timer configuration
 *
 */

#define ALT_MODULE_CLASS_com_timer altera_avalon_timer
#define COM_TIMER_ALWAYS_RUN 1
#define COM_TIMER_BASE 0x8006800
#define COM_TIMER_COUNTER_SIZE 32
#define COM_TIMER_FIXED_PERIOD 1
#define COM_TIMER_FREQ 100000000u
#define COM_TIMER_IRQ 1
#define COM_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define COM_TIMER_LOAD_VALUE 999999ull
#define COM_TIMER_MULT 0.0010
#define COM_TIMER_NAME "/dev/com_timer"
#define COM_TIMER_PERIOD 10
#define COM_TIMER_PERIOD_UNITS "ms"
#define COM_TIMER_RESET_OUTPUT 0
#define COM_TIMER_SNAPSHOT 0
#define COM_TIMER_SPAN 32
#define COM_TIMER_TICKS_PER_SEC 100u
#define COM_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define COM_TIMER_TYPE "altera_avalon_timer"


/*
 * ethernet_subsystem_descriptor_memory configuration
 *
 */

#define ALT_MODULE_CLASS_ethernet_subsystem_descriptor_memory altera_avalon_onchip_memory2
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_BASE 0x8000000
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_CONTENTS_INFO ""
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_DUAL_PORT 1
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_GUI_RAM_BLOCK_TYPE "Automatic"
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_INIT_CONTENTS_FILE "descriptor_memory"
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_INIT_MEM_CONTENT 1
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_INSTANCE_ID "NONE"
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_IRQ -1
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_NAME "/dev/ethernet_subsystem_descriptor_memory"
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_RAM_BLOCK_TYPE "Auto"
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_READ_DURING_WRITE_MODE "DONT_CARE"
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_SINGLE_CLOCK_OP 0
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_SIZE_MULTIPLE 1
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_SIZE_VALUE 8192u
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_SPAN 8192
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_TYPE "altera_avalon_onchip_memory2"
#define ETHERNET_SUBSYSTEM_DESCRIPTOR_MEMORY_WRITABLE 1


/*
 * ethernet_subsystem_sgdma_rx configuration
 *
 */

#define ALT_MODULE_CLASS_ethernet_subsystem_sgdma_rx altera_avalon_sgdma
#define ETHERNET_SUBSYSTEM_SGDMA_RX_ADDRESS_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_RX_ALWAYS_DO_MAX_BURST 1
#define ETHERNET_SUBSYSTEM_SGDMA_RX_ATLANTIC_CHANNEL_DATA_WIDTH 4
#define ETHERNET_SUBSYSTEM_SGDMA_RX_AVALON_MM_BYTE_REORDER_MODE 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_BASE 0x8005c00
#define ETHERNET_SUBSYSTEM_SGDMA_RX_BURST_DATA_WIDTH 8
#define ETHERNET_SUBSYSTEM_SGDMA_RX_BURST_TRANSFER 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_BYTES_TO_TRANSFER_DATA_WIDTH 16
#define ETHERNET_SUBSYSTEM_SGDMA_RX_CHAIN_WRITEBACK_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_RX_COMMAND_FIFO_DATA_WIDTH 104
#define ETHERNET_SUBSYSTEM_SGDMA_RX_CONTROL_DATA_WIDTH 8
#define ETHERNET_SUBSYSTEM_SGDMA_RX_CONTROL_SLAVE_ADDRESS_WIDTH 0x4
#define ETHERNET_SUBSYSTEM_SGDMA_RX_CONTROL_SLAVE_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_RX_DESCRIPTOR_READ_BURST 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_DESC_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_RX_HAS_READ_BLOCK 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_HAS_WRITE_BLOCK 1
#define ETHERNET_SUBSYSTEM_SGDMA_RX_IN_ERROR_WIDTH 6
#define ETHERNET_SUBSYSTEM_SGDMA_RX_IRQ 2
#define ETHERNET_SUBSYSTEM_SGDMA_RX_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_NAME "/dev/ethernet_subsystem_sgdma_rx"
#define ETHERNET_SUBSYSTEM_SGDMA_RX_OUT_ERROR_WIDTH 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_READ_BLOCK_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_RX_READ_BURSTCOUNT_WIDTH 4
#define ETHERNET_SUBSYSTEM_SGDMA_RX_SPAN 64
#define ETHERNET_SUBSYSTEM_SGDMA_RX_STATUS_TOKEN_DATA_WIDTH 24
#define ETHERNET_SUBSYSTEM_SGDMA_RX_STREAM_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_RX_SYMBOLS_PER_BEAT 4
#define ETHERNET_SUBSYSTEM_SGDMA_RX_TYPE "altera_avalon_sgdma"
#define ETHERNET_SUBSYSTEM_SGDMA_RX_UNALIGNED_TRANSFER 0
#define ETHERNET_SUBSYSTEM_SGDMA_RX_WRITE_BLOCK_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_RX_WRITE_BURSTCOUNT_WIDTH 4


/*
 * ethernet_subsystem_sgdma_tx configuration
 *
 */

#define ALT_MODULE_CLASS_ethernet_subsystem_sgdma_tx altera_avalon_sgdma
#define ETHERNET_SUBSYSTEM_SGDMA_TX_ADDRESS_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_TX_ALWAYS_DO_MAX_BURST 1
#define ETHERNET_SUBSYSTEM_SGDMA_TX_ATLANTIC_CHANNEL_DATA_WIDTH 4
#define ETHERNET_SUBSYSTEM_SGDMA_TX_AVALON_MM_BYTE_REORDER_MODE 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_BASE 0x8005c40
#define ETHERNET_SUBSYSTEM_SGDMA_TX_BURST_DATA_WIDTH 8
#define ETHERNET_SUBSYSTEM_SGDMA_TX_BURST_TRANSFER 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_BYTES_TO_TRANSFER_DATA_WIDTH 16
#define ETHERNET_SUBSYSTEM_SGDMA_TX_CHAIN_WRITEBACK_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_TX_COMMAND_FIFO_DATA_WIDTH 104
#define ETHERNET_SUBSYSTEM_SGDMA_TX_CONTROL_DATA_WIDTH 8
#define ETHERNET_SUBSYSTEM_SGDMA_TX_CONTROL_SLAVE_ADDRESS_WIDTH 0x4
#define ETHERNET_SUBSYSTEM_SGDMA_TX_CONTROL_SLAVE_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_TX_DESCRIPTOR_READ_BURST 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_DESC_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_TX_HAS_READ_BLOCK 1
#define ETHERNET_SUBSYSTEM_SGDMA_TX_HAS_WRITE_BLOCK 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_IN_ERROR_WIDTH 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_IRQ 3
#define ETHERNET_SUBSYSTEM_SGDMA_TX_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_NAME "/dev/ethernet_subsystem_sgdma_tx"
#define ETHERNET_SUBSYSTEM_SGDMA_TX_OUT_ERROR_WIDTH 1
#define ETHERNET_SUBSYSTEM_SGDMA_TX_READ_BLOCK_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_TX_READ_BURSTCOUNT_WIDTH 4
#define ETHERNET_SUBSYSTEM_SGDMA_TX_SPAN 64
#define ETHERNET_SUBSYSTEM_SGDMA_TX_STATUS_TOKEN_DATA_WIDTH 24
#define ETHERNET_SUBSYSTEM_SGDMA_TX_STREAM_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_TX_SYMBOLS_PER_BEAT 4
#define ETHERNET_SUBSYSTEM_SGDMA_TX_TYPE "altera_avalon_sgdma"
#define ETHERNET_SUBSYSTEM_SGDMA_TX_UNALIGNED_TRANSFER 0
#define ETHERNET_SUBSYSTEM_SGDMA_TX_WRITE_BLOCK_DATA_WIDTH 32
#define ETHERNET_SUBSYSTEM_SGDMA_TX_WRITE_BURSTCOUNT_WIDTH 4


/*
 * ethernet_subsystem_tse_mac configuration
 *
 */

#define ALT_MODULE_CLASS_ethernet_subsystem_tse_mac triple_speed_ethernet
#define ETHERNET_SUBSYSTEM_TSE_MAC_BASE 0x8005800
#define ETHERNET_SUBSYSTEM_TSE_MAC_ENABLE_MACLITE 0
#define ETHERNET_SUBSYSTEM_TSE_MAC_FIFO_WIDTH 32
#define ETHERNET_SUBSYSTEM_TSE_MAC_IRQ -1
#define ETHERNET_SUBSYSTEM_TSE_MAC_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ETHERNET_SUBSYSTEM_TSE_MAC_IS_MULTICHANNEL_MAC 0
#define ETHERNET_SUBSYSTEM_TSE_MAC_MACLITE_GIGE 0
#define ETHERNET_SUBSYSTEM_TSE_MAC_MDIO_SHARED 0
#define ETHERNET_SUBSYSTEM_TSE_MAC_NAME "/dev/ethernet_subsystem_tse_mac"
#define ETHERNET_SUBSYSTEM_TSE_MAC_NUMBER_OF_CHANNEL 1
#define ETHERNET_SUBSYSTEM_TSE_MAC_NUMBER_OF_MAC_MDIO_SHARED 1
#define ETHERNET_SUBSYSTEM_TSE_MAC_PCS 0
#define ETHERNET_SUBSYSTEM_TSE_MAC_PCS_ID 0u
#define ETHERNET_SUBSYSTEM_TSE_MAC_PCS_SGMII 0
#define ETHERNET_SUBSYSTEM_TSE_MAC_RECEIVE_FIFO_DEPTH 8192
#define ETHERNET_SUBSYSTEM_TSE_MAC_REGISTER_SHARED 0
#define ETHERNET_SUBSYSTEM_TSE_MAC_RGMII 1
#define ETHERNET_SUBSYSTEM_TSE_MAC_SPAN 1024
#define ETHERNET_SUBSYSTEM_TSE_MAC_TRANSMIT_FIFO_DEPTH 8192
#define ETHERNET_SUBSYSTEM_TSE_MAC_TYPE "triple_speed_ethernet"
#define ETHERNET_SUBSYSTEM_TSE_MAC_UNASSIGNED "unassigned"
#define ETHERNET_SUBSYSTEM_TSE_MAC_USE_MDIO 1


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK COM_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtaguart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtaguart_0 altera_avalon_jtag_uart
#define JTAGUART_0_BASE 0x8006838
#define JTAGUART_0_IRQ 0
#define JTAGUART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAGUART_0_NAME "/dev/jtaguart_0"
#define JTAGUART_0_READ_DEPTH 64
#define JTAGUART_0_READ_THRESHOLD 8
#define JTAGUART_0_SPAN 8
#define JTAGUART_0_TYPE "altera_avalon_jtag_uart"
#define JTAGUART_0_WRITE_DEPTH 64
#define JTAGUART_0_WRITE_THRESHOLD 8


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
#define OS_TICKS_PER_SEC COM_TIMER_TICKS_PER_SEC
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
