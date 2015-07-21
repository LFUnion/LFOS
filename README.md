# LFOS
![Image](http://lfunion.bplaced.net/SmartImage/image.php?category=License&description=GPL3&color=083)
![Image](http://lfunion.bplaced.net/SmartImage/image.php?category=Stars&description=0&color=C93)
![Image](http://lfunion.bplaced.net/SmartImage/image.php?category=Forks&description=0)

LFOS, a simple operating system.
Copyright (C) 2015 LFUnion.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version. See http://www.gnu.org/licenses/.

### Build
You can find daily builds at https://github.com/lfunion/lfos-hourly.

### Version
This is a screenshot of the version:

![Image](http://lfunion.bplaced.net/githubimages/lfos.png)

### How can I contribute?
You have to install software to compile LFOS. Here are the steps for Arch Linux:

`pacman -S nasm`

`yaourt -S lzip`

`pacman -S qemu`

`pacman -S base-devel`

`pacman -S mpfr`

The following part is a bit complicated. You have to change the PKGBUILD file of the package, and remove all lines that contain the
string "mpfr". (Don't forget to update the SHA-checksums)

`yaourt -S i686-elf-gcc`


We'll accept useful push requests. We need developers, so if you 
want to contribute, contact us at <lfunion@web.de>.

## Documentation
This is the documentation for all files and functions in the `kernel/` folder.

### `boot/`
This folder contains the bootloader for LFOS.

### `includes/`
In this folder are the **Kernel** header. They won´t be usable in 
userspace. Use the clib for userspace applications.

### `clib/`
This is the place of the c library.

### `ports/`
The basic hardware port communication system.

### `vga/`
This folder contains the VGA driver. We might change the location to 
`drivers/vga`.
