#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <types.h>


class MemArea
{
    private:
        memAddr start, final;
    public:
        MemArea();
        MemArea(const memAddr start, const memAddr final);
        memAddr begin();
        memAddr end();
        bool valid();

        typedef memAddr iterator;
};

class StringOperations
{
    public:
        // Return the starting address where is sequence is allocated
        // else NULL
        static void *findInMemory(const char *sequence, MemArea memory);
        // Return size of ASCIZ sequence without 0-symbol, NULL on failure
        static uint32 sequenceSize(const char *chars);
};

#endif
