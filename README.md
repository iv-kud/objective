## Objective Operating System

## Install dependencies

#### Ubuntu

```sh
sudo apt update -y
sudo apt -y install build-essential binutils nasm xorriso grub-common qemu-system-i386 mtools
```

You need to build GCC cross compiler for i686 or x86_64 supports x32 architecture/s to compile from sources.
Also required gcc and stdc++ libraries.
Refer to GCC documentation for detailed information - <https://gcc.gnu.org/install/>

## Build and run

Before build the project set some variables - DEBUG and LIBS_PATH.  
These variables may pass through *make* command `make *variables* *rule*`, or usage environment variables `export *name*=*value*`.

#### Variables

1. DEBUG. Not takes value. If defineв, the debug version of the project will be build, otherwise the release version. Responsible for the debug version of the project to test OS via GDB.
2. LIBS_PATH. Takes the path to the required libraries. Now gcc library is required, supplied with the compiled.

#### Ubuntu

Build and run release version
```sh
make all
```

Build and run debug version
```sh
make DEBUG=* all
```
or
```sh
export DEBUG=*
make all
```

## Docs

-   [Link on collection of articles "How startup app without OS"][1]
-   [The GNU GRUB manual][2]
-   [Executable and linkable format ELF][3]
-   [NASM documentation][4]
-   [Article about creatiing a simple OS][5]
-   [Multiboot specification][6]
-   [GCC compiler documentation][7]
-   [Using NASM in a Hello World kernel][8]
-   [Video memory ports x86][9]

[1]:https://habr.com/ru/companies/neobit/articles/173263/
[2]:https://www.gnu.org/software/grub/manual/grub/grub.pdf
[3]:https://www.cs.cmu.edu/afs/cs/academic/class/15213-f00/docs/elf.pdf
[4]:https://www.nasm.us/xdoc/2.16.01/nasmdoc.pdf
[5]:https://wiki.osdev.org/Bare_Bones#Writing_a_kernel_in_C.2B.2B
[6]:https://www.gnu.org/software/grub/manual/multiboot/multiboot.pdf
[7]:https://gcc.gnu.org/onlinedocs/gcc.pdf
[8]:https://wiki.osdev.org/Bare_Bones_with_NASM
[9]:https://stackoverflow.com/questions/17367618/address-of-video-memory
