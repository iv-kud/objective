#ifndef IDT_H
#define IDT_H


#include "../gdt/Gdt.h"
#include <MemoryOperations.h>

// Defines

// Attributes
#define TSK_GATE 0x5
#define INT_GATE_16 0x6
#define TRAP_GATE_16 0x7
#define INT_GATE_32 0xe
#define TRAP_GATE_32 0xf
#define PRESENT_BIT 0x80
#define RING_KERN 0
#define RING_DRIVERSH 0x20
#define RING_DRIVERSL 0x40
#define RING_APP 0x60

//--------

class DescInterrupt32
{
    private:
        uint16 offsetLow;
        uint16 segmentSelector;
        uint8 attributes;
        uint16 offsetHight;
    public:
        DescInterrupt32() = default;
        DescInterrupt32(const DescInterrupt32 &) = default; 
        DescInterrupt32(uint32 offset, uint16 selector, uint8 attr);
        uint64 getDescriptor();
        static DescInterrupt32 InterruptKernelLong(uint32 offset, 
                                                    uint16 selector);
        static DescInterrupt32 TrapKernelLong(uint32 offset,
                                                    uint16 selector);
        static DescInterrupt32 TaskKernel(uint16 selector);
};

class MngIdt
{
    private:
        const static uint8 size = 255;
        static uint64 idt[size];
        static bool isInitialize;
        static bool idtLoaded;
        uint8 currIdx;
    public:
        MngIdt();
        MngIdt(const MngIdt &) = delete;
        bool addDescriptor(DescInterrupt32 desc);
        bool setDescriptor(DescInterrupt32 desc, uint8 idx);
        bool canDescriptorWrite(uint8 idx);
        bool loadIdt();
        static MngIdt &getInstance();
};

extern MngIdt mngIdt;

#endif
