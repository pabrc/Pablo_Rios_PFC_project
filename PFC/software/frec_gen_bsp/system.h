/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'NIOSIImicro'
 * SOPC Builder design path: C:/Users/Pablo/PFC/NIOSIImicro.sopcinfo
 *
 * Generated: Tue Nov 04 12:45:30 CET 2014
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
#define ALT_CPU_BREAK_ADDR 0x1000820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x19
#define ALT_CPU_DCACHE_LINE_SIZE 4
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 2
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x800020
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
#define ALT_CPU_INST_ADDR_WIDTH 0x19
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x800000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x1000820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x19
#define NIOS2_DCACHE_LINE_SIZE 4
#define NIOS2_DCACHE_LINE_SIZE_LOG2 2
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x800020
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
#define NIOS2_INST_ADDR_WIDTH 0x19
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x800000


/*
 * DM9000A configuration
 *
 */

#define ALT_MODULE_CLASS_DM9000A dm9000a
#define DM9000A_BASE 0x1001288
#define DM9000A_IRQ 6
#define DM9000A_IRQ_INTERRUPT_CONTROLLER_ID 0
#define DM9000A_NAME "/dev/DM9000A"
#define DM9000A_SPAN 8
#define DM9000A_TYPE "dm9000a"


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_LCD_16207
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS
#define __ALTPLL
#define __DM9000A


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone II"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/uart"
#define ALT_STDERR_BASE 0x1001298
#define ALT_STDERR_DEV uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/uart"
#define ALT_STDIN_BASE 0x1001298
#define ALT_STDIN_DEV uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/uart"
#define ALT_STDOUT_BASE 0x1001298
#define ALT_STDOUT_DEV uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "NIOSIImicro"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0
#define ALT_TIMESTAMP_CLK none


/*
 * lcd configuration
 *
 */

#define ALT_MODULE_CLASS_lcd altera_avalon_lcd_16207
#define LCD_BASE 0x1001180
#define LCD_IRQ -1
#define LCD_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_NAME "/dev/lcd"
#define LCD_SPAN 16
#define LCD_TYPE "altera_avalon_lcd_16207"


/*
 * pio_async_reset configuration
 *
 */

#define ALT_MODULE_CLASS_pio_async_reset altera_avalon_pio
#define PIO_ASYNC_RESET_BASE 0x10010c0
#define PIO_ASYNC_RESET_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_ASYNC_RESET_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_ASYNC_RESET_CAPTURE 0
#define PIO_ASYNC_RESET_DATA_WIDTH 1
#define PIO_ASYNC_RESET_DO_TEST_BENCH_WIRING 0
#define PIO_ASYNC_RESET_DRIVEN_SIM_VALUE 0
#define PIO_ASYNC_RESET_EDGE_TYPE "NONE"
#define PIO_ASYNC_RESET_FREQ 50000000
#define PIO_ASYNC_RESET_HAS_IN 0
#define PIO_ASYNC_RESET_HAS_OUT 1
#define PIO_ASYNC_RESET_HAS_TRI 0
#define PIO_ASYNC_RESET_IRQ -1
#define PIO_ASYNC_RESET_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_ASYNC_RESET_IRQ_TYPE "NONE"
#define PIO_ASYNC_RESET_NAME "/dev/pio_async_reset"
#define PIO_ASYNC_RESET_RESET_VALUE 0
#define PIO_ASYNC_RESET_SPAN 32
#define PIO_ASYNC_RESET_TYPE "altera_avalon_pio"


