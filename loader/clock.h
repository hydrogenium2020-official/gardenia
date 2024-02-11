/*
* Copyright (c) 2018 naehrwert
* Copyright (c) 2018-2022 CTCaer
* Copyright (c) 2024 hydrogenium2020-offical
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

#ifndef _T124_CLOCK_H_
#define _T124_CLOCK_H_

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
/* soc-specific */
#define TEGRA_CLK_M_KHZ	 12000
#define TEGRA_PLLX_KHZ   2000000
#define TEGRA_PLLP_KHZ   (408000)
#define TEGRA_PLLC_KHZ   (600000)
#define TEGRA_PLLD_KHZ   (925000)
#define TEGRA_PLLU_KHZ   (960000)

#define TEGRA_SCLK_KHZ   (300000)
#define TEGRA_HCLK_RATIO 1
#define TEGRA_HCLK_KHZ   (TEGRA_SCLK_KHZ / (1 + TEGRA_HCLK_RATIO))
#define TEGRA_PCLK_RATIO 0
#define TEGRA_PCLK_KHZ   (TEGRA_HCLK_KHZ / (1 + TEGRA_PCLK_RATIO))

#define CLK_RST_CONTROLLER_OSC_CTRL 0x50
#define CLK_OSC_DRIVE_STRENGTH 7

//PLLC
#define CLK_RST_CONTROLLER_PLLC_BASE 0x80
#define CLK_RST_CONTROLLER_PLLC_MISC 0x8c
#define CLK_RST_CONTROLLER_PLLC_MISC_PLLC_LOCK_ENABLE_SHIFT 24
#define CLK_RST_CONTROLLER_PLLC_MISC2 0x88
#define CLK_RST_CONTROLLER_PLLC_BASE_PLLC_BYPASS_SHIFT 31
#define CLK_RST_CONTROLLER_PLLC_OUT 0x84

#define CLK_RST_CONTROLLER_CLK_SYSTEM_RATE 0x30
#define CLK_RST_CONTROLLER_CLK_SYSTEM_RATE_AHB_RATE_SHIFT 4
#define CLK_RST_CONTROLLER_CLK_SYSTEM_RATE_APB_RATE_SHIFT 0

#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY 0x28

#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SYS_STATE_SHIFT 28
#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SYS_STATE_IDLE 1
#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SYS_STATE_RUN 2
#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SWAKEUP_RUN_SOURCE_PLLC_OUT1 1
#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SWAKEUP_RUN_SOURCE_PLLP_OUT4 2
#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SWAKEUP_RUN_SOURCE_PLLP_OUT3 3
#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SWAKEUP_RUN_SOURCE_PLLP_OUT2 4
#define CLK_RST_CONTROLLER_SCLK_BURST_POLICY_SWAKEUP_RUN_SOURCE_SHIFT 4
//PLLP
#define CLK_RST_CONTROLLER_PLLP_OUTA 0xA4
#define CLK_RST_CONTROLLER_PLLP_OUTB 0xA8
#define CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RATIO_SHIFT 8
#define CLK_RST_CONTROLLER_PLLP_OUTA_PLLP_OUT1_OVRRIDE_SHIFT 2
#define CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_CLKEN_SHIFT 1
#define CLK_RST_CONTROLLER_PLLM_OUT_PLLM_OUT1_RSTN_SHIFT 0

//PLLX
#define PLLX_MISC3_IDDQ (1U << 3)
#define CLK_RST_CONTROLLER_PLLX_BASE 0xe0
#define CLK_RST_CONTROLLER_PLLX_MISC 0xe4
#define CLK_RST_CONTROLLER_PLLX_MISC_3 0x518
#define CLK_RST_CONTROLLER_PLLX_MISC_PLLX_LOCK_ENABLE_SHIFT 18

//PLLU
#define CLK_RST_CONTROLLER_PLLU_BASE 0xc0
#define CLK_RST_CONTROLLER_PLLU_MISC 0xcc
#define CLK_RST_CONTROLLER_PLLU_MISC_PLLU_LOCK_ENABLE_SHIFT 22



