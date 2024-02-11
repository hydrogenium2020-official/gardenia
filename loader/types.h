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
#ifndef _TYPES_H_
#define _TYPES_H_

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef u32 size_t;
typedef u32 uintptr_t;

/* Sizes */
#define SZ_1K   0x400
#define SZ_2K   0x800
#define SZ_4K   0x1000
#define SZ_8K   0x2000
#define SZ_16K  0x4000
#define SZ_32K  0x8000
#define SZ_64K  0x10000
#define SZ_128K 0x20000
#define SZ_256K 0x40000
#define SZ_512K 0x80000
#define SZ_1M   0x100000
#define SZ_2M   0x200000
#define SZ_4M   0x400000
#define SZ_8M   0x800000
#define SZ_16M  0x1000000
#define SZ_32M  0x2000000
#define SZ_64M  0x4000000
#define SZ_128M 0x8000000
#define SZ_256M 0x10000000
#define SZ_512M 0x20000000
#define SZ_1G   0x40000000
#define SZ_2G   0x80000000
#define SZ_PAGE SZ_4K

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#define BIT(n) (1U << (n))
#define ALIGN(x, a) (((x) + (a) - 1) & ~((a) - 1))
#define ALIGN_DOWN(x, a) ((x) & ~((a) - 1))
#endif
