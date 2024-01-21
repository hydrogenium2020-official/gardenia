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

#define CLK_RST_CONTROLLER_CLK_SOURCE_EMC_0 0x19c

void clock_enable(const clk_rst_t *clk);
void clock_disable(const clk_rst_t *clk);
void clock_enable_cl_dvfs();
void clock_enable_i2c(u32 idx);

void config_oscillators();