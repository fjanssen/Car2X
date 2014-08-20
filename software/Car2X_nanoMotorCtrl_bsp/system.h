/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'DE0_Nano_SOPC'
 * SOPC Builder design path: ../../hardware/DE0_Nano_SOPC_20131216.sopcinfo
 *
 * Generated: Mon Aug 18 17:43:13 CEST 2014
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
#define ALT_CPU_BREAK_ADDR 0x6000820
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x0
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1b
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x2000020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1b
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_RESET_ADDR 0x2000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x6000820
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x0
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1b
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x2000020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1b
#define NIOS2_RESET_ADDR 0x2000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __2_CHANNEL_PWM
#define __ALTERA_AVALON_EPCS_FLASH_CONTROLLER
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2
#define __ALTERA_UP_AVALON_RS232
#define __ALTPLL
#define __MOTOR_ENCODER
#define __TERASIC_ADC_READ
#define __TERASIC_SPI_3WIRE
#define __ULTRASOUND_INTERFACE


/*
 * GPIO_0 configuration
 *
 */

#define ALT_MODULE_CLASS_GPIO_0 altera_avalon_pio
#define GPIO_0_BASE 0x6001150
#define GPIO_0_BIT_CLEARING_EDGE_REGISTER 0
#define GPIO_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define GPIO_0_CAPTURE 0
#define GPIO_0_DATA_WIDTH 1
#define GPIO_0_DO_TEST_BENCH_WIRING 0
#define GPIO_0_DRIVEN_SIM_VALUE 0x0
#define GPIO_0_EDGE_TYPE "NONE"
#define GPIO_0_FREQ 100000000u
#define GPIO_0_HAS_IN 0
#define GPIO_0_HAS_OUT 1
#define GPIO_0_HAS_TRI 0
#define GPIO_0_IRQ -1
#define GPIO_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define GPIO_0_IRQ_TYPE "NONE"
#define GPIO_0_NAME "/dev/GPIO_0"
#define GPIO_0_RESET_VALUE 0x0
#define GPIO_0_SPAN 16
#define GPIO_0_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "CYCLONEIVE"
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x6001170
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x6001170
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x6001170
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "DE0_Nano_SOPC"


/*
 * Ultrasound_interface_0 configuration
 *
 */

#define ALT_MODULE_CLASS_Ultrasound_interface_0 Ultrasound_interface
#define ULTRASOUND_INTERFACE_0_BASE 0x6001120
#define ULTRASOUND_INTERFACE_0_IRQ -1
#define ULTRASOUND_INTERFACE_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ULTRASOUND_INTERFACE_0_NAME "/dev/Ultrasound_interface_0"
#define ULTRASOUND_INTERFACE_0_SPAN 16
#define ULTRASOUND_INTERFACE_0_TYPE "Ultrasound_interface"


/*
 * a_2_channel_PWM_0 configuration
 *
 */

#define ALT_MODULE_CLASS_a_2_channel_PWM_0 2_channel_PWM
#define A_2_CHANNEL_PWM_0_BASE 0x6001100
#define A_2_CHANNEL_PWM_0_IRQ -1
#define A_2_CHANNEL_PWM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define A_2_CHANNEL_PWM_0_NAME "/dev/a_2_channel_PWM_0"
#define A_2_CHANNEL_PWM_0_SPAN 32
#define A_2_CHANNEL_PWM_0_TYPE "2_channel_PWM"


/*
 * a_2_channel_PWM_1 configuration
 *
 */

#define ALT_MODULE_CLASS_a_2_channel_PWM_1 2_channel_PWM
#define A_2_CHANNEL_PWM_1_BASE 0x60010c0
#define A_2_CHANNEL_PWM_1_IRQ -1
#define A_2_CHANNEL_PWM_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define A_2_CHANNEL_PWM_1_NAME "/dev/a_2_channel_PWM_1"
#define A_2_CHANNEL_PWM_1_SPAN 32
#define A_2_CHANNEL_PWM_1_TYPE "2_channel_PWM"


/*
 * a_2_channel_PWM_2 configuration
 *
 */

#define ALT_MODULE_CLASS_a_2_channel_PWM_2 2_channel_PWM
#define A_2_CHANNEL_PWM_2_BASE 0x60010a0
#define A_2_CHANNEL_PWM_2_IRQ -1
#define A_2_CHANNEL_PWM_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define A_2_CHANNEL_PWM_2_NAME "/dev/a_2_channel_PWM_2"
#define A_2_CHANNEL_PWM_2_SPAN 32
#define A_2_CHANNEL_PWM_2_TYPE "2_channel_PWM"


/*
 * a_2_channel_PWM_3 configuration
 *
 */