//PLLDP (Graphis PLL)
#define CLK_RST_CONTROLLER_PLLDP_SS_CFG 0x598
#define CLK_RST_CONTROLLER_PLLDP_BASE 0x590
#define CLK_RST_CONTROLLER_PLLDP_MISC 0x594
#define CLK_RST_CONTROLLER_PLLDP_MISC_0_PLLDP_LOCK_ENABLE_SHIFT 30

#define PLL_OUT1_SHIFT			0
#define PLL_OUT2_SHIFT			16
#define PLL_OUT3_SHIFT			0
#define PLL_OUT4_SHIFT			16

#define PLL_BASE_DIVN_SHIFT		8
#define PLL_BASE_DIVM_SHIFT		0
#define PLL_BASE_DIVP_SHIFT		20
#define PLL_MISC_CPCON_SHIFT		8
#define PLL_MISC_LFCON_SHIFT		4

#define CLK_RST_CONTROLLER_PLLC_BASE_PLLC_ENABLE_SHIFT 30
#define CLK_RST_CONTROLLER_PLLC_BASE_PLLC_LOCK_SHIFT 27


#define PLLCX_BASE_LOCK      BIT(27)

#define DIV_ROUND_UP(x, y) ({ \
	__typeof__(x) _div_local_x = (x); \
	__typeof__(y) _div_local_y = (y); \
	(_div_local_x + _div_local_y - 1) / _div_local_y; \
})
#define CLK_DIVIDER(REF, FREQ)	(DIV_ROUND_UP(((REF) * 2), (FREQ)) - 2)

//MC
#define CLK_RST_CONTROLLER_CLK_ENB_H_SET 0x328
#define CLK_RST_CONTROLLER_CLK_ENB_X_SET 0x284
#define CLK_RST_CONTROLLER_RST_DEV_H_SET 0x308
#define CLK_RST_CONTROLLER_RST_DEV_H_CLR 0x30C
#define CLK_RST_CONTROLLER_LVL2_CLK_GATE_OVRD 0x3a4


/* SPECIAL CASE: PLLM, PLLC and PLLX use different-sized fields here */
#define PLLCX_BASE_DIVP_MASK		(0xfU << PLL_BASE_DIVP_SHIFT)
#define PLLM_BASE_DIVP_MASK		(0x1U << PLL_BASE_DIVP_SHIFT)
#define PLLCMX_BASE_DIVN_MASK		(0xffU << PLL_BASE_DIVN_SHIFT)
#define PLLCMX_BASE_DIVM_MASK		(0xffU << PLL_BASE_DIVM_SHIFT)
enum {
	MC_EMEM_CFG_SIZE_MB_SHIFT = 0,
	MC_EMEM_CFG_SIZE_MB_MASK = 0x3fff,

	MC_EMEM_ARB_MISC0_MC_EMC_SAME_FREQ_SHIFT = 27,
	MC_EMEM_ARB_MISC0_MC_EMC_SAME_FREQ_MASK = 1 << 27,

	MC_EMEM_CFG_ACCESS_CTRL_WRITE_ACCESS_DISABLED = 1,

	MC_TIMING_CONTROL_TIMING_UPDATE = 1,
};

//EMC
#define CLK_RST_CONTROLLER_CLK_SOURCE_EMC 0x19c
#define CLK_SOURCE_EMC_MC_EMC_SAME_FREQ (1 << 16)

//PLLM
#define PLLM_BASE 0x90
#define PLLM_MISC1_BASE 0x98
#define PLLM_MISC2_BASE 0x9c
#define PLLM_MISC1_SETUP_SHIFT			0
#define PLLM_MISC1_PD_LSHIFT_PH45_SHIFT		28
#define PLLM_MISC1_PD_LSHIFT_PH90_SHIFT		29
#define PLLM_MISC1_PD_LSHIFT_PH135_SHIFT	30
#define PLLM_MISC2_KCP_SHIFT			1
#define PLLM_MISC2_KVCO_SHIFT			0
#define PLLM_OUT1_RSTN_RESET_DISABLE		(1 << 0)