/*
 * pio_captura_0 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_captura_0 altera_avalon_pio
#define PIO_CAPTURA_0_BASE 0x10011e0
#define PIO_CAPTURA_0_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_CAPTURA_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_CAPTURA_0_CAPTURE 1
#define PIO_CAPTURA_0_DATA_WIDTH 1
#define PIO_CAPTURA_0_DO_TEST_BENCH_WIRING 0
#define PIO_CAPTURA_0_DRIVEN_SIM_VALUE 0
#define PIO_CAPTURA_0_EDGE_TYPE "RISING"
#define PIO_CAPTURA_0_FREQ 50000000
#define PIO_CAPTURA_0_HAS_IN 1
#define PIO_CAPTURA_0_HAS_OUT 0
#define PIO_CAPTURA_0_HAS_TRI 0
#define PIO_CAPTURA_0_IRQ 3
#define PIO_CAPTURA_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_CAPTURA_0_IRQ_TYPE "EDGE"
#define PIO_CAPTURA_0_NAME "/dev/pio_captura_0"
#define PIO_CAPTURA_0_RESET_VALUE 0
#define PIO_CAPTURA_0_SPAN 16
#define PIO_CAPTURA_0_TYPE "altera_avalon_pio"


/*
 * pio_captura_1 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_captura_1 altera_avalon_pio
#define PIO_CAPTURA_1_BASE 0x10011d0
#define PIO_CAPTURA_1_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_CAPTURA_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_CAPTURA_1_CAPTURE 1
#define PIO_CAPTURA_1_DATA_WIDTH 1
#define PIO_CAPTURA_1_DO_TEST_BENCH_WIRING 0
#define PIO_CAPTURA_1_DRIVEN_SIM_VALUE 0
#define PIO_CAPTURA_1_EDGE_TYPE "RISING"
#define PIO_CAPTURA_1_FREQ 50000000
#define PIO_CAPTURA_1_HAS_IN 1
#define PIO_CAPTURA_1_HAS_OUT 0
#define PIO_CAPTURA_1_HAS_TRI 0
#define PIO_CAPTURA_1_IRQ 12
#define PIO_CAPTURA_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_CAPTURA_1_IRQ_TYPE "EDGE"
#define PIO_CAPTURA_1_NAME "/dev/pio_captura_1"
#define PIO_CAPTURA_1_RESET_VALUE 0
#define PIO_CAPTURA_1_SPAN 16
#define PIO_CAPTURA_1_TYPE "altera_avalon_pio"


/*
 * pio_captura_2 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_captura_2 altera_avalon_pio
#define PIO_CAPTURA_2_BASE 0x10011c0
#define PIO_CAPTURA_2_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_CAPTURA_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_CAPTURA_2_CAPTURE 1
#define PIO_CAPTURA_2_DATA_WIDTH 1
#define PIO_CAPTURA_2_DO_TEST_BENCH_WIRING 0
#define PIO_CAPTURA_2_DRIVEN_SIM_VALUE 0
#define PIO_CAPTURA_2_EDGE_TYPE "RISING"
#define PIO_CAPTURA_2_FREQ 50000000
#define PIO_CAPTURA_2_HAS_IN 1
#define PIO_CAPTURA_2_HAS_OUT 0
#define PIO_CAPTURA_2_HAS_TRI 0
#define PIO_CAPTURA_2_IRQ 13
#define PIO_CAPTURA_2_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_CAPTURA_2_IRQ_TYPE "EDGE"
#define PIO_CAPTURA_2_NAME "/dev/pio_captura_2"
#define PIO_CAPTURA_2_RESET_VALUE 0
#define PIO_CAPTURA_2_SPAN 16
#define PIO_CAPTURA_2_TYPE "altera_avalon_pio"


/*
 * pio_captura_3 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_captura_3 altera_avalon_pio
#define PIO_CAPTURA_3_BASE 0x10011b0
#define PIO_CAPTURA_3_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_CAPTURA_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_CAPTURA_3_CAPTURE 1
#define PIO_CAPTURA_3_DATA_WIDTH 1
#define PIO_CAPTURA_3_DO_TEST_BENCH_WIRING 0
#define PIO_CAPTURA_3_DRIVEN_SIM_VALUE 0
#define PIO_CAPTURA_3_EDGE_TYPE "RISING"
#define PIO_CAPTURA_3_FREQ 50000000
#define PIO_CAPTURA_3_HAS_IN 1
#define PIO_CAPTURA_3_HAS_OUT 0
#define PIO_CAPTURA_3_HAS_TRI 0
#define PIO_CAPTURA_3_IRQ 14
#define PIO_CAPTURA_3_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_CAPTURA_3_IRQ_TYPE "EDGE"
#define PIO_CAPTURA_3_NAME "/dev/pio_captura_3"
#define PIO_CAPTURA_3_RESET_VALUE 0
#define PIO_CAPTURA_3_SPAN 16
#define PIO_CAPTURA_3_TYPE "altera_avalon_pio"


/*
 * pio_captura_4 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_captura_4 altera_avalon_pio
#define PIO_CAPTURA_4_BASE 0x10011a0
#define PIO_CAPTURA_4_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_CAPTURA_4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_CAPTURA_4_CAPTURE 1
#define PIO_CAPTURA_4_DATA_WIDTH 1
#define PIO_CAPTURA_4_DO_TEST_BENCH_WIRING 0
#define PIO_CAPTURA_4_DRIVEN_SIM_VALUE 0
#define PIO_CAPTURA_4_EDGE_TYPE "RISING"
#define PIO_CAPTURA_4_FREQ 50000000
#define PIO_CAPTURA_4_HAS_IN 1
#define PIO_CAPTURA_4_HAS_OUT 0
#define PIO_CAPTURA_4_HAS_TRI 0
#define PIO_CAPTURA_4_IRQ 15
#define PIO_CAPTURA_4_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_CAPTURA_4_IRQ_TYPE "EDGE"
#define PIO_CAPTURA_4_NAME "/dev/pio_captura_4"
#define PIO_CAPTURA_4_RESET_VALUE 0
#define PIO_CAPTURA_4_SPAN 16
#define PIO_CAPTURA_4_TYPE "altera_avalon_pio"


/*
 * pio_compara_int_0 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_compara_int_0 altera_avalon_pio
#define PIO_COMPARA_INT_0_BASE 0x1001230
#define PIO_COMPARA_INT_0_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_COMPARA_INT_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_COMPARA_INT_0_CAPTURE 1
#define PIO_COMPARA_INT_0_DATA_WIDTH 1
#define PIO_COMPARA_INT_0_DO_TEST_BENCH_WIRING 0
#define PIO_COMPARA_INT_0_DRIVEN_SIM_VALUE 0
#define PIO_COMPARA_INT_0_EDGE_TYPE "RISING"
#define PIO_COMPARA_INT_0_FREQ 50000000
#define PIO_COMPARA_INT_0_HAS_IN 1
#define PIO_COMPARA_INT_0_HAS_OUT 0
#define PIO_COMPARA_INT_0_HAS_TRI 0
#define PIO_COMPARA_INT_0_IRQ 11
#define PIO_COMPARA_INT_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_COMPARA_INT_0_IRQ_TYPE "EDGE"
#define PIO_COMPARA_INT_0_NAME "/dev/pio_compara_int_0"
#define PIO_COMPARA_INT_0_RESET_VALUE 0
#define PIO_COMPARA_INT_0_SPAN 16
#define PIO_COMPARA_INT_0_TYPE "altera_avalon_pio"


/*
 * pio_compara_int_1 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_compara_int_1 altera_avalon_pio
#define PIO_COMPARA_INT_1_BASE 0x1001220
#define PIO_COMPARA_INT_1_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_COMPARA_INT_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_COMPARA_INT_1_CAPTURE 1
#define PIO_COMPARA_INT_1_DATA_WIDTH 1
#define PIO_COMPARA_INT_1_DO_TEST_BENCH_WIRING 0
#define PIO_COMPARA_INT_1_DRIVEN_SIM_VALUE 0
#define PIO_COMPARA_INT_1_EDGE_TYPE "RISING"
#define PIO_COMPARA_INT_1_FREQ 50000000
#define PIO_COMPARA_INT_1_HAS_IN 1
#define PIO_COMPARA_INT_1_HAS_OUT 0
#define PIO_COMPARA_INT_1_HAS_TRI 0
#define PIO_COMPARA_INT_1_IRQ 7
#define PIO_COMPARA_INT_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_COMPARA_INT_1_IRQ_TYPE "EDGE"
#define PIO_COMPARA_INT_1_NAME "/dev/pio_compara_int_1"
#define PIO_COMPARA_INT_1_RESET_VALUE 0
#define PIO_COMPARA_INT_1_SPAN 16
#define PIO_COMPARA_INT_1_TYPE "altera_avalon_pio"


/*
 * pio_compara_int_2 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_compara_int_2 altera_avalon_pio
#define PIO_COMPARA_INT_2_BASE 0x1001210
#define PIO_COMPARA_INT_2_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_COMPARA_INT_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_COMPARA_INT_2_CAPTURE 1
#define PIO_COMPARA_INT_2_DATA_WIDTH 1
#define PIO_COMPARA_INT_2_DO_TEST_BENCH_WIRING 0
#define PIO_COMPARA_INT_2_DRIVEN_SIM_VALUE 0
#define PIO_COMPARA_INT_2_EDGE_TYPE "RISING"
#define PIO_COMPARA_INT_2_FREQ 50000000
#define PIO_COMPARA_INT_2_HAS_IN 1
#define PIO_COMPARA_INT_2_HAS_OUT 0
#define PIO_COMPARA_INT_2_HAS_TRI 0
#define PIO_COMPARA_INT_2_IRQ 8
#define PIO_COMPARA_INT_2_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_COMPARA_INT_2_IRQ_TYPE "EDGE"
#define PIO_COMPARA_INT_2_NAME "/dev/pio_compara_int_2"
#define PIO_COMPARA_INT_2_RESET_VALUE 0
#define PIO_COMPARA_INT_2_SPAN 16
#define PIO_COMPARA_INT_2_TYPE "altera_avalon_pio"


/*
 * pio_compara_int_3 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_compara_int_3 altera_avalon_pio
#define PIO_COMPARA_INT_3_BASE 0x1001200
#define PIO_COMPARA_INT_3_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_COMPARA_INT_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_COMPARA_INT_3_CAPTURE 1
#define PIO_COMPARA_INT_3_DATA_WIDTH 1
#define PIO_COMPARA_INT_3_DO_TEST_BENCH_WIRING 0
#define PIO_COMPARA_INT_3_DRIVEN_SIM_VALUE 0
#define PIO_COMPARA_INT_3_EDGE_TYPE "RISING"
#define PIO_COMPARA_INT_3_FREQ 50000000
#define PIO_COMPARA_INT_3_HAS_IN 1
#define PIO_COMPARA_INT_3_HAS_OUT 0
#define PIO_COMPARA_INT_3_HAS_TRI 0
#define PIO_COMPARA_INT_3_IRQ 9
#define PIO_COMPARA_INT_3_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_COMPARA_INT_3_IRQ_TYPE "EDGE"
#define PIO_COMPARA_INT_3_NAME "/dev/pio_compara_int_3"
#define PIO_COMPARA_INT_3_RESET_VALUE 0
#define PIO_COMPARA_INT_3_SPAN 16
#define PIO_COMPARA_INT_3_TYPE "altera_avalon_pio"


/*
 * pio_compara_int_4 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_compara_int_4 altera_avalon_pio
#define PIO_COMPARA_INT_4_BASE 0x10011f0
#define PIO_COMPARA_INT_4_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_COMPARA_INT_4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_COMPARA_INT_4_CAPTURE 1
#define PIO_COMPARA_INT_4_DATA_WIDTH 1
#define PIO_COMPARA_INT_4_DO_TEST_BENCH_WIRING 0
#define PIO_COMPARA_INT_4_DRIVEN_SIM_VALUE 0
#define PIO_COMPARA_INT_4_EDGE_TYPE "RISING"
#define PIO_COMPARA_INT_4_FREQ 50000000
#define PIO_COMPARA_INT_4_HAS_IN 1
#define PIO_COMPARA_INT_4_HAS_OUT 0
#define PIO_COMPARA_INT_4_HAS_TRI 0
#define PIO_COMPARA_INT_4_IRQ 10
#define PIO_COMPARA_INT_4_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_COMPARA_INT_4_IRQ_TYPE "EDGE"
#define PIO_COMPARA_INT_4_NAME "/dev/pio_compara_int_4"
#define PIO_COMPARA_INT_4_RESET_VALUE 0
#define PIO_COMPARA_INT_4_SPAN 16
#define PIO_COMPARA_INT_4_TYPE "altera_avalon_pio"


/*
 * pio_datos configuration
 *
 */

