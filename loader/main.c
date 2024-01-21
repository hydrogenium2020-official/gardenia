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
#include "types.h"
#include "printf.h"
#include "string.h"

#include "t124.h"
#include "se.h"
#include "usb.h"
#include "bootrom.h"
#include "fuse.h"
#include "mc.h"
#include "clock.h"
#include "util.h"
#include "pinmux.h"
#include "gpio.h"
#include "i2c.h"

static inline u32 read32(uintptr_t addr) {
    return *(vu32 *)addr;
}

static inline void write32(uintptr_t addr, u32 val) {
    *(vu32 *)addr = val;
}

static inline void or32(uintptr_t addr, u32 val) {
    write32(addr, read32(addr) | val);
}

void *memset(void *s, int c, size_t n) {
    unsigned char* p = (unsigned char*)s;
    for (size_t i = 0; i < n; i++) {
        *p++ = (unsigned char)c;
    }
    return s;
}


#define PMC_CNTRL              0x000
#define PMC_CNTRL_MAIN_RST    (1 << 4)
#define PMC_SCRATCH0           0x050
#define PMC_SCRATCH0_MODE_RCM (1 << 1)
void enter_rcm() {
    or32(PMC_BASE + PMC_SCRATCH0, PMC_SCRATCH0_MODE_RCM);
    or32(PMC_BASE + PMC_CNTRL, PMC_CNTRL_MAIN_RST);
}


void config_hw(){
    printf_("Starting Initing hardware.");
    fuse_disable_program();
    printf_("[x] fuse program disabled\n");
    
    // Initialize counters, CLKM, BPMP(also called AVP in T124/T132) and other clocks based on 38.4MHz oscillator.
	config_oscillators();

    mc_enable();
    printf_("[x] mc setup\n");

    config_gpios();
    printf_("[x] GPIO setup\n");
    

    //clock_enable_cl_dvfs();
    //printf_("[x] DVFS setup\n");
    
    //FIXME I2C Doesn't work!!!
    printf_("Fixme.I2C doesn't work");
	// clock_enable_i2c(I2C_1);
	// clock_enable_i2c(I2C_5);

}

__attribute__((section(".init")))
void _start() {
    // u8 *buffer = (u8*)0x40020000;
    printf_("gardenia is booting.");

    //printf_("%p",&_start);
    //pivot_stack(0x200);

    //Setting up hardware
    dump_pkc();
    config_hw();
    
    enter_rcm();
}

