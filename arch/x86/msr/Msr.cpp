#include "Msr.h"

Msr::Msr()
{
    Cpuinfo cpuinfo;
    cpuinfo.cpuid(Cpuinfo::VersionInfo);

    msrSupport = cpuinfo.getRegs().edx & Cpuinfo::MSR;
};

bool Msr::rdmsr(MsrCommand *cmd)
{
    if(!msrSupport or cmd == nullptr) return true;

    uint64 rdmsrResult = 0;
    uint32 regs[2];
    asm(
        "mov %2, %%ecx\n\t"
        "rdmsr\n\t"
        "mov %%eax, %0\n\t"
        "mov %%edx, %1\n\t"
        : "=&r"(regs[0]), "=&r"(regs[1])
        : "r"(cmd->getCommand()));

    MemoryOperations::copy(regs, &rdmsrResult, sizeof(uint64));
    cmd->decode(rdmsrResult);

    return false;
};

bool Msr::wrmsr(MsrCommand *cmd)
{
    if(!msrSupport or cmd == nullptr) return true;

    uint32 regs[2];
    uint64 msr = cmd->getMsr();

    MemoryOperations::copy(&msr, regs, sizeof(uint64));

    asm(
        "mov %0, %%eax\n\t"
        "mov %1, %%edx\n\t"
        "mov %2, %%ecx\n\t"
        "wrmsr\n\t"
        : "=r"(regs[0]), "=r"(regs[1])
        : "r"(cmd->getCommand()));

    return false;
};

Ia32ApicBase::Ia32ApicBase()
{
    Cpuinfo cpuinfo;
    bool cpuidAddrSzNotSupport = cpuinfo.cpuid(Cpuinfo::AddressSize);
    cpuidOutputRegisters AddrSzRegs = cpuinfo.getRegs();

    cpuinfo.cpuid(Cpuinfo::VersionInfo);
    if(cpuinfo.getRegs().edx & Cpuinfo::PAE
        and cpuidAddrSzNotSupport) maxPhyAddr = 36;
    else if(cpuidAddrSzNotSupport) maxPhyAddr = 32;
    else if(!cpuidAddrSzNotSupport) maxPhyAddr = (uint8)AddrSzRegs.edx;

    bspFlag = enableFlag = false;
    baseField = NULL;
};

uint32 Ia32ApicBase::getCommand()
{
    return 0x1b;
};

void Ia32ApicBase::decode(uint64 rdmsrResult)
{
    bspFlag = rdmsrResult & BSP_FLAG;
    enableFlag = rdmsrResult & APIC_ENABLE_FLAG;
    setBaseField(rdmsrResult);
};

uint64 Ia32ApicBase::getMsr()
{
    uint64 msr = 0;

    MemoryOperations::copy(&baseField, &msr, sizeof(uint64));
    msr |= bspFlag << 8;
    msr |= enableFlag << 11;

    return msr;
};

void Ia32ApicBase::setBaseField(uint64 fieldAddr)
{
    uint64 mask = BASE_FIELD_MASK_LOW | 
                    ((UINT64_HIGH<< (maxPhyAddr - 32)) ^ UINT64_HIGH);

    baseField = fieldAddr & mask;
};

void Ia32ApicBase::setBspFlag(bool flag)
{
    bspFlag = flag;
};

void Ia32ApicBase::setEnableFlag(bool flag)
{
    enableFlag = flag;
};
