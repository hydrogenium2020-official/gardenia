# gardenia

(WIP)This is a custom bootloader for Tegra T124/T132 Soc.
A fork of early commit of [hekate](https://github.com/CTCaer/hekate/).

# Issues/TODO
- Init PMIC (TPS65913)
- Init SDRAM
- Init Display
I am studying its process.

## Build
### **Archlinux** 
```shell
sudo pacman -S arm-none-eabi-newlib arm-none-eabi-gcc arm-none-eabi-binutils #Build Toolchain
mkdir build
make
...#Run the payload
```
