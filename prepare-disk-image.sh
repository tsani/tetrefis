#!/bin/bash

set -e

# prepare a loopback device for disk.img
DEV=$(losetup --find --partscan --show disk.img)
# format the EFI system partition as FAT32
mkfs.fat -F 32 ${DEV}p1
# mount it and copy the tetris EFI application
mkdir -p mnt
mount ${DEV}p1 mnt
cp tetris.efi mnt
umount mnt
sync
# remove the loopback device
losetup -d $DEV
