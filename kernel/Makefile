.SILENT: build
.PHONY: build
.PHONY: clean

VERSION = $(shell cat VERSION)
GCC = i686-elf-gcc
GCC_INCLUDES = -I./includes/ -I./klib/includes/ -I./kshell/includes/ -include lfos_config.h
GCC_FLAGS = -O2 -ffreestanding -std=gnu99 -Wall -Wextra -g -DLFOS_VERSION=\"$(VERSION)\"

build:
	echo "Cleaning ..."
	make clean
	echo "Assembling bootloader ..."
	mkdir build
	mkdir build/klib
	mkdir build/drivers
	mkdir build/kshell
	nasm -felf32 -o build/bootloader.o boot/bootloader.asm -g
	echo "Assembling segments"
	nasm -felf32 -o build/segments.o memory/segments.asm -g
	echo "Assembling exception handlers"
	nasm -felf32 -o build/exceptions.o interrupts/exceptions.asm -g
	echo "Assembling IRQ handlers"
	nasm -felf32 -o build/irqs.o interrupts/irqs.asm -g
	echo "Compiling GDT"
	$(GCC) -c memory/gdt.c -o build/gdt.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling IDT"
	$(GCC) -c interrupts/idt.c -o build/idt.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling C common exception handler"
	$(GCC) -c interrupts/exceptionhandler.c -o build/exceptionhandler.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling C IRQ handler"
	$(GCC) -c interrupts/irq.c -o build/irq.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling PIC"
	$(GCC) -c interrupts/pic.c -o build/pic.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling watermark memory manager"
	$(GCC) -c memory/mm_watermark.c -o build/mm_watermark.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling segmentation memory manager"
	$(GCC) -c memory/mm_segmentation.c -o build/mm_segmentation.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling outb"
	$(GCC) -c ports/outb.c -o build/outb.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling inb"
	$(GCC) -c ports/inb.c -o build/inb.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling cpu"
	$(GCC) -c cpu/cpu.c -o build/cpu.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling CMOS driver"
	$(GCC) -c drivers/cmos/cmos.c -o build/drivers/cmos.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling RTC driver"
	$(GCC) -c drivers/rtc/rtc.c -o build/drivers/rtc.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling VGA driver ..."
	$(GCC) -c drivers/vga/vga.c -o build/drivers/vga.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling ATA driver"
	$(GCC) -c drivers/ata/ata.c -o build/drivers/ata.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling serial driver"
	$(GCC) -c drivers/serial/serial.c -o build/drivers/serial.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling keyboard driver ..."
	$(GCC) -c drivers/keyboard/keyboard.c -o build/drivers/keyboard.o $(GCC_INCLUDES) $(GCC_FLAGS)´
	echo "Compiling PIT driver"
	$(GCC) -c drivers/pit/pit.c -o build/drivers/pit.o $(GCC_INCLUDES) $(GCC_FLAGS)
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
	echo "Compiling kmem"
	$(GCC) -c klib/kmem.c -o build/klib/kmem.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling KFS"
	$(GCC) -c klib/kfs.c -o build/klib/kfs.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kshell"
	$(GCC) -c kshell/kshell.c -o build/kshell/kshell.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling process"
	$(GCC) -c multitasking/process.c -o build/process.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling tasks"
	$(GCC) -c multitasking/tasks.c -o build/tasks.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling driver_api"
	$(GCC) -c drivers/api/driver_api.c -o build/driver_api.o $(GCC_INCLUDES) $(GCC_FLAGS)	
	echo "Compiling api"
	$(GCC) -c drivers/api/api.c -o build/api.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling outw"
	$(GCC) -c ports/outw.c -o build/outw.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling inw"
	$(GCC) -c ports/inw.c -o build/inw.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling outdw"
	$(GCC) -c ports/outdw.c -o build/outdw.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling indw"
	$(GCC) -c ports/indw.c -o build/indw.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling pciio"
	$(GCC) -c drivers/pcidrivers/pci/pciio.c -o build/pciio.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling pci"
	$(GCC) -c drivers/pcidrivers/pci/pci.c -o build/pci.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kmath"
	$(GCC) -c klib/kmath.c -o build/kmath.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling machinespecficregister"
	$(GCC) -c ports/machineregister/machinespecficregister.c -o build/machinespecficregister.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Compiling kernel ..."
	$(GCC) -c kernel.c -o build/kernel.o $(GCC_INCLUDES) $(GCC_FLAGS)
	echo "Linking ..."
	
	$(GCC) -T linker.ld -o build/lfos.bin -ffreestanding -O2 -nostdlib -Wall build/bootloader.o build/kernel.o build/drivers/vga.o build/drivers/ata.o build/drivers/serial.o build/drivers/keyboard.o build/drivers/beeper.o build/drivers/pit.o build/drivers/rtc.o build/drivers/cmos.o build/klib/kio.o build/klib/kcom.o build/klib/kfs.o build/klib/kcasts.o build/klib/kstring.o build/klib/kmem.o build/klib/ktime.o build/kshell/kshell.o build/ufs.o build/mm_watermark.o build/mm_segmentation.o build/outb.o build/inb.o build/segments.o build/gdt.o build/idt.o build/exceptionhandler.o build/pic.o build/exceptions.o build/irqs.o build/irq.o build/cpu.o build/process.o build/tasks.o build/api.o build/driver_api.o build/inw.o build/outw.o build/outdw.o build/indw.o build/pciio.o build/pci.o build/kmath.o build/machinespecficregister.o -lgcc -Wl,-Map=build/memory.map
	
	echo "Stripping debug symbols from kernel ..."
	objcopy --only-keep-debug build/lfos.bin build/lfos.sym
	objcopy --strip-debug build/lfos.bin
	
clean:
	rm -rf build/
	
test:
	qemu-system-i386 -serial stdio -kernel build/lfos.bin

testATA:
	dd if=/dev/zero of=build/hdd.img count=4096
	qemu-system-i386 -smp cpus=2,cores=2 -kernel build/lfos.bin -serial stdio -drive file=build/hdd.img,if=ide

debug:
	qemu-system-i386 -serial stdio -kernel build/lfos.bin -s -S &
	gdb --symbols=build/lfos.sym --eval-command="target remote localhost:1234"
	killall qemu-system-i386
