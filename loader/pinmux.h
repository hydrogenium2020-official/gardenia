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

#ifndef _T124_PINMUX_H_
#define _T124_PINMUX_H_

enum {
	PINMUX_FUNC_MASK = 3 << 0,

	PINMUX_PULL_MASK = 3 << 2,
	PINMUX_PULL_NONE = 0 << 2,
	PINMUX_PULL_DOWN = 1 << 2,
	PINMUX_PULL_UP = 2 << 2,

	PINMUX_TRISTATE = 1 << 4,
	PINMUX_PARKED = 1 << 5,
	PINMUX_INPUT_ENABLE = 1 << 6,
	PINMUX_LOCK = 1 << 7,
	PINMUX_LPDR = 1 << 8,
	PINMUX_HSM = 1 << 9,
	PINMUX_IO_HV = 1 << 10,
	PINMUX_OPEN_DRAIN = 1 << 11,
	PINMUX_SCHMT = 1 << 12,

	PINMUX_DRIVE_1X = 0 << 13,
	PINMUX_DRIVE_2X = 1 << 13,
	PINMUX_DRIVE_3X = 2 << 13,
	PINMUX_DRIVE_4X = 3 << 13,
};
/*! 0:UART-A, 1:UART-B, 3:UART-C, 3:UART-D */
#define PINMUX_AUX_UARTX_TX(x)  (0xE4 + 0x10 * (x))
#define PINMUX_AUX_UARTX_RX(x)  (0xE8 + 0x10 * (x))
#define PINMUX_AUX_UARTX_RTS(x) (0xEC + 0x10 * (x))
#define PINMUX_AUX_UARTX_CTS(x) (0xF0 + 0x10 * (x))
/*! 0:GEN1, 1:GEN2, 2:GEN3, 3:CAM, 4:PWR */
#define PINMUX_AUX_X_I2C_SCL(x) (0xBC + 8 * (x))
#define PINMUX_AUX_X_I2C_SDA(x) (0xC0 + 8 * (x))
void pinmux_config_uart(u32 idx);
void pinmux_config_i2c(u32 idx);

#endif