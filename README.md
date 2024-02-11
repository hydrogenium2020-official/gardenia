# gardenia
**NOTICE: This project is in early development! I am not responsible for any damage to your device, please proceed with caution.**

(WIP)This is a custom bootloader for Tegra T124/T132 Soc.
A fork of early commit of [hekate](https://github.com/CTCaer/hekate/).

# Issues/TODO
#### T124 UDI TK1 Core board
- Bring up Display
- Bring up EMMC

I am studying its process.

## Build
### **Archlinux** 
```shell
sudo pacman -S arm-none-eabi-newlib arm-none-eabi-gcc arm-none-eabi-binutils #Build Toolchain
mkdir build
make
...#Run the payload
```
