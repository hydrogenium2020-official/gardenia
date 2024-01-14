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
#include "types.h"

/*! Generic clock descriptor. */
typedef struct _clk_rst_t
{
	u16 reset;
	u16 enable;
	u16 source;
	u8 index;
	u8 clk_src;
	u8 clk_div;
} clk_rst_t;

#define CLK_RST_CONTROLLER_CLK_SOURCE_EMC 0x19c
#define CLK_RST_CONTROLLER_CLK_ENB_H_SET 0x328
#define CLK_RST_CONTROLLER_CLK_ENB_X_SET 0x284
#define CLK_RST_CONTROLLER_RST_DEV_H_SET 0x308
#define CLK_RST_CONTROLLER_SPARE_REG0 0x55c
#define CLK_RST_CONTROLLER_OSC_CTRL 0x50
#define CLK_RST_CONTROLLER_CLK_SYSTEM_RATE 0x30
#define CLK_RST_CONTROLLER_CLK_SOURCE_SYS 0x400
#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY 0x28
#define CLK_RST_CONTROLLER_SUPER_SCLK_DIVIDER 0x2c
//I2C
#define CLK_RST_CONTROLLER_RST_DEVICES_L 0x4
#define CLK_RST_CONTROLLER_RST_DEVICES_H 0x8
#define CLK_RST_CONTROLLER_RST_DEVICES_U 0xC

#define CLK_RST_CONTROLLER_CLK_SOURCE_I2C2 0x198
#define CLK_RST_CONTROLLER_CLK_OUT_ENB_H 0x14
#define CLK_RST_CONTROLLER_CLK_SOURCE_I2C1 0x124
#define CLK_RST_CONTROLLER_CLK_SOURCE_I2C5 0x128
#define CLK_RST_CONTROLLER_CLK_OUT_ENB_L 0x10
void clock_enable(const clk_rst_t *clk);
void clock_disable(const clk_rst_t *clk);
void clock_enable_cl_dvfs();
void clock_enable_i2c(u32 idx);

void config_oscillators();