/*
* Copyright (c) 2024 hydrogenium2020-offical
* Copyright (c) 2018 naehrwert
* Copyright (c) 2020 CTCaer
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

#ifndef _T124_PMC_H_
#define _T124_PMC_H_

#include "types.h"
#define APBDEV_PMC_OSC_EDPD_OVER     0x1A4

//SDRAM
#define APBDEV_PMC_VDDP_SEL 		0x1CC
#define APBDEV_PMC_DDR_PWR 			0xE8
#define APBDEV_PMC_NO_IOPOWER 		0x44
#define APBDEV_PMC_REG_SHORT 		0x2CC
#define APBDEV_PMC_DDR_CFG 			0x1D0
#define APBDEV_PMC_POR_DPD_CTRL 	0x264
#define APBDEV_PMC_IO_DPD3_REQ		0x45c
enum {
	PMC_XOFS_SHIFT = 1,
	PMC_XOFS_MASK = 0x3f << PMC_XOFS_SHIFT
};

enum {
	PMC_POR_DPD_CTRL_MEM0_ADDR0_CLK_SEL_DPD_MASK = 1 << 0,
	PMC_POR_DPD_CTRL_MEM0_ADDR1_CLK_SEL_DPD_MASK = 1 << 1,
	PMC_POR_DPD_CTRL_MEM0_HOLD_CKE_LOW_OVR_MASK = 1 << 31,
};
enum {
	PMC_DDR_CFG_PKG_MASK = 1 << 0,
	PMC_DDR_CFG_IF_MASK = 1 << 1,
	PMC_DDR_CFG_XM0_RESET_TRI_MASK = 1 << 12,
	PMC_DDR_CFG_XM0_RESET_DPDIO_MASK = 1 << 13,
};
enum {
	PMC_DDR_PWR_EMMC_MASK = 1 << 1,
	PMC_DDR_PWR_VAL_MASK = 1 << 0,
};
enum {
	PMC_NO_IOPOWER_MEM_MASK = 1 << 7,
	PMC_NO_IOPOWER_MEM_COMP_MASK = 1 << 16,
};

#endif