#ifndef GLOBALCONSTRUCT_H
#define GLOBALCONSTRUCT_H

#include "../arch/x86/io/GlobalObj.h"
#include "../arch/x86/gdt/GlobalObj.h"

class GlobalConstruct
{
    public:
        static void terminalInit();
        static void gdtInit();
};

#endif
