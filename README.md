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
your own computer! TetrEFIs requires that a 640x480 video mode with 24-bit
blue-green-red color depth be available. If your UEFI firmware does not provide
this video mode, then tetrEFIs will fail to load.

To run in an emulator, drop `tetris.efi` into the root of this repo (or build it
from source) and run `make`. Note that this will call `sudo` on the provided
script `prepare-disk-image.sh` to create and mount a loopback device to prepare
a ~60MiB disk image with an EFI system partition on it.  Run `make run` in order
to load the disk image in QEMU.
