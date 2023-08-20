#include "TypeConverter.h"

void IntConverter::clearBuff()
{
    for(int i = 0; i < 21; i++) buffer[i] = '\0';
};

char *IntConverter::intToChar(int n)
{
    clearBuff();

    int number = n >> 31;   // n < 0 - n = -1, else n = 0
    number = (n ^ number) - number; // Clear sign bit

    bool isNegative = n < 0;
    unsigned int indx = 19;

    do {
        buffer[indx--] = 48 + (number % 10);
        number /= 10;
    }while(number != 0);
    
    if(isNegative) buffer[indx--] = '-';

    return &buffer[++indx];
};

char *IntConverter::uintToChar(unsigned int n)
{
    clearBuff();

    unsigned int number = n;
    unsigned int indx = 19;

    do {
        buffer[indx--] = 48 + (number % 10);
        number /= 10;
    }while(number != 0);
    
    return &buffer[++indx];
};
