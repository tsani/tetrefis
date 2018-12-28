#!/bin/bash

set -e

DEV=$(losetup --find --partscan --show disk.img)
mkfs.fat -F 32 ${DEV}p1
mount ${DEV}p1 mnt
cp tetris.efi mnt
umount mnt
sync
losetup -d $DEV
