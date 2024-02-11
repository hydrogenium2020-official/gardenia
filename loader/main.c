/*
* Copyright (c) 2024 hydrogenium2020-offical
* Copyright (c) 2018 naehrwert
* Copyright (c) 2018-2023 CTCaer
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
#include "usb.h"
#include "bootrom.h"
#include "fuse.h"
#include "mc.h"
#include "clock.h"
#include "util.h"
#include "pinmux.h"
#include "gpio.h"
#include "uart.h"
#include "sdram.h"
#include "memory_map.h"

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
    printf_("Starting Initing hardware.\n");
    fuse_disable_program();
    printf_("[x] fuse program disabled\n");
    
    // Initialize oscillators
	config_oscillators();

    // My board didn't have UART port
    // pinmux_config_uart(UART_D);
	// clock_enable_uart(UART_D);
	// uart_init(UART_D, 115200, UART_AO_TX_AO_RX);
	// uart_invert(UART_D, 0, UART_INVERT_TXD);

    //uart_send(UART_D, (u8 *)"hekate: Hello!\r\n", 16);
	//uart_wait_xfer(UART_D, UART_TX_IDLE);

    // mc_enable();
    // printf_("[x] mc setup\n");

    config_gpios();
    printf_("[x] GPIO setup\n");

    sdram_init();
    printf_("[x] SDRAM setup\n");

}
extern void pivot_stack(u32 stack_top);
__attribute__((section(".init")))
void _start() {
    // u8 *buffer = (u8*)0x40020000;
    printf_("gardenia is booting.\n");

    //printf_("%p",&_start);

    //Setting up hardware
    dump_pkc();
    config_hw();
    
    printf_("%d\n",MMIO_REG32(0x90010000,0));
    MMIO_REG32(0x90010000,0)=0x123456;
    printf_("%d\n",MMIO_REG32(0x90010000,0));
    sleep(200);
    printf_("%d\n",MMIO_REG32(0x90010000,0));

    u32 total_size = (MC(MC_EMEM_CFG) >>
			MC_EMEM_CFG_SIZE_MB_SHIFT) & MC_EMEM_CFG_SIZE_MB_MASK;

	printf_("Total SDRAM (MB): %u\n", total_size);
    
    //Pivot the stack so we have enough space.
	pivot_stack(IPL_STACK_TOP);
    printf_("alive");

	heap_init(IPL_HEAP_START);

    enter_rcm();
}

