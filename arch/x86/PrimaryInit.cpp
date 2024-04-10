#include "PrimaryInit.h"
#include "idt/Idt.h"
#include "io/VGADisplay.h"


struct InterruptFrame
{
#ifdef X86_64
    const uint64 ip;
    const uint64 cs;
    const uint64 flags;
#else
    const uint32 ip;
    const uint32 cs;
    const uint32 flags;
#endif
};

// Test ISRs define start
__attribute__((interrupt)) void isr0(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Divide error" << '\n';
};

__attribute__((interrupt)) void isr1(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Debug exception" << '\n';
};

__attribute__((interrupt)) void isr2(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "NMI interrupt" << '\n';
};

__attribute__((interrupt)) void isr3(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Breakpoint" << '\n';
};

__attribute__((interrupt)) void isr4(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Overflow" << '\n';
};

__attribute__((interrupt)) void isr5(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Bound range exceed" << '\n';
};

__attribute__((interrupt)) void isr6(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Invalid opcode" << '\n';
};

__attribute__((interrupt)) void isr7(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "No math coprocessor" << '\n';
};

__attribute__((interrupt)) void isr8(struct InterruptFrame *frame, uword errorCode)
{
    asm("cli\n\t");
    out::display << "Double fault" << '\n';
};

__attribute__((interrupt)) void isr10(struct InterruptFrame *frame, uword errorCode)
{
    asm("cli\n\t");
    out::display << "Invalid TSS" << "\n";
};

__attribute__((interrupt)) void isr11(struct InterruptFrame *frame, uword errorCode)
{
    asm("cli\n\t");
    out::display << "Segment not present" << "\n";
};

__attribute__((interrupt)) void isr12(struct InterruptFrame *frame, uword errorCode)
{
    asm("cli\n\t");
    out::display << "Stack segment fault" << "\n";
};

__attribute__((interrupt)) void isr13(struct InterruptFrame *frame, uword errorCode)
{
    asm("cli\n\t");
    out::display << "#GP" << "\n";
};

__attribute__((interrupt)) void isr14(struct InterruptFrame *frame, uword errorCode)
{
    asm("cli\n\t");
    out::display << "Page fault" << "\n";
};

__attribute__((interrupt)) void isr16(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Math fault" << "\n";
};

__attribute__((interrupt)) void isr17(struct InterruptFrame *frame, uword errorCode)
{
    asm("cli\n\t");
    out::display << "Alignment check" << "\n";
};

__attribute__((interrupt)) void isr18(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Machine check" << "\n";
};

__attribute__((interrupt)) void isr19(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "SIMD point exception" << "\n";
};

__attribute__((interrupt)) void isr20(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Virtualization exception" << "\n";
};

__attribute__((interrupt)) void isr21(struct InterruptFrame *frame, uword errorCode)
{
    asm("cli\n\t");
    out::display << "Control protection exception" << "\n";
};

__attribute__((interrupt)) void isrUser(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "User-defined interrupt" << "\n";
};

__attribute__((interrupt)) void isrKeyboard(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "KINT ";
    uint8 buff[2];

    // PIC write EOI
    asm("in $0x60, %al");
    asm("mov %%al, %0" : "=r"(buff[0]));
    asm("in $0x64, %al");
    asm("mov %%al, %0" : "=r"(buff[1]));
    asm("mov $0x20, %al\n\t");
    asm("outb %al, $0x20\n\t");
    out::display << (uint32)buff[0] << ' ' << (uint32)buff[1] << '\n';
};
__attribute__((interrupt)) void isrTimer(struct InterruptFrame *frame)
{
    asm("cli\n\t");
    out::display << "Timer interrupt" << "\n";
};
//Test ISRs define end -------------------

void PrimaryInitialization::processorInitialize()
{
    MngIdt &mngIdt = MngIdt::getInstance();
    MngGdt &mngGdt = MngGdt::getInstance();

    mngGdt.addDescriptor(DescSeg32::flatCodeKernel());
    mngGdt.addDescriptor(DescSeg32::flatDataKernel());
    mngGdt.loadGdt();

// Filling IDT start !!!REWRITE!!
    DescInterrupt32 descInt = DescInterrupt32::TrapKernelLong
                              (
                                (uint32)isr0,
                                mngGdt.getCodeSegmentKernel()
                              );
    // Int 0
    mngIdt.addDescriptor(descInt);

    // Int 1
    descInt.setOffset((uint32)isr1);
    mngIdt.addDescriptor(descInt);

    // Int 2
    descInt.setOffset((uint32)isr2);
    mngIdt.addDescriptor(descInt);

    // Int 3
    descInt.setOffset((uint32)isr3);
    mngIdt.addDescriptor(descInt);

    // Int 4
    descInt.setOffset((uint32)isr4);
    mngIdt.addDescriptor(descInt);

    // Int 5
    descInt.setOffset((uint32)isr5);
    mngIdt.addDescriptor(descInt);

    // Int 6
    descInt.setOffset((uint32)isr6);
    mngIdt.addDescriptor(descInt);

    // Int 7
    descInt.setOffset((uint32)isr7);
    mngIdt.addDescriptor(descInt);

    // Int 8
    descInt.setOffset((uint32)isr8);
    mngIdt.addDescriptor(descInt);

    // Int 10
    descInt.setOffset((uint32)isr10);
    mngIdt.addDescriptor(descInt);

    // Int 11
    descInt.setOffset((uint32)isr11);
    mngIdt.addDescriptor(descInt);

    // Int 12
    descInt.setOffset((uint32)isr12);
    mngIdt.addDescriptor(descInt);

    // Int 13
    descInt.setOffset((uint32)isr13);
    mngIdt.addDescriptor(descInt);

    // Int 14
    descInt.setOffset((uint32)isr14);
    mngIdt.addDescriptor(descInt);

    // Int 16
    descInt.setOffset((uint32)isr16);
    mngIdt.addDescriptor(descInt);

    // Int 17
    descInt.setOffset((uint32)isr17);
    mngIdt.addDescriptor(descInt);

    // Int 18
    descInt.setOffset((uint32)isr18);
    mngIdt.addDescriptor(descInt);

    // Int 19
    descInt.setOffset((uint32)isr19);
    mngIdt.addDescriptor(descInt);

    // Int 20
    descInt.setOffset((uint32)isr20);
    mngIdt.addDescriptor(descInt);

    // Int 21
    descInt.setOffset((uint32)isr21);
    mngIdt.addDescriptor(descInt);

    // Int 32
    descInt.setOffset((uint32)isrTimer);
    mngIdt.setDescriptor(descInt, 32);

    // Int 33
    descInt.setOffset((uint32)isrKeyboard);
    mngIdt.setDescriptor(descInt, 33);
//Filling IDT end ------------------------------

    mngIdt.loadIdt();

//------------
};

void PrimaryInitialization::devicesInitialize()
{
    out::display = VGADisplay();
};
