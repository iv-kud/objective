#include <MemoryOperations.h>

uint32 MemoryOperations::copy(void *source, void *destination, uint32 sizeBytes)
{
    if(source == nullptr || destination == nullptr) return NULL;

    char *src = (char *)source, *dst = (char*)destination;

    uint32 byteNumber = 1;
    while(byteNumber <= sizeBytes)
    {
        dst[byteNumber - 1] = src[byteNumber - 1];
        byteNumber++;
    }

    return byteNumber;
};

uint32 MemoryOperations::set(void *field, uint8 value, uint32 sizeBytes)
{
    if(field == nullptr) return NULL;

    char *charField = (char*)field;

    uint32 byteNumber = 1;
    while(byteNumber <= sizeBytes)
    {
        charField[byteNumber - 1] = value;
        byteNumber++;
    }

    return byteNumber;
};
