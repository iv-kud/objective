CC = gcc# compiler
LD = ld# linker
ASM = nasm# assembler
# what is the flag -O2 
CFLAGS = -c -Wall -ffreestanding -nostdinc -nostdlib -lgcc# c compiler flags
# flag elf32 allow decrease object file size
AFLAGS = -f elf64# asm compiler flags
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
	$(ASM) $(AFLAGS) -o ./$(BDIR)/boot.o ./kernel/boot.s
	@echo "Link object files..."
	$(LD) -m elf_x86_64 -o ./$(BDIR)/kernel.bin -T ./kernel/linker.ld ./$(BDIR)/*.o
	@echo "Project was built"

clean:
	rm -rf ./build

run:
	 qemu-system-i386 -cdrom ./$(BDIR)/kernel.iso
