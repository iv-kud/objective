#include "gdt/Gdt.h"
#include "io/VGADisplay.h"


class PrimaryInitialization
{
    protected:
        virtual void processorInitialize();
        virtual void devicesInitialize();
};
