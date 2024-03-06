#include "PrimaryInit.h"


void PrimaryInitialization::processorInitialize()
{
    MngGdt mngGdt = MngGdt();

    mngGdt.addDescriptor(DescSeg32::flatCodeKernel());
    mngGdt.addDescriptor(DescSeg32::flatDataKernel());
    mngGdt.loadGdt();
};

void PrimaryInitialization::devicesInitialize()
{
    out::display = VGADisplay();
};
