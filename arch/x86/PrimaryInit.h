#include "gdt/Gdt.h"
#include "io/VGADisplay.h"
#include "idt/Idt.h"


class PrimaryInitialization
{
    protected:
        virtual void processorInitialize();
        virtual void devicesInitialize();
};