#define ALT_MODULE_CLASS_pio_datos altera_avalon_pio
#define PIO_DATOS_BASE 0x1001000
#define PIO_DATOS_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_DATOS_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_DATOS_CAPTURE 0
#define PIO_DATOS_DATA_WIDTH 32
#define PIO_DATOS_DO_TEST_BENCH_WIRING 0
#define PIO_DATOS_DRIVEN_SIM_VALUE 0
#define PIO_DATOS_EDGE_TYPE "NONE"
#define PIO_DATOS_FREQ 50000000
#define PIO_DATOS_HAS_IN 0
#define PIO_DATOS_HAS_OUT 1
#define PIO_DATOS_HAS_TRI 0
#define PIO_DATOS_IRQ -1
#define PIO_DATOS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_DATOS_IRQ_TYPE "NONE"
#define PIO_DATOS_NAME "/dev/pio_datos"
#define PIO_DATOS_RESET_VALUE 0
#define PIO_DATOS_SPAN 32
#define PIO_DATOS_TYPE "altera_avalon_pio"


/*
 * pio_direc configuration
 *
 */

#define ALT_MODULE_CLASS_pio_direc altera_avalon_pio
#define PIO_DIREC_BASE 0x1001080
#define PIO_DIREC_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_DIREC_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_DIREC_CAPTURE 0
#define PIO_DIREC_DATA_WIDTH 4
#define PIO_DIREC_DO_TEST_BENCH_WIRING 0
#define PIO_DIREC_DRIVEN_SIM_VALUE 0
#define PIO_DIREC_EDGE_TYPE "NONE"
#define PIO_DIREC_FREQ 50000000
#define PIO_DIREC_HAS_IN 0
#define PIO_DIREC_HAS_OUT 1
#define PIO_DIREC_HAS_TRI 0
#define PIO_DIREC_IRQ -1
#define PIO_DIREC_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_DIREC_IRQ_TYPE "NONE"
#define PIO_DIREC_NAME "/dev/pio_direc"
#define PIO_DIREC_RESET_VALUE 0
#define PIO_DIREC_SPAN 32
#define PIO_DIREC_TYPE "altera_avalon_pio"


