.SILENT:mkiso

mkiso:
	cd ../; make
	echo "Copying kernel ..."
	cp ../kernel/build/lfos.bin isoroot/boot/
	echo "Creating iso image ..."
	grub-mkrescue -d /usr/lib/grub/i386-pc/ -o lfos.iso isoroot/
	
clean:
	rm -rf lfos.iso