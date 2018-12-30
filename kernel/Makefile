QEMU=qemu-system-x86_64 -cpu qemu64
CC=clang
LD=ld
OVMF=ovmf
DISK=disk.img

EFI_INCLUDES=\
	-I/usr/include/efi \
	-I/usr/include/efi/protocol \
	-I/usr/include/efi/x86_64

EFI_CFLAGS=\
	-ffreestanding \
	-fno-stack-protector \
	-fpic \
	-DHAVE_USE_MS_ABI \
	-fshort-wchar \
	-mno-red-zone \
	$(EFI_INCLUDES)

EFI_CRT_OBJ=/usr/lib/crt0-efi-x86_64.o
EFI_LDS=/usr/lib/elf_x86_64_efi.lds

# linker flags for building EFI application:
# - We don't link in the C library.
# - An EFI application is built as a shared object, and uses efi_main as
#   its entry point.
# - subsystem 10 is for EFI application
# - We need to use the absolute path to libgnuefi.a since -l will look
#   in the ldpath for the *cross*-compiler, which doesn't have gnu-efi
#   installed. But luckily this library is portable since it doesn't
#   have any dependencies.
EFI_LDFLAGS=\
	-nostdlib \
	-znocombreloc \
	-T $(EFI_LDS) \
	-shared \
	-Bsymbolic \
	-L/usr/lib

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
	-rm *.img *.o *.EFI

base-$(DISK).img:
	dd if=/dev/zero of=$@ bs=1k count=$(DISKSIZE)

tetris.efi: tetris.so
	objcopy -j .text -j .sdata -j .data \
  -j .dynamic -j .dynsym  -j .rel \
  -j .rela -j .reloc -j .eh_frame \
  --target=efi-app-x86_64 $^ $@

tetris.so: hello.o
	$(LD) -o $@ $(EFI_CRT_OBJ) $^ $(EFI_LDFLAGS) -lefi -lgnuefi

hello.o: hello.c
	$(CC) $(EFI_CFLAGS) -c -o $@ $^

.PHONY: run
run: disk.img
	$(QEMU) \
		-drive if=pflash,format=raw,unit=0,file=$(OVMF)/OVMF_CODE.fd,readonly=on \
		-drive if=pflash,format=raw,unit=1,file=$(OVMF)/OVMF_VARS.fd \
		-drive if=ide,file=disk.img,format=raw \
		-net none