/* CLK_RST_CONTROLLER_PLL*_BASE_0 */
#define PLL_BASE_BYPASS			(1U << 31)
#define PLL_BASE_ENABLE			(1U << 30)
#define PLL_BASE_REF_DIS		(1U << 29)
#define PLL_BASE_OVRRIDE		(1U << 28)
#define PLL_BASE_LOCK			(1U << 27)
#define IO_STABILIZATION_DELAY (2)

#define PLL_BASE_DIVP_SHIFT		20
#define PLL_BASE_DIVP_MASK		(7U << PLL_BASE_DIVP_SHIFT)

#define PLL_BASE_DIVN_SHIFT		8
#define PLL_BASE_DIVN_MASK		(0x3ffU << PLL_BASE_DIVN_SHIFT)

#define PLL_BASE_DIVM_SHIFT		0
#define PLL_BASE_DIVM_MASK		(0x1f << PLL_BASE_DIVM_SHIFT)


//Reset
#define CLK_RST_CONTROLLER_RST_DEVICES_L 0x4
#define CLK_RST_CONTROLLER_RST_DEVICES_H 0x8
#define CLK_RST_CONTROLLER_RST_DEVICES_U 0xC

#define CLK_RST_CONTROLLER_CLK_OUT_ENB_L 0x10
#define CLK_RST_CONTROLLER_CLK_OUT_ENB_H 0x14
#define CLK_RST_CONTROLLER_CLK_OUT_ENB_U 0x18

//UART
#define CLK_RST_CONTROLLER_CLK_SOURCE_UARTA 0x178
#define CLK_RST_CONTROLLER_CLK_SOURCE_UARTB 0x17C
#define CLK_RST_CONTROLLER_CLK_SOURCE_UARTC 0x1A0
#define CLK_RST_CONTROLLER_CLK_SOURCE_UARTD 0x1C0
enum CLK_L_DEV
{
	CLK_L_UARTA   = 6,
	CLK_L_UARTB   = 7,
};
enum CLK_H_DEV
{
	CLK_H_UARTC    = 23,
};
enum CLK_U_DEV
{
	CLK_U_UARTD          = 1,
};
enum {
	CLK_OSC_XOE = 0x1 << 0,
	CLK_OSC_XOFS_SHIFT = 4,
	CLK_OSC_XOFS_MASK = 0x3f << CLK_OSC_XOFS_SHIFT,
	CLK_OSC_FREQ_SHIFT = 28,
	CLK_OSC_FREQ_MASK = 0xf << CLK_OSC_FREQ_SHIFT
};



struct pll_dividers {
	u32	n : 10;
	u32	m : 8;
	u32	p : 4;
	u32	cpcon : 4;
	u32	lfcon : 4;
	u32	: 2;
};

/* Some PLLs have more restrictive divider bit lengths or are missing some
 * fields. Make sure to use the right struct in the osc_table definition to get
 * compile-time checking, but keep the bits aligned with struct pll_dividers so
 * they can be used interchangeably at run time. Add new formats as required. */
struct pllcx_dividers {
	u32	n : 8;
	u32	: 2;
	u32	m : 8;
	u32	p : 4;
	u32	: 10;
};
struct pllpad_dividers {
	u32	n : 10;
	u32	m : 5;
	u32	: 3;
	u32	p : 3;
	u32	: 1;
	u32	cpcon : 4;
	u32	: 6;
};
struct pllu_dividers {
	u32	n : 10;
	u32	m : 5;
	u32	: 3;
	u32	p : 1;
	u32	: 3;
	u32	cpcon : 4;
	u32	lfcon : 4;
	u32	: 2;
};

union __attribute__((transparent_union)) pll_fields {
	u32 raw;
	struct pll_dividers div;
	struct pllcx_dividers cx;
	struct pllpad_dividers pad;
	struct pllu_dividers u;
};


void clock_enable(const clk_rst_t *clk);
void clock_disable(const clk_rst_t *clk);
void clock_enable_cl_dvfs();
void clock_enable_i2c(u32 idx);
void clock_enable_uart(u32 idx);
void config_oscillators();
int clock_uart_use_src_div(u32 idx, u32 baud);

#endif
