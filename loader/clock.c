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


}
