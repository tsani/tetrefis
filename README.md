tetrEFIs
========

Tetris as an EFI application.

Inspired by [tetrasm](https://github.com/programble/tetrasm).

![Screenshot](https://raw.githubusercontent.com/tsani/tetrefis/master/screenshot.png)

Features
--------

* Full glorious 640x480 graphics mode
* Scoring
* Custom proportional font
* Levels with increasing gravity
* Clockwise and counterclockwise rotation
* Next piece preview

Binaries
--------

The EFI application is available on the
[releases](https://github.com/tsani/tetrefis/releases) page.
If you drop this into your EFI system partition, you should be able to play on
your own computer! Tetrefis requires that a 640x480 video mode with 24-bit
blue-green-red color depth be available. If your UEFI firmware does not provide
this video mode, then tetrefis will fail to load.

Building from source
--------------------

The Makefile uses `clang` and `ld`. All dependencies, viz. the gnu-efi library,
is included in this repo.
To build only the EFI application, run `make tetris.efi`.
Since the default make target is the runnable disk image, run `make` to build
`disk.img`.

Running in QEMU
---------------

To run in an emulator, drop `tetris.efi` into the root of this repo (or build it
from source) and run `make` to build disk image `disk.img`.
Note that this will call `sudo` on the provided script `prepare-disk-image.sh`
to create and mount a loopback device to prepare a ~60MiB disk image with an EFI
system partition on it.  Run `make run` in order to load the disk image in QEMU.

In QEMU, the TianoCore OVMF splash screen should appear. At the countdown, hit
return. The `FS0:` drive should be listed. This means that the firmware
detected the EFI system partition. Switch to it typing `FS0:` followed by the
return key. Then, launch the EFI application by typing `tetris.efi` followed by
return.

License
-------

Copyright 2019 Jacob Thomas Errington

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
