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
#include "types.h"

enum {
	OSC_FREQ_13 = 0,
	OSC_FREQ_16P8 = 1,
	OSC_FREQ_19P2 = 4,
	OSC_FREQ_38P4 = 5,
	OSC_FREQ_12 = 8,
	OSC_FREQ_48 = 9,
	OSC_FREQ_26 = 12
};
/* This table defines the frequency dividers for every PLL to turn the external
 * OSC clock into the frequencies defined by TEGRA_PLL*_KHZ in soc/clock.h.
 * All PLLs have three dividers (n, m and p), with the governing formula for
 * the output frequency being CF = (IN / m), VCO = CF * n and OUT = VCO / (2^p).
 * All divisor configurations must meet the PLL's constraints for VCO and CF:
 * PLLX:  12 MHz < CF < 50 MHz, 700 MHz < VCO < 3000 MHz
 * PLLC:  12 MHz < CF < 50 MHz, 600 MHz < VCO < 1400 MHz
 * PLLM:  12 MHz < CF < 50 MHz, 400 MHz < VCO < 1066 MHz
 * PLLP:   1 MHz < CF <  6 MHz, 200 MHz < VCO <  700 MHz
 * PLLD:   1 MHz < CF <  6 MHz, 500 MHz < VCO < 1000 MHz
 * PLLU:   1 MHz < CF <  6 MHz, 480 MHz < VCO <  960 MHz
 * PLLDP: 12 MHz < CF < 38 MHz, 600 MHz < VCO < 1200 MHz
 * (values taken from Linux' drivers/clk/tegra/clk-tegra124.c). */
