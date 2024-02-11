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
#include "types.h"
#include "i2c.h"
void i2c_init(u32 i2c_idx)
{
	vu32 *base = (vu32 *)(I2C_BASE + (u32)_i2c_base_offsets[i2c_idx]);

	base[I2C_CLK_DIVISOR] = (5 << 16) | 1; // SF mode Div: 6, HS mode div: 2.
	base[I2C_BUS_CLEAR_CONFIG] = (9 << 16) | BC_TERMINATE | BC_ENABLE;

	// Load configuration.
	_i2c_load_cfg_wait(base);

	for (u32 i = 0; i < 10; i++)
	{
		if (base[I2C_INT_STATUS] & BUS_CLEAR_DONE)
			break;
		usleep(25);
	}

	(vu32)base[I2C_BUS_CLEAR_STATUS];
	base[I2C_INT_STATUS] = base[I2C_INT_STATUS];
}