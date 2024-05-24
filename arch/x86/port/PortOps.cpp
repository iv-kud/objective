#include "PortOps.h"


void PortOps::outb(portadr port, regb value)
{
    asm("outb %b0, %w1"
        :
        : "a"(value), "Nd"(port)
        : "memory");
};

void PortOps::outw(portadr port, regw value)
{
    asm("out %w0, %w1"
        :
        : "a"(value), "Nd"(port)
        : "memory");
};

void PortOps::outl(portadr port, regl value)
{
    asm("out %k0, %w1"
        :
        : "a"(value), "Nd"(port)
        : "memory");
};

regb PortOps::inb(portadr port)
{
    regb res;

    asm("in %w1, %b0"
        : "=a"(res)
        : "Nd"(port)
        : "memory");

    return res;
};

regw PortOps::inw(portadr port)
{
    regw res;

    asm("in %w1, %w0"
        : "=a"(res)
        : "Nd"(port)
        : "memory");

    return res;
};

regl PortOps::inl(portadr port)
{
    regl res;

    asm("in %w1, %k0"
        : "=a"(res)
        : "Nd"(port)
        : "memory");

    return res;
};
