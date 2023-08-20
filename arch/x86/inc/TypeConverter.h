#ifndef TYPECONVERTER_H
#define TYPECONVERTER_H

#include "../io/VGADisplay.h"

class IntConverter
{
    private:
        char buffer[21];
        void clearBuff();

    public:
        char *intToChar(int n);
        char *uintToChar(unsigned int n);
};

#endif
