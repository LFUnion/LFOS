.SILENT: build
.PHONY: build
.PHONY: clean

GCC = i686-elf-gcc
GCC_INCLUDES = -I./includes/
GCC_FLAGS = -O2 -ffreestanding -std=gnu99 -Wall -Wextra

build:
	echo "Cleaning ..."
	make clean
	echo "Assembling bootloader ..."
	mkdir build
	nasm -felf32 -o build/bootloader.o boot/bootloader.asm
	echo "Compiling outb"
	$(GCC) -c ports/outb.c -o build/outb.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling inb"
	$(GCC) -c ports/inb.c -o build/inb.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling VGA driver ..."
	$(GCC) -c vga/vga.c -o build/vga.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kernel ..."
	$(GCC) -c kernel.c -o build/kernel.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Linking ..."
	$(GCC) -T linker.ld -o build/fsos.bin -ffreestanding -O2 -nostdlib build/bootloader.o build/vga.o build/kernel.o -lgcc
	
clean:
	rm -rf build/
	
test:
	qemu-system-i386 -kernel build/fsos.bin
