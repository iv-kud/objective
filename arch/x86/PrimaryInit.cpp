#include "PrimaryInit.h"
#include "idt/Idt.h"


// Function to test idt work. Should remove
void isr()
{
    out::display << "The kernel has finished" << '\n';
};

void PrimaryInitialization::processorInitialize()
{
    MngIdt &mngIdt = MngIdt::getInstance();
    MngGdt &mngGdt = MngGdt::getInstance();

    mngGdt.addDescriptor(DescSeg32::flatCodeKernel());
    mngGdt.addDescriptor(DescSeg32::flatDataKernel());
    mngGdt.loadGdt();

    mngIdt.setDescriptor(
        DescInterrupt32::InterruptKernelLong(
            (uint32)isr, 
            mngGdt.getCodeSegmentKernel()),
         0x20);
    mngIdt.loadIdt();
};

void PrimaryInitialization::devicesInitialize()
{
    out::display = VGADisplay();
};
