#ifdef __cplusplus
extern "C" {
#endif

#include "../arch/x86/io/GlobalObj.h"
#include "../arch/x86/inc/TypeConverter.h"

void main()
{
    VGADisplay d;
    IntConverter conv;

    unsigned int i = 124;

    d << conv.intToChar(i);
    d << "Hello, world!\tHello, world!";
    for(int i = 0; i < 10; i++)d << "\tHello!";
};

#ifdef __cplusplus
};
#endif
