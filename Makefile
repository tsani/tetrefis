QEMU=qemu-system-x86_64 -cpu qemu64
CC=clang
LD=ld
OVMF=ovmf
DISK=disk.img

EFI_INCLUDES=\
	-Ivendor/include/efi \
	-Ivendor/include/efi/protocol \
	-Ivendor/include/efi/x86_64

EFI_CFLAGS=\
	-Wall \
	-Werror \
	-ffreestanding \
	-fno-stack-protector \
	-fpic \
	-DHAVE_USE_MS_ABI \
	-fshort-wchar \
	-mno-red-zone \
	$(EFI_INCLUDES)

EFI_CRT_OBJ=vendor/lib/crt0-efi-x86_64.o
EFI_LDS=vendor/lib/elf_x86_64_efi.lds

# linker flags for building EFI application:
# - We don't link in the standard library
# - We don't combine relocations
# - We use the custom ld script provided by gnu-efi
# - we build a shared object file
# - I don't really understand -Bsymbolic, but if I remove it then ld
#   complains about failing to process some relocations
EFI_LDFLAGS=\
	-nostdlib \
	-znocombreloc \
	-T $(EFI_LDS) \
	-shared \
	-Bsymbolic \
	-Lvendor/lib

# Sizes are in KiB
DISKSIZE=60000 # ~60 MiB

# The complete disk image.
$(DISK): tetris.efi base-$(DISK) layout.sfdisk
	cp -u base-$(DISK) $@
  # scripted fdisk command to create a gpt disk image and partition
	sfdisk $@ < layout.sfdisk
  # use a separate script run as root (to mount loopback devices and so on)
  # to actually construct the disk image
	sudo ./prepare-disk-image.sh

.PHONY: clean
clean:
	-rm *.img *.o *.efi

# constructs the base (empty) disk image
base-$(DISK):
	dd if=/dev/zero of=$@ bs=1k count=$(DISKSIZE)

# convert ELF shared object file into an EFI PE file
%.efi: %.so
	objcopy -j .text -j .sdata -j .data \
  -j .dynamic -j .dynsym  -j .rel \
  -j .rela -j .reloc -j .eh_frame \
  --target=efi-app-x86_64 $^ $@

tetris.so: main.o screen.o tetris.o rng.o time.o blocks.o basic_types.o input.o text.o
	$(LD) -o $@ $(EFI_CRT_OBJ) $^ $(EFI_LDFLAGS) -lefi -lgnuefi

%.o: %.c
	$(CC) $(EFI_CFLAGS) -c -o $@ $^

.PHONY: run
run: disk.img
	$(QEMU) \
		-drive if=pflash,format=raw,unit=0,file=$(OVMF)/OVMF_CODE.fd,readonly=on \
		-drive if=pflash,format=raw,unit=1,file=$(OVMF)/OVMF_VARS.fd \
		-drive if=ide,file=disk.img,format=raw \
		-net none
