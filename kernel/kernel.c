#include "GlobalConstruct.h"
#include <TypeConverter.h>
#include <types.h>

#include "../arch/x86/cpuinfo/Cpuinfo.h"

void main()
{
    GlobalConstruct::terminalInit();
    GlobalConstruct::gdtInit();
    Cpuinfo cpuinf;
};
