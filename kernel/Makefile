.SILENT: build
.PHONY: build
.PHONY: clean

GCC = i686-elf-gcc
GCC_INCLUDES = -I./includes/ -I./klib/includes/
GCC_FLAGS = -O2 -ffreestanding -std=gnu99 -Wall -Wextra

build:
	echo "Cleaning ..."
	make clean
	echo "Assembling bootloader ..."
	mkdir build
	nasm -felf32 -o build/bootloader.o boot/bootloader.asm
	echo "Assembling segments"
	nasm -felf32 -o build/segments.o memory/segments.asm
	echo "Compiling GDT"
	$(GCC) -c memory/gdt.c -o build/gdt.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling IDT"
	$(GCC) -c interrupts/idt.c -o build/idt.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling outb"
	$(GCC) -c ports/outb.c -o build/outb.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling inb"
	$(GCC) -c ports/inb.c -o build/inb.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling VGA driver ..."
	$(GCC) -c vga/vga.c -o build/vga.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kernel ..."
	$(GCC) -c kernel.c -o build/kernel.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Linking ..."
	$(GCC) -T linker.ld -o build/lfos.bin -ffreestanding -O2 -nostdlib -Wall build/vga.o build/outb.o build/inb.o build/segments.o build/gdt.o build/idt.o build/kernel.o build/bootloader.o -lgcc
	
clean:
	rm -rf build/
	
test:
	qemu-system-i386 -kernel build/lfos.bin
