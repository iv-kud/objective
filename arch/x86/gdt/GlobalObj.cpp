#include "GlobalObj.h"


uint64 MngGdt::gdt[MngGdt::size];

MngGdt mngGdt;

void mngGdtInit()
{
    if(!mngGdt.getIsGdtLoaded())
    {
        mngGdt = MngGdt();
    }
};
