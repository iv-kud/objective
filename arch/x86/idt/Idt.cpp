#include "Idt.h"


uint64 MngIdt::idt[MngIdt::size];
bool MngIdt::isInitialize = false;
bool MngIdt::idtLoaded = false;
MngIdt mngIdt;

DescInterrupt32::DescInterrupt32(uint32 offset, uint16 selector, uint8 attr)
{
    uint8 gateType = attr & 0x0f;

    if((gateType == TSK_GATE and offset != 0)
        or gateType < TSK_GATE
        or (gateType > TRAP_GATE_16 and gateType < INT_GATE_32)
        or gateType > TRAP_GATE_32
        or !(attr & PRESENT_BIT))
    {
        offsetLow = 0;
        offsetHight = 0;
        segmentSelector = 0;
        attributes = 0;
    }
    else
    {
        offsetLow = offset & 0xffff;
        offsetHight = (offset & 0xffff0000) >> 16;
        segmentSelector = selector;
        attributes = attr;
    }
};

uint64 DescInterrupt32::getDescriptor()
{
    uint64 desc = 0;

    desc |= offsetLow;
    desc |= (uint32)segmentSelector << 16;
    desc |= (uint64)attributes << 40;
    desc |= (uint64)offsetHight << 48;

    return desc;
};

DescInterrupt32 DescInterrupt32::InterruptKernelLong(uint32 offset, uint16 selector)
{
    return DescInterrupt32(
                          offset,
                          selector,
                          PRESENT_BIT | RING_KERN | INT_GATE_32
                          );
};

DescInterrupt32 DescInterrupt32::TrapKernelLong(uint32 offset, uint16 selector)
{
    return DescInterrupt32(
                          offset,
                          selector,
                          PRESENT_BIT | RING_KERN | TRAP_GATE_32
                          );
};

DescInterrupt32 DescInterrupt32::TaskKernel(uint16 selector)
{
    return DescInterrupt32(
                          NULL,
                          selector,
                          PRESENT_BIT | RING_KERN | TSK_GATE
                          );
};

MngIdt::MngIdt()
{
    if(!isInitialize)
    {
        MemoryOperations::set(idt, 0, sizeof(uint64) * size);
        currIdx = NULL;
        idtLoaded = false;
        isInitialize = true;
    }
};

bool MngIdt::canDescriptorWrite(uint8 idx)
{
    if(idt[idx] or idtLoaded) return false;
    else return true;
};

bool MngIdt::addDescriptor(DescInterrupt32 desc)
{
    if(!canDescriptorWrite(currIdx)) return false;

    idt[currIdx++] = desc.getDescriptor();
    return true;
};

bool MngIdt::setDescriptor(DescInterrupt32 desc, uint8 idx)
{
    if(!canDescriptorWrite(idx)) return false;

    idt[idx] = desc.getDescriptor();
    return true;
};

bool MngIdt::loadIdt()
{
    if(idtLoaded) return false;

    //Set descriptor
    uint64 descriptor = 0;
    uint16 size = sizeof(uint64) * size - 1;
    uint32 offset = (uint32)(&idt);

    descriptor |= offset;
    descriptor <<= 16;
    descriptor |= size;

    // Load descriptor in LDTR
    asm ("lidt %0" :: "m"(descriptor));

    idtLoaded = true;
    return true;
};

// Get static instance of MngIdt initialized once
MngIdt &MngIdt::getInstance()
{
    if(!isInitialize) mngIdt = MngIdt();
    return mngIdt;
};