#define ALT_MODULE_CLASS_a_2_channel_PWM_3 2_channel_PWM
#define A_2_CHANNEL_PWM_3_BASE 0x6001080
#define A_2_CHANNEL_PWM_3_IRQ -1
#define A_2_CHANNEL_PWM_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define A_2_CHANNEL_PWM_3_NAME "/dev/a_2_channel_PWM_3"
#define A_2_CHANNEL_PWM_3_SPAN 32
#define A_2_CHANNEL_PWM_3_TYPE "2_channel_PWM"


/*
 * a_2_channel_PWM_4 configuration
 *
 */

#define ALT_MODULE_CLASS_a_2_channel_PWM_4 2_channel_PWM
#define A_2_CHANNEL_PWM_4_BASE 0x6001060
#define A_2_CHANNEL_PWM_4_IRQ -1
#define A_2_CHANNEL_PWM_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define A_2_CHANNEL_PWM_4_NAME "/dev/a_2_channel_PWM_4"
#define A_2_CHANNEL_PWM_4_SPAN 32
#define A_2_CHANNEL_PWM_4_TYPE "2_channel_PWM"


/*
 * a_2_channel_PWM_5 configuration
 *
 */

#define ALT_MODULE_CLASS_a_2_channel_PWM_5 2_channel_PWM
#define A_2_CHANNEL_PWM_5_BASE 0x6001040
#define A_2_CHANNEL_PWM_5_IRQ -1
#define A_2_CHANNEL_PWM_5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define A_2_CHANNEL_PWM_5_NAME "/dev/a_2_channel_PWM_5"
#define A_2_CHANNEL_PWM_5_SPAN 32
#define A_2_CHANNEL_PWM_5_TYPE "2_channel_PWM"


/*
 * a_2_channel_PWM_6 configuration
 *
 */

#define ALT_MODULE_CLASS_a_2_channel_PWM_6 2_channel_PWM
#define A_2_CHANNEL_PWM_6_BASE 0x6001020
#define A_2_CHANNEL_PWM_6_IRQ -1
#define A_2_CHANNEL_PWM_6_IRQ_INTERRUPT_CONTROLLER_ID -1
#define A_2_CHANNEL_PWM_6_NAME "/dev/a_2_channel_PWM_6"
#define A_2_CHANNEL_PWM_6_SPAN 32
#define A_2_CHANNEL_PWM_6_TYPE "2_channel_PWM"


/*
 * a_2_channel_PWM_7 configuration
 *
 */

#define ALT_MODULE_CLASS_a_2_channel_PWM_7 2_channel_PWM
#define A_2_CHANNEL_PWM_7_BASE 0x6001000
#define A_2_CHANNEL_PWM_7_IRQ -1
#define A_2_CHANNEL_PWM_7_IRQ_INTERRUPT_CONTROLLER_ID -1
#define A_2_CHANNEL_PWM_7_NAME "/dev/a_2_channel_PWM_7"
#define A_2_CHANNEL_PWM_7_SPAN 32
#define A_2_CHANNEL_PWM_7_TYPE "2_channel_PWM"


/*
 * adc_spi_read configuration
 *
 */

#define ADC_SPI_READ_BASE 0x6001178
#define ADC_SPI_READ_IRQ -1
#define ADC_SPI_READ_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ADC_SPI_READ_NAME "/dev/adc_spi_read"
#define ADC_SPI_READ_SPAN 4
#define ADC_SPI_READ_TYPE "TERASIC_ADC_READ"
#define ALT_MODULE_CLASS_adc_spi_read TERASIC_ADC_READ


/*
 * altpll_sys configuration
 *
 */

#define ALTPLL_SYS_BASE 0x6001160
#define ALTPLL_SYS_IRQ -1
#define ALTPLL_SYS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ALTPLL_SYS_NAME "/dev/altpll_sys"
#define ALTPLL_SYS_SPAN 16
#define ALTPLL_SYS_TYPE "altpll"
#define ALT_MODULE_CLASS_altpll_sys altpll


/*
 * epcs configuration
 *
 */

#define ALT_MODULE_CLASS_epcs altera_avalon_epcs_flash_controller
#define EPCS_BASE 0x4000000
#define EPCS_IRQ 4
#define EPCS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define EPCS_NAME "/dev/epcs"
#define EPCS_REGISTER_OFFSET 1024
#define EPCS_SPAN 2048
#define EPCS_TYPE "altera_avalon_epcs_flash_controller"


/*
 * g_sensor_int configuration
 *
 */

