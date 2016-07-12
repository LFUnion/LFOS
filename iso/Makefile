.SILENT:mkiso

mkiso:
	cd ../kernel/; make buildelf
	echo "Copying kernel ..."
	cp ../kernel/build/lfos.bin isoroot/boot/
	echo "Generating initrd ..."
	cd ../initrd; tar vcf ../iso/isoroot/boot/lfos_initrd.tar *
	echo "Creating iso image ..."
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o lfos.iso isoroot/
	
clean:
	rm -rf lfos.iso