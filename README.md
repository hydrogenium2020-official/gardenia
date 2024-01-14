# gardenia

(WIP)This is a custom bootloader for Tegra T124/T132 Soc.
A fork of early commit of [hekate](https://github.com/CTCaer/hekate/).

# Issues
- Clock setting? I am not sure it is ture.Here is my code.
```c
void config_oscillators()
{	

	CLOCK(CLK_RST_CONTROLLER_SPARE_REG0) = (CLOCK(CLK_RST_CONTROLLER_SPARE_REG0) & 0xFFFFFFF3) | 0; // Clear 3-2bit and set CLK_M_DIVISOR to 1.the 3-2bit is divisor.
	SYSCTR0(SYSCTR0_CNTFID0)             = 12000000;   // Set counter frequency. 12Mhz

	//This register is for 1 microsecond. bit7-0->DIVISOR bit15-8->DIVIDEND.So we need 1/12
	TIMER0(TIMERUS_USEC_CFG)                = 0x0B;      // For 12MHz clk_m. 	1/12 -> 0x00/0x0b
	 
	CLOCK(CLK_RST_CONTROLLER_OSC_CTRL)   = 0x80000071; // Set OSC to 12MHz and drive strength.

	PMC(APBDEV_PMC_OSC_EDPD_OVER) = (PMC(APBDEV_PMC_OSC_EDPD_OVER) & 0xFFFFFF81) | 0xE; // Set LP0 OSC drive strength.
	PMC(APBDEV_PMC_OSC_EDPD_OVER) = (PMC(APBDEV_PMC_OSC_EDPD_OVER) & 0xFFBFFFFF) | PMC_OSC_EDPD_OVER_OSC_CTRL_OVER;
	PMC(APBDEV_PMC_CNTRL2)        = (PMC(APBDEV_PMC_CNTRL2) & 0xFFFFEFFF) | PMC_CNTRL2_HOLD_CKE_LOW_EN;
	
	//Not impl in T124?Only in T210 and newer
	//PMC(APB_MISC_GP_ASDBGREG)     = (PMC(APB_MISC_GP_ASDBGREG) & 0xFCFFFFFF) | (2 << 24); // CFG2TMC_RAM_SVOP_PDP.

	CLOCK(CLK_RST_CONTROLLER_CLK_SYSTEM_RATE) = 0x00;       // Set HCLK div to 1 and PCLK div to 1.
	//CLOCK(CLK_RST_CONTROLLER_PLLMB_BASE)     &= 0xBFFFFFFF; // PLLMB disable.

	PMC(APBDEV_PMC_TSC_MULT) = (PMC(APBDEV_PMC_TSC_MULT) & 0xFFFF0000) | 0x16E0; // 0x249F = 12000000 * (16 / 32.768 kHz).

	CLOCK(CLK_RST_CONTROLLER_CLK_SOURCE_SYS)     = 0;          // Set BPMP/SCLK div to 1.
	CLOCK(CLK_RST_CONTROLLER_SCLK_BURST_POLICY)  = 0x20004444; // Set BPMP/SCLK source to Run and PLLP_OUT2 (204MHz).
	CLOCK(CLK_RST_CONTROLLER_SUPER_SCLK_DIVIDER) = 0x80000000; // Enable SUPER_SDIV to 1.
	CLOCK(CLK_RST_CONTROLLER_CLK_SYSTEM_RATE)    = 2;          // Set HCLK div to 1 and PCLK div to 3.
}
```

- I2C cannot be initialized properly. When I set the frequency, avp crashed

## Build
### **Archlinux** 
```shell
sudo pacman -S arm-none-eabi-newlib arm-none-eabi-gcc arm-none-eabi-binutils #Build Toolchain
mkdir build
make
...#Run the payload
```
