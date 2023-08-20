CC = i686-elf-g++# compiler
LD = ld# linker
ASM = nasm# assembler
# test -O2 flag
CFLAGS = -c -m32 -Wall -ffreestanding -nostdinc -nostdlib -lgcc# c compiler flags
# flag elf32 allow decrease object file size
AFLAGS = -f elf32# asm compiler flags
BDIR = build# build directory

.PHONY: install

install: build
	@echo "Creating an iso image of OS"
	cp ./$(BDIR)/kernel.bin ./iso/os/
	grub-mkrescue -o ./$(BDIR)/kernel.iso ./iso

build:
	mkdir $(BDIR) 
	@echo "Compile source files..."
	$(CC) $(CFLAGS) -o ./$(BDIR)/kernel.o ./kernel/kernel.c
	$(CC) $(CFLAGS) -o ./$(BDIR)/VGADisplay.o ./arch/x86/io/VGADisplay.cpp
	$(CC) $(CFLAGS) -o ./$(BDIR)/TypeConverter.o ./arch/x86/inc/TypeConverter.cpp
	$(CC) $(CFLAGS) -o ./$(BDIR)/GlobalObj.o ./arch/x86/io/GlobalObj.cpp
	$(ASM) $(AFLAGS) -o ./$(BDIR)/boot.o ./kernel/boot.s
	@echo "Link object files..."
	$(LD) -m elf_i386 -o ./$(BDIR)/kernel.bin -T ./kernel/linker.ld ./$(BDIR)/*.o
	@echo "Project was built"

clean:
	rm -rf ./build

run:
	 qemu-system-i386 -cdrom ./$(BDIR)/kernel.iso
