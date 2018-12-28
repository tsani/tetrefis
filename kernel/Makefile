CC=x86_64-w64-mingw32-gcc

EFICFLAGS=-ffreestanding -I/usr/include/efi -I/usr/include/efi/protocol -I/usr/include/efi/x86_64
EFILDFLAGS=-nostdlib -Wl,-dll -shared -Wl,--subsystem=10 -e efi_main /usr/lib/libgnuefi.a -lgcc

part.img: BOOTX64.EFI
	dd if=/dev/zero of=$@ bs=1k count=1440 # floppy disk size
	mformat -i $@ -f 1440 ::
	mmd -i $@ ::/EFI
	mmd -i $@ ::/EFI/BOOT
	mcopy -i $@ $< ::/EFI/BOOT

BOOTX64.EFI: hello.o
	$(CC) -o $@ $^ $(EFILDFLAGS) 

hello.o: hello.c
	$(CC) $(EFICFLAGS) -c -o $@ $^
