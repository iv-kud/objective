#include "StringOperations.h"


MemArea::MemArea()
{
    start = final = NULL;
};

MemArea::MemArea(const uintptr start, const uintptr final)
{
    this->start = start;
    this->final = final;

    if(!valid())
    {
        *this = MemArea();
    }
};

uintptr MemArea::begin()
{
    return start;
}

uintptr MemArea::end()
{
    if(start == final) return start;
    else return final + 1;
};

bool MemArea::valid()
{
    if(start > final
        or start == NULL
        or final == NULL) return false;
    else return true;
};

uint32 StringOperations::sequenceSize(const char *chars)
{
    uint32 indx = 0;
    while(chars[indx++]){}

    return --indx;
};

void *StringOperations::findInMemory(const char *sequence, MemArea memory)
{
    if(sequence == nullptr or !memory.valid()) return NULL;

    uint32 seqIndx = 0;
    for(MemArea::iterator it = memory.begin(); it != memory.end(); it++)
    {
        char ch = sequence[seqIndx], chMem = (*((char *)it));

        if(ch == '\0') return (void *)(it - sequenceSize(sequence));
        else if(ch != chMem)
        {
            seqIndx = 0;
        }
        else if(ch == chMem)
        {
            seqIndx++;
        }
    }
    return NULL;
};
