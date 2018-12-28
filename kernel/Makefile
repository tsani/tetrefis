QEMU=qemu-system-x86_64 -cpu qemu64
CC=x86_64-w64-mingw32-gcc
OVMF=ovmf
DISK=disk.img

# C compilation flags for building EFI application:
# - The application is freestanding (no stdlib)
# - 
EFICFLAGS=\
	-ffreestanding \
	-I/usr/include/efi \
	-I/usr/include/efi/protocol \
	-I/usr/include/efi/x86_64

# linker flags for building EFI application:
# - We don't link in the C library.
# - An EFI application is built as a shared object, and uses efi_main as
#   its entry point.
# - subsystem 10 is for EFI application
# - We need to use the absolute path to libgnuefi.a since -l will look
#   in the ldpath for the *cross*-compiler, which doesn't have gnu-efi
#   installed. But luckily this library is portable since it doesn't
#   have any dependencies.
EFILDFLAGS=\
	-nostdlib \
	-Wl,-dll \
	-shared \
	-Wl,--subsystem=10 \
	-e efi_main \
	/usr/lib/libgnuefi.a -lgcc

# Sizes are in KiB
DISKSIZE=60000

# The complete disk image.
$(DISK): tetris.efi base-$(DISK).img layout.sfdisk
	cp -u base-$(DISK).img $@
	sfdisk $@ < layout.sfdisk
  # scripted fdisk command to create a gpt disk image and partition
  # write the partition into the disk image at the correct location
	sudo ./prepare-disk-image.sh

.PHONY: clean
clean:
	rm *.img *.o *.EFI

base-$(DISK).img:
	dd if=/dev/zero of=$@ bs=1k count=$(DISKSIZE)

tetris.efi: hello.o
	$(CC) -o $@ $^ $(EFILDFLAGS) 

hello.o: hello.c
	$(CC) $(EFICFLAGS) -c -o $@ $^

.PHONY: run
run: disk.img
	$(QEMU) \
		-drive if=pflash,format=raw,unit=0,file=$(OVMF)/OVMF_CODE.fd,readonly=on \
		-drive if=pflash,format=raw,unit=1,file=$(OVMF)/OVMF_VARS.fd \
		-drive if=ide,file=disk.img,format=raw \
		-net none
