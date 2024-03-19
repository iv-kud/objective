#include "acpi.h"
#include "StringOperations.h"


Rsdp::Rsdp() : rsdpStruct(nullptr), rsdtObj(nullptr), xsdtObj(nullptr)
{
    rsdpStruct = (struct rsdp *)StringOperations::findInMemory(rsdpSign, rsdpRomMemArea);

    if(rsdpStruct == nullptr)
    {
        rsdpStruct = (struct rsdp *)StringOperations::findInMemory(rsdpSign, rsdpEbdaMemArea);
    }

    if(rsdpStruct != nullptr)
    {
        rsdtObj = Rsdt(rsdpStruct->rsdtAddress);
        if(rsdpStruct->revision >= validFieldRevision)
        {
            xsdtObj = Xsdt(rsdpStruct->xsdtAddress);
        }
    }
};

const Rsdt *Rsdp::getRsdt() const
{
    if(rsdpStruct != nullptr) return &rsdtObj;
    else return nullptr;
};

Rsdt::Rsdt(const nulltype null) : entry(null)
{
    rsdtStruct = null;
};

Rsdt::Rsdt(const uint32 addrRsdt) : entry(nullptr)
{
    rsdtStruct = (const struct rsdt *)(addrRsdt);
    if(rsdtStruct != nullptr)
    {
        entry = Entry(rsdtStruct->header.length,
                        (&rsdtStruct->firstEntryAddr));
    }
};

const Xsdt *Rsdp::getXsdt() const
{
    if(rsdpStruct != nullptr) return &xsdtObj;
    else return nullptr;
};

Xsdt::Xsdt(const nulltype null)
{
    xsdtStruct = nullptr;
};

Xsdt::Xsdt(const uint32 xsdt)
{
    xsdtStruct = (const struct xsdt *)(xsdt);
};

Entry::Entry(const uint32 rsdtLength, const uint32 *entryAddress)
{
    sizeHeadersInBytes = rsdtLength - sizeof(descHeader);
    headers = (const struct descHeader **)(entryAddress);
};

Entry::Entry(const nulltype null)
{
    sizeHeadersInBytes = 0;
    headers = null;
};
