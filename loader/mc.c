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
#include "clock.h"
#include "printf.h"
#include "t124.h"
#include "util.h"
#include "mc.h"

void mc_disable_ahb_redirect()
{
	MC(MC_IRAM_BOM) = 0xFFFFF000;
	MC(MC_IRAM_TOM) = 0;
	//Disable IRAM_CFG_WRITE_ACCESS (sticky).
	//MC(MC_IRAM_REG_CTRL) = MC(MC_IRAM_REG_CTRL) & 0xFFFFFFFE | 1;
	CLOCK(0x3A4) &= 0xFFF7FFFF;
}
void mc_enable()
{
	CLOCK(CLK_RST_CONTROLLER_CLK_SOURCE_EMC) = CLOCK(CLK_RST_CONTROLLER_CLK_SOURCE_EMC) & 0x1FFFFFFF | 0x40000000;
	//Enable MIPI CAL clock.
	CLOCK(CLK_RST_CONTROLLER_CLK_ENB_H_SET) = CLOCK(CLK_RST_CONTROLLER_CLK_ENB_H_SET) & 0xFDFFFFFF | 0x2000000;
	//Enable MC clock.
	CLOCK(CLK_RST_CONTROLLER_CLK_ENB_H_SET) = CLOCK(CLK_RST_CONTROLLER_CLK_ENB_H_SET) & 0xFFFFFFFE | 1;
	//Enable EMC DLL clock.
	CLOCK(CLK_RST_CONTROLLER_CLK_ENB_X_SET) = CLOCK(CLK_RST_CONTROLLER_CLK_ENB_X_SET) & 0xFFFFBFFF | 0x4000;
	CLOCK(CLK_RST_CONTROLLER_RST_DEV_H_SET) = 0x2000001; //Clear EMC and MC reset.

	//#ifdef CONFIG_ENABLE_AHB_REDIRECT
	mc_disable_ahb_redirect();


	//mc_enable_ahb_redirect();
	//#endif
}