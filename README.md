# LFOS
![Image](https://img.shields.io/badge/license-GPL-brightgreen.svg)
![Image](https://img.shields.io/github/release/LFUnion/lfos.svg)
![Image](https://b0939017.ngrok.io/job/LFOS/badge/icon)

LFOS, a simple operating system.
Copyright (C) 2015 LFUnion.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version. See http://www.gnu.org/licenses/.

### Build
Builds are on the LFUnion jenkins server at https://b0939017.ngrok.io

### Documentation
The documentation can be found at http://lfunion.bplaced.net/lfos/doc/html/

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


We'll accept useful pull requests. We need developers, so if you 
want to contribute, contact us at <lfunion@web.de>.