#define ALT_MODULE_CLASS_g_sensor_int altera_avalon_pio
#define G_SENSOR_INT_BASE 0x5000030
#define G_SENSOR_INT_BIT_CLEARING_EDGE_REGISTER 0
#define G_SENSOR_INT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define G_SENSOR_INT_CAPTURE 1
#define G_SENSOR_INT_DATA_WIDTH 1
#define G_SENSOR_INT_DO_TEST_BENCH_WIRING 0
#define G_SENSOR_INT_DRIVEN_SIM_VALUE 0x0
#define G_SENSOR_INT_EDGE_TYPE "RISING"
#define G_SENSOR_INT_FREQ 10000000u
#define G_SENSOR_INT_HAS_IN 1
#define G_SENSOR_INT_HAS_OUT 0
#define G_SENSOR_INT_HAS_TRI 0
#define G_SENSOR_INT_IRQ 3
#define G_SENSOR_INT_IRQ_INTERRUPT_CONTROLLER_ID 0
#define G_SENSOR_INT_IRQ_TYPE "EDGE"
#define G_SENSOR_INT_NAME "/dev/g_sensor_int"
#define G_SENSOR_INT_RESET_VALUE 0x0
#define G_SENSOR_INT_SPAN 16
#define G_SENSOR_INT_TYPE "altera_avalon_pio"


/*
 * gsensor_spi configuration
 *
 */

#define ALT_MODULE_CLASS_gsensor_spi TERASIC_SPI_3WIRE
#define GSENSOR_SPI_BASE 0x4000800
#define GSENSOR_SPI_IRQ -1
#define GSENSOR_SPI_IRQ_INTERRUPT_CONTROLLER_ID -1
#define GSENSOR_SPI_NAME "/dev/gsensor_spi"
#define GSENSOR_SPI_SPAN 64
#define GSENSOR_SPI_TYPE "TERASIC_SPI_3WIRE"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * i2c_scl configuration
 *
 */

#define ALT_MODULE_CLASS_i2c_scl altera_avalon_pio
#define I2C_SCL_BASE 0x4000840
#define I2C_SCL_BIT_CLEARING_EDGE_REGISTER 0
#define I2C_SCL_BIT_MODIFYING_OUTPUT_REGISTER 0
#define I2C_SCL_CAPTURE 0
#define I2C_SCL_DATA_WIDTH 1
#define I2C_SCL_DO_TEST_BENCH_WIRING 0
#define I2C_SCL_DRIVEN_SIM_VALUE 0x0
#define I2C_SCL_EDGE_TYPE "NONE"
#define I2C_SCL_FREQ 50000000u
#define I2C_SCL_HAS_IN 0
#define I2C_SCL_HAS_OUT 1
#define I2C_SCL_HAS_TRI 0
#define I2C_SCL_IRQ -1
#define I2C_SCL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define I2C_SCL_IRQ_TYPE "NONE"
#define I2C_SCL_NAME "/dev/i2c_scl"
#define I2C_SCL_RESET_VALUE 0x1
#define I2C_SCL_SPAN 16
#define I2C_SCL_TYPE "altera_avalon_pio"


/*
 * i2c_sda configuration
 *
 */

#define ALT_MODULE_CLASS_i2c_sda altera_avalon_pio
#define I2C_SDA_BASE 0x4000850
#define I2C_SDA_BIT_CLEARING_EDGE_REGISTER 0
#define I2C_SDA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define I2C_SDA_CAPTURE 0
#define I2C_SDA_DATA_WIDTH 1
#define I2C_SDA_DO_TEST_BENCH_WIRING 0
#define I2C_SDA_DRIVEN_SIM_VALUE 0x0
#define I2C_SDA_EDGE_TYPE "NONE"
#define I2C_SDA_FREQ 50000000u
#define I2C_SDA_HAS_IN 0
#define I2C_SDA_HAS_OUT 0
#define I2C_SDA_HAS_TRI 1
#define I2C_SDA_IRQ -1
#define I2C_SDA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define I2C_SDA_IRQ_TYPE "NONE"
#define I2C_SDA_NAME "/dev/i2c_sda"
#define I2C_SDA_RESET_VALUE 0x1
#define I2C_SDA_SPAN 16
#define I2C_SDA_TYPE "altera_avalon_pio"


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x6001170
#define JTAG_UART_IRQ 5
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * key configuration
 *
 */

#define ALT_MODULE_CLASS_key altera_avalon_pio
#define KEY_BASE 0x5000050
#define KEY_BIT_CLEARING_EDGE_REGISTER 0
#define KEY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEY_CAPTURE 1
#define KEY_DATA_WIDTH 2
#define KEY_DO_TEST_BENCH_WIRING 0
#define KEY_DRIVEN_SIM_VALUE 0x0
#define KEY_EDGE_TYPE "FALLING"
#define KEY_FREQ 10000000u
#define KEY_HAS_IN 1
#define KEY_HAS_OUT 0
#define KEY_HAS_TRI 0
#define KEY_IRQ 1
#define KEY_IRQ_INTERRUPT_CONTROLLER_ID 0
#define KEY_IRQ_TYPE "EDGE"
#define KEY_NAME "/dev/key"
#define KEY_RESET_VALUE 0x0
#define KEY_SPAN 16
#define KEY_TYPE "altera_avalon_pio"


