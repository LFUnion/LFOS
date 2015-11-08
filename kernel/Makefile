.SILENT: build
.PHONY: build
.PHONY: clean

GCC = i686-elf-gcc
GCC_INCLUDES = -I./includes/ -I./klib/includes/ -I./kshell/includes/
GCC_FLAGS = -O2 -ffreestanding -std=gnu99 -Wall -Wextra

build:
	echo "Cleaning ..."
	make clean
	echo "Assembling bootloader ..."
	mkdir build
	mkdir build/klib
	mkdir build/drivers
	mkdir build/kshell
	nasm -felf32 -o build/bootloader.o boot/bootloader.asm
	echo "Assembling segments"
	nasm -felf32 -o build/segments.o memory/segments.asm
	echo "Assembling exception handlers"
	nasm -felf32 -o build/exceptions.o interrupts/exceptions.asm
	echo "Compiling GDT"
	$(GCC) -c memory/gdt.c -o build/gdt.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling IDT"
	$(GCC) -c interrupts/idt.c -o build/idt.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling C common exception handler"
	$(GCC) -c interrupts/exceptionhandler.c -o build/exceptionhandler.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling memory manager"
	$(GCC) -c memory/memmanager.c -o build/memmanager.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling outb"
	$(GCC) -c ports/outb.c -o build/outb.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling inb"
	$(GCC) -c ports/inb.c -o build/inb.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling cpu"
	$(GCC) -c cpu/cpu.c -o build/cpu.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling RTC driver"
	$(GCC) -c drivers/rtc/rtc.c -o build/drivers/rtc.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling VGA driver ..."
	$(GCC) -c drivers/vga/vga.c -o build/drivers/vga.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling ATA driver"
	$(GCC) -c drivers/ata/ata.c -o build/drivers/ata.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling serial driver"
	$(GCC) -c drivers/serial/serial.c -o build/drivers/serial.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling keyboard driver ..."
	$(GCC) -c drivers/keyboard/keyboard.c -o build/drivers/keyboard.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling beeper driver"
	$(GCC) -c drivers/sound/beeper.c -o build/drivers/beeper.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling uFS"
	$(GCC) -c fs/ufs.c -o build/ufs.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling KIO"
	$(GCC) -c klib/kio.c -o build/klib/kio.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kcom"
	$(GCC) -c klib/kcom.c -o build/klib/kcom.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kcasts"
	$(GCC) -c klib/kcasts.c -o build/klib/kcasts.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling ktime"
	$(GCC) -c klib/ktime.c -o build/klib/ktime.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kstring"
	$(GCC) -c klib/kstring.c -o build/klib/kstring.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kshell"
	$(GCC) -c kshell/kshell.c -o build/kshell/kshell.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling process"
	$(GCC) -c multitasking/process.c -o build/process.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kernel ..."
	$(GCC) -c kernel.c -o build/kernel.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Linking ..."
	$(GCC) -T linker.ld -o build/lfos.bin -ffreestanding -O2 -nostdlib -Wall build/bootloader.o build/kernel.o build/drivers/vga.o build/drivers/ata.o build/drivers/serial.o build/drivers/keyboard.o build/drivers/beeper.o build/drivers/rtc.o build/klib/kio.o build/klib/kcom.o build/klib/kcasts.o build/klib/kstring.o build/klib/ktime.o build/kshell/kshell.o build/memmanager.o build/outb.o build/inb.o build/segments.o build/gdt.o build/idt.o build/exceptionhandler.o build/exceptions.o build/cpu.o build/process.o -lgcc
	
clean:
	rm -rf build/
	
test:
	qemu-system-i386 -serial stdio -kernel build/lfos.bin

testATA:
	dd if=/dev/zero of=build/hdd.img count=4096
	qemu-system-i386 -kernel build/lfos.bin -serial stdio -drive file=build/hdd.img,if=ide
	
