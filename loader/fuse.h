/*
* Copyright (c) 2023-2024 hydrogenium2020-offical
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 3, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _T124_FUSE_H_
#define _T124_FUSE_H_

//

#define FUSE_PRODUCTION_MODE 0x100
#define FUSE_SKU_INFO_0 0x110

#define FUSE_DISABLEREGPROGRAM 0x2c

//Soc frequency 
#define FUSE_CPU_SPEEDO_1_CALIB               0x12C
#define FUSE_CPU_SPEEDO_2_CALIB               0x130
#define FUSE_SOC_SPEEDO_0_CALIB               0x134
#define FUSE_SOC_SPEEDO_1_CALIB               0x138
#define FUSE_SOC_SPEEDO_2_CALIB               0x13C
#define FUSE_SOC_IDDQ_CALIB                   0x140

#define FUSE_FA 0x148

/// Security mode

// RSA Public key in PKC mode
#define FUSE_PUBLIC_KEY0                      0x164
#define FUSE_PUBLIC_KEY1                      0x168
#define FUSE_PUBLIC_KEY2                      0x16C
#define FUSE_PUBLIC_KEY3                      0x170
#define FUSE_PUBLIC_KEY4                      0x174
#define FUSE_PUBLIC_KEY5                      0x178
#define FUSE_PUBLIC_KEY6                      0x17C
#define FUSE_PUBLIC_KEY7                      0x180

#define FUSE_SECURITY_MODE 0x1A0

//Aes key used in SBK mode
#define FUSE_PRIVATE_KEY0                     0x1A4
#define FUSE_PRIVATE_KEY1                     0x1A8
#define FUSE_PRIVATE_KEY2                     0x1AC
#define FUSE_PRIVATE_KEY3                     0x1B0
#define FUSE_PRIVATE_KEY4                     0x1B4

#define FUSE_BOOT_DEVICE_INFO 0x1BC

/*! Fuse commands. */
#define FUSE_READ     0x1
#define FUSE_WRITE    0x2
#define FUSE_SENSE    0x3
#define FUSE_CMD_MASK 0x3

void dump_pkc();
void fuse_disable_program();
#endif