/*
 * led configuration
 *
 */

#define ALT_MODULE_CLASS_led altera_avalon_pio
#define LED_BASE 0x6001140
#define LED_BIT_CLEARING_EDGE_REGISTER 0
#define LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_CAPTURE 0
#define LED_DATA_WIDTH 8
#define LED_DO_TEST_BENCH_WIRING 0
#define LED_DRIVEN_SIM_VALUE 0x0
#define LED_EDGE_TYPE "NONE"
#define LED_FREQ 100000000u
#define LED_HAS_IN 0
#define LED_HAS_OUT 1
#define LED_HAS_TRI 0
#define LED_IRQ -1
#define LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_IRQ_TYPE "NONE"
#define LED_NAME "/dev/led"
#define LED_RESET_VALUE 0x0
#define LED_SPAN 16
#define LED_TYPE "altera_avalon_pio"


/*
 * motor_encoder_0 configuration
 *
 */

#define ALT_MODULE_CLASS_motor_encoder_0 motor_encoder
#define MOTOR_ENCODER_0_BASE 0x6001130
#define MOTOR_ENCODER_0_IRQ -1
#define MOTOR_ENCODER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MOTOR_ENCODER_0_NAME "/dev/motor_encoder_0"
#define MOTOR_ENCODER_0_SPAN 16
#define MOTOR_ENCODER_0_TYPE "motor_encoder"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x2000000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO ""
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x18
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 9
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 1
#define SDRAM_SPAN 33554432
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * select_i2c_clk configuration
 *
 */

#define ALT_MODULE_CLASS_select_i2c_clk altera_avalon_pio
#define SELECT_I2C_CLK_BASE 0x5000020
#define SELECT_I2C_CLK_BIT_CLEARING_EDGE_REGISTER 0
#define SELECT_I2C_CLK_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SELECT_I2C_CLK_CAPTURE 0
#define SELECT_I2C_CLK_DATA_WIDTH 1
#define SELECT_I2C_CLK_DO_TEST_BENCH_WIRING 0
#define SELECT_I2C_CLK_DRIVEN_SIM_VALUE 0x0
#define SELECT_I2C_CLK_EDGE_TYPE "NONE"
#define SELECT_I2C_CLK_FREQ 10000000u
#define SELECT_I2C_CLK_HAS_IN 0
#define SELECT_I2C_CLK_HAS_OUT 1
#define SELECT_I2C_CLK_HAS_TRI 0
#define SELECT_I2C_CLK_IRQ -1
#define SELECT_I2C_CLK_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SELECT_I2C_CLK_IRQ_TYPE "NONE"
#define SELECT_I2C_CLK_NAME "/dev/select_i2c_clk"
#define SELECT_I2C_CLK_RESET_VALUE 0x0
#define SELECT_I2C_CLK_SPAN 16
#define SELECT_I2C_CLK_TYPE "altera_avalon_pio"


/*
 * sw configuration
 *
 */

#define ALT_MODULE_CLASS_sw altera_avalon_pio
#define SW_BASE 0x5000040
#define SW_BIT_CLEARING_EDGE_REGISTER 0
#define SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SW_CAPTURE 1
#define SW_DATA_WIDTH 4
#define SW_DO_TEST_BENCH_WIRING 0
#define SW_DRIVEN_SIM_VALUE 0x0
#define SW_EDGE_TYPE "ANY"
#define SW_FREQ 10000000u
#define SW_HAS_IN 1
#define SW_HAS_OUT 0
#define SW_HAS_TRI 0
#define SW_IRQ 2
#define SW_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SW_IRQ_TYPE "EDGE"
#define SW_NAME "/dev/sw"
#define SW_RESET_VALUE 0x0
#define SW_SPAN 16
#define SW_TYPE "altera_avalon_pio"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid
#define SYSID_BASE 0x5000060
#define SYSID_ID 0u
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1386756594u
#define SYSID_TYPE "altera_avalon_sysid"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x5000000
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 10000000u
#define TIMER_IRQ 0
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 9999ull
#define TIMER_MULT 0.0010
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "ms"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1000u
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"


/*
 * uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_uart_0 altera_up_avalon_rs232
#define UART_0_BASE 0x0
#define UART_0_IRQ 7
#define UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_0_NAME "/dev/uart_0"
#define UART_0_SPAN 8
#define UART_0_TYPE "altera_up_avalon_rs232"

#endif /* __SYSTEM_H_ */
