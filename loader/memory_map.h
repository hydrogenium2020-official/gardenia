/*
 * Copyright (c) 2024 hydrogenium2020-offical
 * Copyright (c) 2019-2021 CTCaer
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

#ifndef _T124_MEMORY_MAP_H_
#define _T124_MEMORY_MAP_H_

#define SDRAM_PARAMS_ADDR 0x40030000 // SDRAM extraction buffer during sdram init.

/* --- DRAM START --- */
#define DRAM_START     0x80000000

/* Stack theoretical max: 33MB */
#define IPL_STACK_TOP  0x83100000
#define IPL_HEAP_START 0x84000000
#define  IPL_HEAP_SZ      SZ_512M

#endif
