/*
* Copyright (c) 2024 hydrogenium2020-offical
* Copyright (c) 2018 naehrwert
* Copyright (c) 2018-2022 CTCaer
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

void mc_enable_ahb_redirect()
{
	CLOCK(CLK_RST_CONTROLLER_LVL2_CLK_GATE_OVRD) = CLOCK(CLK_RST_CONTROLLER_LVL2_CLK_GATE_OVRD) & 0xFFF7FFFF | 0x80000;
	//MC(MC_IRAM_REG_CTRL) &= 0xFFFFFFFE;
	MC(MC_IRAM_BOM) = 0x40000000;
	MC(MC_IRAM_TOM) = 0x4003F000;
}

void mc_enable()
{
	CLOCK(CLK_RST_CONTROLLER_CLK_SOURCE_EMC) = CLOCK(CLK_RST_CONTROLLER_CLK_SOURCE_EMC) & 0x1FFFFFFF | 0x40000000;
	//Enable MC clock.
	CLOCK(CLK_RST_CONTROLLER_CLK_ENB_H_SET) = CLOCK(CLK_RST_CONTROLLER_CLK_ENB_H_SET) & 0xFFFFFFFE | 1;
	//Enable EMC DLL clock.
	CLOCK(CLK_RST_CONTROLLER_CLK_ENB_X_SET) = CLOCK(CLK_RST_CONTROLLER_CLK_ENB_X_SET) & 0xFFFFBFFF | 0x4000;
	CLOCK(CLK_RST_CONTROLLER_RST_DEV_H_SET) = 0x2000001; //Clear EMC and MC reset.
	sleep(5);

    //Enable ahb redirect
    mc_enable_ahb_redirect();

}