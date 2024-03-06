#include "../arch/SecondaryInit.h"

#include "../arch/x86/cpuinfo/Cpuinfo.h"

void main()
{
    SecondaryInitialization init;

    init.processorInitialize();
    init.devicesInitialize();

    out::display << "Hello, World!\n";
};