struct {
	int khz;
	struct pllcx_dividers	pllx;	/* target:  CONFIG_PLLX_KHZ */
	struct pllcx_dividers	pllc;	/* target:  600 MHz */
	/* PLLM is set up dynamically by clock_sdram(). */
	/* PLLP is hardwired to 408 MHz in HW (unless we set BASE_OVRD). */
	struct pllu_dividers	pllu;	/* target;  960 MHz */
	struct pllcx_dividers	plldp;	/* target;  270 MHz */
	/* PLLDP treats p differently (OUT = VCO / (p + 1) for p < 6). */
} static const osc_table[16] = {
	[OSC_FREQ_12] = {
		.khz = 12000,
		.pllx = {.n = TEGRA_PLLX_KHZ / 12000, .m =  1, .p = 0},
		.pllc = {.n =  50, .m =  1, .p = 0},
		.pllu = {.n = 960, .m = 12, .p = 0, .cpcon = 12, .lfcon = 2},
		.plldp = {.n = 90, .m =  1, .p = 3},
	},
	[OSC_FREQ_13] = {
		.khz = 13000,
		.pllx = {.n = TEGRA_PLLX_KHZ / 13000, .m =  1, .p = 0},
		.pllc = {.n =  46, .m =  1, .p = 0},		 /* 598.0 MHz */
		.pllu = {.n = 960, .m = 13, .p = 0, .cpcon = 12, .lfcon = 2},
		.plldp = {.n = 83, .m =  1, .p = 3},		 /* 269.8 MHz */
	},
	[OSC_FREQ_16P8] = {
		.khz = 16800,
		.pllx = {.n = TEGRA_PLLX_KHZ / 16800, .m =  1, .p = 0},
		.pllc = {.n =  71, .m =  1, .p = 1},		 /* 596.4 MHz */
		.pllu = {.n = 400, .m =  7, .p = 0, .cpcon = 5, .lfcon = 2},
		.plldp = {.n = 64, .m =  1, .p = 3},		 /* 268.8 MHz */
	},
	[OSC_FREQ_19P2] = {
		.khz = 19200,
		.pllx = {.n = TEGRA_PLLX_KHZ / 19200, .m =  1, .p = 0},
		.pllc = {.n =  62, .m =  1, .p = 1},		 /* 595.2 MHz */
		.pllu = {.n = 200, .m =  4, .p = 0, .cpcon = 3, .lfcon = 2},
		.plldp = {.n = 56, .m =  1, .p = 3},		 /* 268.8 MHz */
	},
	[OSC_FREQ_26] = {
		.khz = 26000,
		.pllx = {.n = TEGRA_PLLX_KHZ / 26000, .m =  1, .p = 0},
		.pllc = {.n =  23, .m =  1, .p = 0},		 /* 598.0 MHz */
		.pllu = {.n = 960, .m = 26, .p = 0, .cpcon = 12, .lfcon = 2},
		.plldp = {.n = 83, .m =  2, .p = 3},		 /* 269.8 MHz */
	},
	/* These oscillators get predivided as PLL inputs... n/m/p divisors for
	 * 38.4 should always match 19.2, and 48 should always match 12. */
	[OSC_FREQ_38P4] = {
		.khz = 38400,
		.pllx = {.n = TEGRA_PLLX_KHZ / 19200, .m =  1, .p = 0},
		.pllc = {.n =  62, .m =  1, .p = 1},		 /* 595.2 MHz */
		.pllu = {.n = 200, .m =  4, .p = 0, .cpcon = 3, .lfcon = 2},
		.plldp = {.n = 56, .m =  1, .p = 3},		 /* 268.8 MHz */
	},
	[OSC_FREQ_48] = {
		.khz = 48000,
		.pllx = {.n = TEGRA_PLLX_KHZ / 12000, .m =  1, .p = 0},
		.pllc = {.n =  50, .m =  1, .p = 0},
		.pllu = {.n = 960, .m = 12, .p = 0, .cpcon = 12, .lfcon = 2},
		.plldp = {.n = 90, .m =  1, .p = 3},
	},
};
enum {
	SCLK_SYS_STATE_STDBY,
	SCLK_SYS_STATE_IDLE,
	SCLK_SYS_STATE_RUN,
	SCLK_SYS_STATE_IRQ = 4U,
	SCLK_SYS_STATE_FIQ = 8U,
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

static void init_pll(u32 pll_base_offset, u32 pll_misc_offset, const union pll_fields pll, u32 lock)
{
	//TODO: rename
	u32 dividers =  pll.div.n << PLL_BASE_DIVN_SHIFT |
			pll.div.m << PLL_BASE_DIVM_SHIFT |
			pll.div.p << PLL_BASE_DIVP_SHIFT;
	u32 misc_con = pll.div.cpcon << PLL_MISC_CPCON_SHIFT |
		       pll.div.lfcon << PLL_MISC_LFCON_SHIFT;

	/* Write dividers but BYPASS the PLL while we're messing with it. */
	CLOCK(pll_base_offset)=dividers | (1<<CLK_RST_CONTROLLER_PLLC_BASE_PLLC_BYPASS_SHIFT);
	/*
	 * Set Lock bit, CPCON and LFCON fields (default to 0 if it doesn't
	 * exist for this PLL)
	 */
	CLOCK(pll_misc_offset)=(lock | misc_con);

	/* Enable PLL and take it back out of BYPASS */
	CLOCK(pll_base_offset)=dividers | (1 << CLK_RST_CONTROLLER_PLLC_BASE_PLLC_ENABLE_SHIFT);

	/* Wait for lock ready */
	while (!(CLOCK(pll_base_offset) & (1 << CLK_RST_CONTROLLER_PLLC_BASE_PLLC_LOCK_SHIFT)));

}

/* From Coreboot */
/* Clock configuration. */
void config_oscillators()
{	
	// clock_get_osc_bits()
	//	Copied from coreboot
	// 	OSC_FREQ_13 = 0,
	// 	OSC_FREQ_16P8 = 1,
	// 	OSC_FREQ_19P2 = 4,
	// 	OSC_FREQ_38P4 = 5,
	// 	OSC_FREQ_12 = 8,
	// 	OSC_FREQ_48 = 9,
	// 	OSC_FREQ_26 = 12
	// 
	// 8 is 12mhz
	//TODO other osc freq porting
	u32 clk_osc_bit=(CLOCK(CLK_RST_CONTROLLER_OSC_CTRL)&CLK_OSC_FREQ_MASK)>>CLK_OSC_FREQ_SHIFT;


	/* Set PLLC dynramp_step A to 0x2b and B to 0xb (from U-Boot -- why? */
	CLOCK(CLK_RST_CONTROLLER_PLLC_MISC2)=(0x2b << 17 | 0xb << 9);
	

	// static const osc_table[16] = {
	// [OSC_FREQ_12] = {
	// 	.khz = 12000,
	// 	.pllx = {.n = TEGRA_PLLX_KHZ / 12000, .m =  1, .p = 0},
	// 	.pllc = {.n =  50, .m =  1, .p = 0},
	// 	.pllu = {.n = 960, .m = 12, .p = 0, .cpcon = 12, .lfcon = 2},
	// 	.plldp = {.n = 90, .m =  1, .p = 3},
	// },
	/* Max out the AVP clock before everything else (need PLLC for that). */
	init_pll(CLK_RST_CONTROLLER_PLLC_BASE,CLK_RST_CONTROLLER_PLLC_MISC,osc_table[clk_osc_bit].pllc,(1 << CLK_RST_CONTROLLER_PLLC_MISC_PLLC_LOCK_ENABLE_SHIFT));
	printf_("[x] PLLC setup\n");

	/* Typical ratios are 1:2:2 or 1:2:3 sclk:hclk:pclk (See: APB DMA
	 * features section in the TRM). */
	CLOCK(CLK_RST_CONTROLLER_CLK_SYSTEM_RATE)=
		TEGRA_HCLK_RATIO << CLK_RST_CONTROLLER_CLK_SYSTEM_RATE_AHB_RATE_SHIFT |
		TEGRA_PCLK_RATIO << CLK_RST_CONTROLLER_CLK_SYSTEM_RATE_APB_RATE_SHIFT;

	CLOCK(CLK_RST_CONTROLLER_PLLC_OUT)=CLK_DIVIDER(TEGRA_PLLC_KHZ, TEGRA_SCLK_KHZ)
		<< CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RATIO_SHIFT | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_CLKEN_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RSTN_SHIFT);