/*
 * pio_direc_ram configuration
 *
 */

#define ALT_MODULE_CLASS_pio_direc_ram altera_avalon_pio
#define PIO_DIREC_RAM_BASE 0x1001060
#define PIO_DIREC_RAM_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_DIREC_RAM_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_DIREC_RAM_CAPTURE 0
#define PIO_DIREC_RAM_DATA_WIDTH 6
#define PIO_DIREC_RAM_DO_TEST_BENCH_WIRING 0
#define PIO_DIREC_RAM_DRIVEN_SIM_VALUE 0
#define PIO_DIREC_RAM_EDGE_TYPE "NONE"
#define PIO_DIREC_RAM_FREQ 50000000
#define PIO_DIREC_RAM_HAS_IN 0
#define PIO_DIREC_RAM_HAS_OUT 1
#define PIO_DIREC_RAM_HAS_TRI 0
#define PIO_DIREC_RAM_IRQ -1
#define PIO_DIREC_RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_DIREC_RAM_IRQ_TYPE "NONE"
#define PIO_DIREC_RAM_NAME "/dev/pio_direc_ram"
#define PIO_DIREC_RAM_RESET_VALUE 0
#define PIO_DIREC_RAM_SPAN 32
#define PIO_DIREC_RAM_TYPE "altera_avalon_pio"


