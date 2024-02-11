/*
 * Copyright (c) 2024 hydrogenium2020-offical
 * Copyright 2014 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */
#include "types.h"
u32 read32(u32 *addr)
{
    return *(vu32 *)addr;
}

void write32(u32 *addr, u32 val)
{
    *(vu32 *)addr = val;
}

void setbits32(u32 *addr,u32 bits)
{
	write32(addr, read32(addr) | bits);
}

void clrbits32(u32 *addr,u32 bits)
{
	write32(addr, read32(addr) & ~bits);
}

void clrsetbits32(u32 *addr,u32 mask, u32 value)
{
    write32(addr,(read32(addr) & ~((u32)(mask))) | (value));
}