	/* sclk = 300 MHz */
	CLOCK(CLK_RST_CONTROLLER_SCLK_BURST_POLICY)=
		CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SYS_STATE_RUN << CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SYS_STATE_SHIFT |
		CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SWAKEUP_RUN_SOURCE_PLLC_OUT1 <<CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SWAKEUP_RUN_SOURCE_SHIFT;		
	printf_("[x] System Clock:300 Mhz\n");

	// Read oscillator drive strength from OSC_EDPD_OVER.XOFS and copy
	// to OSC_CTRL.XOFS and set XOE. --copied from lp0
	
	/*
	 * Ambiguous quote from u-boot. TODO: what's this mean?
	 * "should update same value in PMC_OSC_EDPD_OVER XOFS
	 * field for warmboot "
	 */
	u32 xofs = (PMC(APBDEV_PMC_OSC_EDPD_OVER) &
		    PMC_XOFS_MASK) >> PMC_XOFS_SHIFT;

	/*Change the oscillator drive strength (from U-Boot -- why?) */
	u32 osc_ctrl = CLOCK(CLK_RST_CONTROLLER_OSC_CTRL);
	osc_ctrl &= ~CLK_OSC_XOFS_MASK;
	osc_ctrl |= (xofs << CLK_OSC_XOFS_SHIFT);
	osc_ctrl |= CLK_OSC_XOE;
	CLOCK(CLK_RST_CONTROLLER_OSC_CTRL)=osc_ctrl;

	/* Disable IDDQ for PLLX before we set it up (from U-Boot -- why?) */
	CLOCK(CLK_RST_CONTROLLER_PLLX_MISC_3) &= ~PLLX_MISC3_IDDQ; // Disable IDDQ.

	/* Set up PLLP_OUT(1|2|3|4) divisor to generate (9.6|48|102|204)MHz */

	//pll2 ovr shift should be 18?
	
	CLOCK(CLK_RST_CONTROLLER_PLLP_OUTA)=((CLK_DIVIDER(TEGRA_PLLP_KHZ, 9600) << (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RATIO_SHIFT) |
	(1 << CLK_RST_CONTROLLER_PLLP_OUTA_PLLP_OUT1_OVRRIDE_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_CLKEN_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RSTN_SHIFT)) << PLL_OUT1_SHIFT |
	(CLK_DIVIDER(TEGRA_PLLP_KHZ, 48000) << (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RATIO_SHIFT) |
	(1 << CLK_RST_CONTROLLER_PLLP_OUTA_PLLP_OUT1_OVRRIDE_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_CLKEN_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RSTN_SHIFT)) << PLL_OUT2_SHIFT);