/*
 * pio_en_mux configuration
 *
 */

#define ALT_MODULE_CLASS_pio_en_mux altera_avalon_pio
#define PIO_EN_MUX_BASE 0x10010a0
#define PIO_EN_MUX_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_EN_MUX_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_EN_MUX_CAPTURE 0
#define PIO_EN_MUX_DATA_WIDTH 1
#define PIO_EN_MUX_DO_TEST_BENCH_WIRING 0
#define PIO_EN_MUX_DRIVEN_SIM_VALUE 0
#define PIO_EN_MUX_EDGE_TYPE "NONE"
#define PIO_EN_MUX_FREQ 50000000
#define PIO_EN_MUX_HAS_IN 0
#define PIO_EN_MUX_HAS_OUT 1
#define PIO_EN_MUX_HAS_TRI 0
#define PIO_EN_MUX_IRQ -1
#define PIO_EN_MUX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_EN_MUX_IRQ_TYPE "NONE"
#define PIO_EN_MUX_NAME "/dev/pio_en_mux"
#define PIO_EN_MUX_RESET_VALUE 0
#define PIO_EN_MUX_SPAN 32
#define PIO_EN_MUX_TYPE "altera_avalon_pio"


/*
 * pio_in_32 configuration
 *
 */

#define ALT_MODULE_CLASS_pio_in_32 altera_avalon_pio
#define PIO_IN_32_BASE 0x1001190
#define PIO_IN_32_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_IN_32_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_IN_32_CAPTURE 1
#define PIO_IN_32_DATA_WIDTH 32
#define PIO_IN_32_DO_TEST_BENCH_WIRING 0
#define PIO_IN_32_DRIVEN_SIM_VALUE 0
#define PIO_IN_32_EDGE_TYPE "RISING"
#define PIO_IN_32_FREQ 50000000
#define PIO_IN_32_HAS_IN 1
#define PIO_IN_32_HAS_OUT 0
#define PIO_IN_32_HAS_TRI 0
#define PIO_IN_32_IRQ -1
#define PIO_IN_32_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_IN_32_IRQ_TYPE "NONE"
#define PIO_IN_32_NAME "/dev/pio_in_32"
#define PIO_IN_32_RESET_VALUE 0
#define PIO_IN_32_SPAN 16
#define PIO_IN_32_TYPE "altera_avalon_pio"


