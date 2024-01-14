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
#include "t124.h"
#include "clock.h"
#include "timer.h"
#include "pmc.h"
#include "printf.h"
#include "util.h"
static clk_rst_t _clock_cl_dvfs = { 0x35C, 0x364, 0, 0x1B, 0, 0 };


//I2C default parameters - TLOW: 4, THIGH: 2, DEBOUNCE: 0, FM_DIV: 26.
static const clk_rst_t _clock_i2c[] = {
	{ CLK_RST_CONTROLLER_RST_DEVICES_L, CLK_RST_CONTROLLER_CLK_OUT_ENB_L, CLK_RST_CONTROLLER_CLK_SOURCE_I2C1, 12, 0, 19 }, //20.4MHz -> 100KHz
	{ CLK_RST_CONTROLLER_RST_DEVICES_H, CLK_RST_CONTROLLER_CLK_OUT_ENB_H, CLK_RST_CONTROLLER_CLK_SOURCE_I2C2, 22, 0, 4  }, //81.6MHz -> 400KHz
	{ 0, 0, 0, 0, 0, 4  }, //81.6MHz -> 400KHz
	{ 0, 0, 0, 0, 0, 19 }, //20.4MHz -> 100KHz
	{ CLK_RST_CONTROLLER_RST_DEVICES_H, CLK_RST_CONTROLLER_CLK_OUT_ENB_H, CLK_RST_CONTROLLER_CLK_SOURCE_I2C5, 15, 0, 4  }, //81.6MHz -> 400KHz
	{ 0, 0, 0, 0, 0, 19 }  //20.4MHz -> 100KHz
};


void clock_enable(const clk_rst_t *clk)
{
	// Put clock into reset.
	CLOCK(clk->reset) = (CLOCK(clk->reset) & ~BIT(clk->index)) | BIT(clk->index);
	// Disable.
	CLOCK(clk->enable) &= ~BIT(clk->index);
	// Configure clock source if required.
	if (clk->source)
		CLOCK(clk->source) = clk->clk_div | (clk->clk_src << 29);
	// Enable.
	CLOCK(clk->enable) = (CLOCK(clk->enable) & ~BIT(clk->index)) | BIT(clk->index);
	sleep(2);

	// Take clock off reset.
	CLOCK(clk->reset) &= ~BIT(clk->index);
}

void clock_disable(const clk_rst_t *clk)
{
	// Put clock into reset.
	CLOCK(clk->reset) = (CLOCK(clk->reset) & ~BIT(clk->index)) | BIT(clk->index);
	// Disable.
	CLOCK(clk->enable) &= ~BIT(clk->index);
}

//For NS Switch
/*
 * CLK_OSC - 38.4 MHz crystal.
 * CLK_M   - 19.2 MHz (osc/2).
 * CLK_S   - 32.768 KHz (from PMIC).
 * SCLK    - 204MHz init (-> 408MHz -> OC).
 * HCLK    - 204MHz init (-> 408MHz -> OC).
 * PCLK    - 68MHz  init (-> 136MHz -> OC/4).
 */
//For P1761(Ardbeg,Fuze F1)
/*
 * CLK_OSC - 12 MHz crystal.
 * CLK_M   - 12 MHz (osc/2).
 * CLK_S   - 32.768 KHz (from PMIC).
 * SCLK    - 127.5MHz init (-> 408MHz -> OC).
 * HCLK    - 127.5MHz init (-> 408MHz -> OC).
 * PCLK    - 31.875?MHz  init (-> 136MHz -> OC/4).
 */
void config_oscillators()
{	

	CLOCK(CLK_RST_CONTROLLER_SPARE_REG0) = (CLOCK(CLK_RST_CONTROLLER_SPARE_REG0) & 0xFFFFFFF3) | 0; // Clear 3-2bit and set CLK_M_DIVISOR to 1.the 3-2bit is divisor.
	SYSCTR0(SYSCTR0_CNTFID0)             = 12000000;   // Set counter frequency. 12Mhz

	//This register is for 1 microsecond. bit7-0->DIVISOR bit15-8->DIVIDEND.So we need 1/12
	TIMER0(TIMERUS_USEC_CFG)                = 0x0B;      // For 12MHz clk_m. 	1/12 -> 0x00/0x0b
	 
	CLOCK(CLK_RST_CONTROLLER_OSC_CTRL)   = 0x80000071; // Set OSC to 12MHz and drive strength.

	PMC(APBDEV_PMC_OSC_EDPD_OVER) = (PMC(APBDEV_PMC_OSC_EDPD_OVER) & 0xFFFFFF81) | 0xE; // Set LP0 OSC drive strength.
	PMC(APBDEV_PMC_OSC_EDPD_OVER) = (PMC(APBDEV_PMC_OSC_EDPD_OVER) & 0xFFBFFFFF) | PMC_OSC_EDPD_OVER_OSC_CTRL_OVER;
	PMC(APBDEV_PMC_CNTRL2)        = (PMC(APBDEV_PMC_CNTRL2) & 0xFFFFEFFF) | PMC_CNTRL2_HOLD_CKE_LOW_EN;
	
	//Not impl in T124?Only in T210 and newer
	//PMC(APB_MISC_GP_ASDBGREG)     = (PMC(APB_MISC_GP_ASDBGREG) & 0xFCFFFFFF) | (2 << 24); // CFG2TMC_RAM_SVOP_PDP.

	CLOCK(CLK_RST_CONTROLLER_CLK_SYSTEM_RATE) = 0x00;       // Set HCLK div to 1 and PCLK div to 1.
	//CLOCK(CLK_RST_CONTROLLER_PLLMB_BASE)     &= 0xBFFFFFFF; // PLLMB disable.

	PMC(APBDEV_PMC_TSC_MULT) = (PMC(APBDEV_PMC_TSC_MULT) & 0xFFFF0000) | 0x16E0; // 0x249F = 12000000 * (16 / 32.768 kHz).

	CLOCK(CLK_RST_CONTROLLER_CLK_SOURCE_SYS)     = 0;          // Set BPMP/SCLK div to 1.
	CLOCK(CLK_RST_CONTROLLER_SCLK_BURST_POLICY)  = 0x20004444; // Set BPMP/SCLK source to Run and PLLP_OUT2 (204MHz).
	CLOCK(CLK_RST_CONTROLLER_SUPER_SCLK_DIVIDER) = 0x80000000; // Enable SUPER_SDIV to 1.
	CLOCK(CLK_RST_CONTROLLER_CLK_SYSTEM_RATE)    = 2;          // Set HCLK div to 1 and PCLK div to 3.
}

void clock_enable_cl_dvfs(){
	clock_enable(&_clock_cl_dvfs);
}
void clock_enable_i2c(u32 idx)
{
	clock_enable(&_clock_i2c[idx]);
}