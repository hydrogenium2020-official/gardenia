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
//SE
#ifndef _T124_SE_H_
#define _T124_SE_H_

#define SE_KEYTABLE_REG_OFFSET		0x31c
#define SE_KEYTABLE_SLOT_SHIFT		7
#define SE_KEYTABLE_SLOT(x)			(x << SE_KEYTABLE_SLOT_SHIFT)
#define SE_KEYTABLE_QUAD_SHIFT		2
#define SE_KEY_TABLE_ACCESS_REG_OFFSET	0x284
#define SE_INT_STATUS_REG_OFFSET	0x010
#define SE_KEYTABLE_DATA0_REG_OFFSET	0x320

#endif