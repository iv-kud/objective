#include "gdt/Gdt.h"
#include "io/VGADisplay.h"


#define x86_ARCH

class PrimaryInitialization
{
    protected:
        virtual void processorInitialize();
        virtual void devicesInitialize();
};
