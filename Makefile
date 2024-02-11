

CC = $(DEVKITARM)/bin/arm-none-eabi-gcc
LD = $(DEVKITARM)/bin/arm-none-eabi-ld
OBJCOPY = $(DEVKITARM)/bin/arm-none-eabi-objcopy

TARGET := bootloader
BUILD := build
SOURCEDIR := loader
OBJS = $(addprefix $(BUILD)/, \
	stack.o		\
	main.o		\
	fuse.o		\
	usb.o		\
	util.o		\
	mc.o		\
	timer.o		\
	clock.o		\
	pinmux.o	\
	gpio.o		\
	heap.o		\
	uart.o      \
	sdram.o 	\
	sdram_lp0.o \
	io.o 		\
)

OBJS += $(addprefix $(BUILD)/, \
	printf.o	\
)

INCLUDE:=-I lib/printf -I loader
ARCH := -march=armv4t -mtune=arm7tdmi -mthumb -mthumb-interwork
CFLAGS = $(ARCH) $(INCLUDE) -fno-common -nostdlib -lnosys -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-inline -std=gnu11 -lgcc -Wl,--nmagic  # -Wall
LDFLAGS = $(ARCH) -nostartfiles -lgcc -lnosys -Wl,--nmagic#do not use --gc-sections here,it will cause strange problem

.PHONY: all clean

all: $(BUILD)/$(TARGET)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(BUILD)/$(TARGET).elf
	@rm -rf $(BUILD)/$(TARGET)

$(BUILD)/$(TARGET): $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -S -O binary $< $@

$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -T loader/link.ld $^ -o $@

$(BUILD)/%.o: $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SOURCEDIR)/%.S
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: lib/printf/%.c
	$(CC) $(CFLAGS) -c $< -o $@