	CLOCK(CLK_RST_CONTROLLER_PLLP_OUTB)= ((CLK_DIVIDER(TEGRA_PLLP_KHZ, 102000) << (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RATIO_SHIFT) |
		(1 << CLK_RST_CONTROLLER_PLLP_OUTA_PLLP_OUT1_OVRRIDE_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_CLKEN_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RSTN_SHIFT)) << PLL_OUT3_SHIFT |
		(CLK_DIVIDER(TEGRA_PLLP_KHZ, 204000) << (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RATIO_SHIFT) |
		(1 << CLK_RST_CONTROLLER_PLLP_OUTA_PLLP_OUT1_OVRRIDE_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_CLKEN_SHIFT) | (1 << CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RSTN_SHIFT)) << PLL_OUT4_SHIFT);

	init_pll(CLK_RST_CONTROLLER_PLLX_BASE,CLK_RST_CONTROLLER_PLLX_MISC,osc_table[clk_osc_bit].pllx,(1 << CLK_RST_CONTROLLER_PLLX_MISC_PLLX_LOCK_ENABLE_SHIFT));

	init_pll(CLK_RST_CONTROLLER_PLLU_BASE,CLK_RST_CONTROLLER_PLLU_MISC,osc_table[clk_osc_bit].pllu,(1 << CLK_RST_CONTROLLER_PLLU_MISC_PLLU_LOCK_ENABLE_SHIFT));


	//TODO usb device init later


	/* Graphics just has to be different. There's a few more bits we
	* need to set in here, but it makes sense just to restrict all the
	* special bits to this one function. Imported form graphics_pll(void)
	*/

	/* the vendor code sets the dither bit (28)
	* an undocumented bit (24)
	* and clamp while we mess with it (22)
	* Dither is pretty important to display port
	* so we really do need to handle these bits.
	* I'm not willing to not clamp it, even if
	* it might "mostly work" with it not set,
	* I don't want to find out in a few months
	* that it is needed.
	*/
	u32 scfg = (1<<28) | (1<<24) | (1<<22);
	CLOCK(CLK_RST_CONTROLLER_PLLDP_SS_CFG)=scfg;
	
	init_pll(CLK_RST_CONTROLLER_PLLDP_BASE, CLK_RST_CONTROLLER_PLLDP_MISC,
		osc_table[clk_osc_bit].plldp, (1 << CLK_RST_CONTROLLER_PLLDP_MISC_0_PLLDP_LOCK_ENABLE_SHIFT));
	/* leave dither and undoc bits set, release clamp */
	scfg = (1<<28) | (1<<24);
	CLOCK(CLK_RST_CONTROLLER_PLLDP_SS_CFG)=scfg;

	/* disp1 will be set when panel information (pixel clock) is
	* retrieved (clock_display).
	*/
	printf_("[X] PLLP,PLLX,PLLU,PLLDP setup\n");
}
static const clk_rst_t _clock_uart[] = {
	{ CLK_RST_CONTROLLER_RST_DEVICES_L, CLK_RST_CONTROLLER_CLK_OUT_ENB_L, CLK_RST_CONTROLLER_CLK_SOURCE_UARTA,   CLK_L_UARTA,   0, 2 },
	{ CLK_RST_CONTROLLER_RST_DEVICES_L, CLK_RST_CONTROLLER_CLK_OUT_ENB_L, CLK_RST_CONTROLLER_CLK_SOURCE_UARTB,   CLK_L_UARTB,   0, 2 },
	{ CLK_RST_CONTROLLER_RST_DEVICES_H, CLK_RST_CONTROLLER_CLK_OUT_ENB_H, CLK_RST_CONTROLLER_CLK_SOURCE_UARTC,   CLK_H_UARTC,   0, 2 },
	{ CLK_RST_CONTROLLER_RST_DEVICES_U, CLK_RST_CONTROLLER_CLK_OUT_ENB_U, CLK_RST_CONTROLLER_CLK_SOURCE_UARTD,   CLK_U_UARTD,   0, 2 },
};
void clock_enable_uart(u32 idx)
{
	clock_enable(&_clock_uart[idx]);
}
#define UART_SRC_CLK_DIV_EN BIT(24)

int clock_uart_use_src_div(u32 idx, u32 baud)
{
	u32 clk_src_div = CLOCK(_clock_uart[idx].source) & 0xE0000000;

	if (baud == 3000000)
		CLOCK(_clock_uart[idx].source) = clk_src_div | UART_SRC_CLK_DIV_EN | 15;
	else if (baud == 1000000)
		CLOCK(_clock_uart[idx].source) = clk_src_div | UART_SRC_CLK_DIV_EN | 49;
	else
	{
		CLOCK(_clock_uart[idx].source) = clk_src_div | 2;

		return 1;
	}

	return 0;
}
