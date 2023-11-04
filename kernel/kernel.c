#include "GlobalConstruct.h"
#include "../arch/x86/io/GlobalObj.h"
#include "../arch/x86/inc/TypeConverter.h"

void main()
{
    GlobalConstruct::terminalInit();
    GlobalConstruct::gdtInit();

    display << "Hello, World!";

};