/*
 * pio_in_ext configuration
 *
 */

#define ALT_MODULE_CLASS_pio_in_ext altera_avalon_pio
#define PIO_IN_EXT_BASE 0x1001240
#define PIO_IN_EXT_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_IN_EXT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_IN_EXT_CAPTURE 1
#define PIO_IN_EXT_DATA_WIDTH 8
#define PIO_IN_EXT_DO_TEST_BENCH_WIRING 0
#define PIO_IN_EXT_DRIVEN_SIM_VALUE 0
#define PIO_IN_EXT_EDGE_TYPE "RISING"
#define PIO_IN_EXT_FREQ 50000000
#define PIO_IN_EXT_HAS_IN 1
#define PIO_IN_EXT_HAS_OUT 0
#define PIO_IN_EXT_HAS_TRI 0
#define PIO_IN_EXT_IRQ 4
#define PIO_IN_EXT_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_IN_EXT_IRQ_TYPE "EDGE"
#define PIO_IN_EXT_NAME "/dev/pio_in_ext"
#define PIO_IN_EXT_RESET_VALUE 0
#define PIO_IN_EXT_SPAN 16
#define PIO_IN_EXT_TYPE "altera_avalon_pio"


/*
 * pio_in_key_edge configuration
 *
 */

#define ALT_MODULE_CLASS_pio_in_key_edge altera_avalon_pio
#define PIO_IN_KEY_EDGE_BASE 0x1001250
#define PIO_IN_KEY_EDGE_BIT_CLEARING_EDGE_REGISTER 1
#define PIO_IN_KEY_EDGE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_IN_KEY_EDGE_CAPTURE 1
#define PIO_IN_KEY_EDGE_DATA_WIDTH 3
#define PIO_IN_KEY_EDGE_DO_TEST_BENCH_WIRING 0
#define PIO_IN_KEY_EDGE_DRIVEN_SIM_VALUE 0
#define PIO_IN_KEY_EDGE_EDGE_TYPE "FALLING"
#define PIO_IN_KEY_EDGE_FREQ 50000000
#define PIO_IN_KEY_EDGE_HAS_IN 1
#define PIO_IN_KEY_EDGE_HAS_OUT 0
#define PIO_IN_KEY_EDGE_HAS_TRI 0
#define PIO_IN_KEY_EDGE_IRQ 5
#define PIO_IN_KEY_EDGE_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PIO_IN_KEY_EDGE_IRQ_TYPE "EDGE"
#define PIO_IN_KEY_EDGE_NAME "/dev/pio_in_key_edge"
#define PIO_IN_KEY_EDGE_RESET_VALUE 0
#define PIO_IN_KEY_EDGE_SPAN 16
#define PIO_IN_KEY_EDGE_TYPE "altera_avalon_pio"


/*
 * pio_in_sw configuration
 *
 */

#define ALT_MODULE_CLASS_pio_in_sw altera_avalon_pio
#define PIO_IN_SW_BASE 0x1001260
#define PIO_IN_SW_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_IN_SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_IN_SW_CAPTURE 0
#define PIO_IN_SW_DATA_WIDTH 18
#define PIO_IN_SW_DO_TEST_BENCH_WIRING 0
#define PIO_IN_SW_DRIVEN_SIM_VALUE 0
#define PIO_IN_SW_EDGE_TYPE "NONE"
#define PIO_IN_SW_FREQ 50000000
#define PIO_IN_SW_HAS_IN 1
#define PIO_IN_SW_HAS_OUT 0
#define PIO_IN_SW_HAS_TRI 0
#define PIO_IN_SW_IRQ -1
#define PIO_IN_SW_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_IN_SW_IRQ_TYPE "NONE"
#define PIO_IN_SW_NAME "/dev/pio_in_sw"
#define PIO_IN_SW_RESET_VALUE 0
#define PIO_IN_SW_SPAN 16
#define PIO_IN_SW_TYPE "altera_avalon_pio"


/*
 * pio_out_ext configuration
 *
 */

