## Object Operating System

----

## Install dependencies

#### Ubuntu

```sh
sudo apt update -y
sudo apt -y install build-essential binutils nasm xorriso grub-common qemu-system-i386 mtools
```

## Build and run

#### Ubuntu

```sh
# Build and create iso image
make install  
make run
```

## Docs

-   [Link on collection of articles "How startup app without OS"][1]
-   [The GNU GRUB manual][2]
-   [Executable and linkable format ELF][3]
-   [NASM documentation][4]
-   [Article where creating a simple OS][5]
-   [Multiboot specification][6]
-   [GCC compiler documentation][7]
-   [Using NASM in a Hello World kernel][8]

[1]:https://habr.com/ru/companies/neobit/articles/173263/
[2]:https://www.gnu.org/software/grub/manual/grub/grub.pdf
[3]:https://www.cs.cmu.edu/afs/cs/academic/class/15213-f00/docs/elf.pdf
[4]:https://www.nasm.us/xdoc/2.16.01/nasmdoc.pdf
[5]:https://wiki.osdev.org/Bare_Bones#Writing_a_kernel_in_C.2B.2B
[6]:https://www.gnu.org/software/grub/manual/multiboot/multiboot.pdf
[7]:https://gcc.gnu.org/onlinedocs/gcc.pdf
[8]:https://wiki.osdev.org/Bare_Bones_with_NASM
