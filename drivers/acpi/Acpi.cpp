#include "Acpi.h"


const char *Rsdp::signatureString = "RSD PTR ";
const uint8 Rsdp::validFieldRevision = 2;
const memAddr Rsdp::romAreaStart = 0xe0000;
const memAddr Rsdp::romAreaEnd = 0xfffff;
const memAddr Rsdp::ebdaAreaStart = 0x80000;
const memAddr Rsdp::ebdaAreaEnd = 0x803ff;
const uint8 Rsdp::checksunFieldSize = 20;
const uint8 Entry::size = 4;
const uint8 sizeWithoutIcs = 44;

Rsdt *Rsdp::getRsdt() const
{
    Rsdt *rsdtPtr = (Rsdt *)(rsdtAddress);
    if(rsdtPtr == nullptr or checksumCheck()) return nullptr;
    else return rsdtPtr;
};

Xsdt *Rsdp::getXsdt() const
{
    Xsdt *xsdtPtr = (Xsdt *)(xsdtAddress);
    if(xsdtPtr == nullptr or checksumCheck()) return nullptr;
    else return xsdtPtr;
};


const uint32 DescHeader::getLength() const
{
    return length;
};

const Entry *Rsdt::getEntry(uint8 index) const
{
    uint32 entriesAmount = (header.getLength() - sizeof(DescHeader)) / Entry::size;

    if(index >= entriesAmount 
        or header.checksumCheck()) return nullptr;
    else return ((const Entry **)&entries)[index];
};

uint8 Rsdp::checksumCheck() const
{
    uint8 check = 0;
    for(uint32 offset = 0; offset < checksunFieldSize; offset++)
    {
        check += *(uint8 *)((memAddr)this + offset);
    }
    return check;
};

uint8 DescHeader::checksumCheck() const
{
    uint8 check = 0;
    for(uint32 offset = 0; offset < length; offset++)
    {
        check += *(uint8 *)((memAddr)this + offset);
    }
    return check;
};

const Ics *Madt::getIcs(uint8 index) const
{
    uint32 icsBytesRemain = header.getLength() - ::sizeWithoutIcs;
    uint16 indexAmass = 0;
    const Ics *icsPtr = (Ics *)(&icsBegin);

    while(icsBytesRemain > 0)
    {
        if(indexAmass == index) return icsPtr;
        else
        {
            icsBytesRemain -= icsPtr->getLength();
            indexAmass++;
            icsPtr = (Ics *)((memAddr)icsPtr + icsPtr->getLength());
        }
    }

    return nullptr;
};