#define ALT_MODULE_CLASS_pio_out_ext altera_avalon_pio
#define PIO_OUT_EXT_BASE 0x10010e0
#define PIO_OUT_EXT_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_OUT_EXT_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_OUT_EXT_CAPTURE 0
#define PIO_OUT_EXT_DATA_WIDTH 8
#define PIO_OUT_EXT_DO_TEST_BENCH_WIRING 0
#define PIO_OUT_EXT_DRIVEN_SIM_VALUE 0
#define PIO_OUT_EXT_EDGE_TYPE "NONE"
#define PIO_OUT_EXT_FREQ 50000000
#define PIO_OUT_EXT_HAS_IN 0
#define PIO_OUT_EXT_HAS_OUT 1
#define PIO_OUT_EXT_HAS_TRI 0
#define PIO_OUT_EXT_IRQ -1
#define PIO_OUT_EXT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_OUT_EXT_IRQ_TYPE "NONE"
#define PIO_OUT_EXT_NAME "/dev/pio_out_ext"
#define PIO_OUT_EXT_RESET_VALUE 0
#define PIO_OUT_EXT_SPAN 32
#define PIO_OUT_EXT_TYPE "altera_avalon_pio"


/*
 * pio_out_green configuration
 *
 */

#define ALT_MODULE_CLASS_pio_out_green altera_avalon_pio
#define PIO_OUT_GREEN_BASE 0x1001100
#define PIO_OUT_GREEN_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_OUT_GREEN_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_OUT_GREEN_CAPTURE 0
#define PIO_OUT_GREEN_DATA_WIDTH 9
#define PIO_OUT_GREEN_DO_TEST_BENCH_WIRING 0
#define PIO_OUT_GREEN_DRIVEN_SIM_VALUE 0
#define PIO_OUT_GREEN_EDGE_TYPE "NONE"
#define PIO_OUT_GREEN_FREQ 50000000
#define PIO_OUT_GREEN_HAS_IN 0
#define PIO_OUT_GREEN_HAS_OUT 1
#define PIO_OUT_GREEN_HAS_TRI 0
#define PIO_OUT_GREEN_IRQ -1
#define PIO_OUT_GREEN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_OUT_GREEN_IRQ_TYPE "NONE"
#define PIO_OUT_GREEN_NAME "/dev/pio_out_green"
#define PIO_OUT_GREEN_RESET_VALUE 0
#define PIO_OUT_GREEN_SPAN 32
#define PIO_OUT_GREEN_TYPE "altera_avalon_pio"


/*
 * pio_out_red configuration
 *
 */

#define ALT_MODULE_CLASS_pio_out_red altera_avalon_pio
#define PIO_OUT_RED_BASE 0x1001120
#define PIO_OUT_RED_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_OUT_RED_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_OUT_RED_CAPTURE 0
#define PIO_OUT_RED_DATA_WIDTH 18
#define PIO_OUT_RED_DO_TEST_BENCH_WIRING 0
#define PIO_OUT_RED_DRIVEN_SIM_VALUE 0
#define PIO_OUT_RED_EDGE_TYPE "NONE"
#define PIO_OUT_RED_FREQ 50000000
#define PIO_OUT_RED_HAS_IN 0
#define PIO_OUT_RED_HAS_OUT 1
#define PIO_OUT_RED_HAS_TRI 0
#define PIO_OUT_RED_IRQ -1
#define PIO_OUT_RED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_OUT_RED_IRQ_TYPE "NONE"
#define PIO_OUT_RED_NAME "/dev/pio_out_red"
#define PIO_OUT_RED_RESET_VALUE 0
#define PIO_OUT_RED_SPAN 32
#define PIO_OUT_RED_TYPE "altera_avalon_pio"


/*
 * pio_sel_salida configuration
 *
 */

