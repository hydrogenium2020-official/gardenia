/*
* Copyright (c) 2024 hydrogenium2020-offical
* Copyright (c) 2018 naehrwert
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 2, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _T124_H_
#define _T124_H_
#include "types.h"

//address map for T124
#define FUSE_BASE 0x7000F800 //8k length
#define SE_BASE 0x70012000 //8k length
#define PMC_BASE 0x7000E400 //2k e400-ebff length
#define CLOCK_BASE 0x60006000
#define TIMER0_BASE 0x60005000
#define MC_BASE 0x70019000
#define SYSCTR0_BASE     0x700F0000
#define APB_MISC_BASE 0x70000000
#define PINMUX_AUX_BASE 0x70003000
#define I2C_BASE         0x7000C000
#define UART_BASE 0x70006000
#define EMC_BASE 0x7001B000
#define SYSREG_BASE 0x6000C000
#define BPMP_CACHE_BASE  0x50040000
#define IRAM_BASE        0x40000000

#define DRAM_START     0x80000000

#define MMIO_REG32(base, off) *(vu32 *)((base) + (off))

#define SE(off)                 MMIO_REG32(SE_BASE, off)
#define PMC(off)                MMIO_REG32(PMC_BASE, off)
#define FUSE(off)               MMIO_REG32(FUSE_BASE, off)
#define CLOCK(off)              MMIO_REG32(CLOCK_BASE, off)
#define TIMER0(off)             MMIO_REG32(TIMER0_BASE, off)
#define MC(off)                 MMIO_REG32(MC_BASE, off)
#define SYSCTR0(off)            MMIO_REG32(SYSCTR0_BASE, off)
#define APB_MISC(off)           MMIO_REG32(APB_MISC_BASE, off)
#define PINMUX_AUX(off)         MMIO_REG32(PINMUX_AUX_BASE, off)
#define I2C(off)                MMIO_REG32(I2C_BASE, off)
#define UART(off)               MMIO_REG32(UART_BASE, off)
#define EMC(off)                MMIO_REG32(EMC_BASE, off)
#define SYSREG(off)             MMIO_REG32(SYSREG_BASE, off)
#define BPMP_CACHE_CTRL(off)    MMIO_REG32(BPMP_CACHE_BASE, off)

//PMC
#define APBDEV_PMC_CRYPTO_OP 0xF4
#define SYSCTR0_CNTFID0 0x20

//System registers
//#define AHB_ARBITRATION_XBAR_CTRL            0xE0

//GPIO
#define APB_MISC_PP_PINMUX_GLOBAL 0x40


#endif