#define ALT_MODULE_CLASS_pio_sel_salida altera_avalon_pio
#define PIO_SEL_SALIDA_BASE 0x1001020
#define PIO_SEL_SALIDA_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_SEL_SALIDA_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_SEL_SALIDA_CAPTURE 0
#define PIO_SEL_SALIDA_DATA_WIDTH 4
#define PIO_SEL_SALIDA_DO_TEST_BENCH_WIRING 0
#define PIO_SEL_SALIDA_DRIVEN_SIM_VALUE 0
#define PIO_SEL_SALIDA_EDGE_TYPE "NONE"
#define PIO_SEL_SALIDA_FREQ 50000000
#define PIO_SEL_SALIDA_HAS_IN 0
#define PIO_SEL_SALIDA_HAS_OUT 1
#define PIO_SEL_SALIDA_HAS_TRI 0
#define PIO_SEL_SALIDA_IRQ -1
#define PIO_SEL_SALIDA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_SEL_SALIDA_IRQ_TYPE "NONE"
#define PIO_SEL_SALIDA_NAME "/dev/pio_sel_salida"
#define PIO_SEL_SALIDA_RESET_VALUE 0
#define PIO_SEL_SALIDA_SPAN 32
#define PIO_SEL_SALIDA_TYPE "altera_avalon_pio"


/*
 * pio_wr configuration
 *
 */

#define ALT_MODULE_CLASS_pio_wr altera_avalon_pio
#define PIO_WR_BASE 0x1001040
#define PIO_WR_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_WR_BIT_MODIFYING_OUTPUT_REGISTER 1
#define PIO_WR_CAPTURE 0
#define PIO_WR_DATA_WIDTH 1
#define PIO_WR_DO_TEST_BENCH_WIRING 0
#define PIO_WR_DRIVEN_SIM_VALUE 0
#define PIO_WR_EDGE_TYPE "NONE"
#define PIO_WR_FREQ 50000000
#define PIO_WR_HAS_IN 0
#define PIO_WR_HAS_OUT 1
#define PIO_WR_HAS_TRI 0
#define PIO_WR_IRQ -1
#define PIO_WR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_WR_IRQ_TYPE "NONE"
#define PIO_WR_NAME "/dev/pio_wr"
#define PIO_WR_RESET_VALUE 0
#define PIO_WR_SPAN 32
#define PIO_WR_TYPE "altera_avalon_pio"


/*
 * pll configuration
 *
 */

#define ALT_MODULE_CLASS_pll altpll
#define PLL_BASE 0x1001270
#define PLL_IRQ -1
#define PLL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PLL_NAME "/dev/pll"
#define PLL_SPAN 16
#define PLL_TYPE "altpll"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x800000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x16
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 8
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 12
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 8388608
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
 * system_id configuration
 *
 */

#define ALT_MODULE_CLASS_system_id altera_avalon_sysid_qsys
#define SYSTEM_ID_BASE 0x1001290
#define SYSTEM_ID_ID 305419896
#define SYSTEM_ID_IRQ -1
#define SYSTEM_ID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSTEM_ID_NAME "/dev/system_id"
#define SYSTEM_ID_SPAN 8
#define SYSTEM_ID_TIMESTAMP 1415101208
#define SYSTEM_ID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x1001160
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000
#define TIMER_0_IRQ 0
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 4999
#define TIMER_0_MULT 1.0E-6
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 100
#define TIMER_0_PERIOD_UNITS "us"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 10000.0
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"


/*
 * timer_1 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_1 altera_avalon_timer
#define TIMER_1_ALWAYS_RUN 0
#define TIMER_1_BASE 0x1001140
#define TIMER_1_COUNTER_SIZE 32
#define TIMER_1_FIXED_PERIOD 0
#define TIMER_1_FREQ 50000000
#define TIMER_1_IRQ 1
#define TIMER_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_1_LOAD_VALUE 49999
#define TIMER_1_MULT 0.0010
#define TIMER_1_NAME "/dev/timer_1"
#define TIMER_1_PERIOD 1
#define TIMER_1_PERIOD_UNITS "ms"
#define TIMER_1_RESET_OUTPUT 0
#define TIMER_1_SNAPSHOT 1
#define TIMER_1_SPAN 32
#define TIMER_1_TICKS_PER_SEC 1000.0
#define TIMER_1_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_1_TYPE "altera_avalon_timer"


/*
 * uart configuration
 *
 */

#define ALT_MODULE_CLASS_uart altera_avalon_jtag_uart
#define UART_BASE 0x1001298
#define UART_IRQ 2
#define UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_NAME "/dev/uart"
#define UART_READ_DEPTH 64
#define UART_READ_THRESHOLD 8
#define UART_SPAN 8
#define UART_TYPE "altera_avalon_jtag_uart"
#define UART_WRITE_DEPTH 64
#define UART_WRITE_THRESHOLD 8


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
#define OS_TICKS_PER_SEC TIMER_0_TICKS_PER_SEC
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
