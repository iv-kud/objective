#include <types.h>
#include <StringOperations.h>


typedef decltype(nullptr) nulltype;

struct descHeader
{
    char signature[4];
    uint32 length;
    uint8 revision;
    uint8 checksum;
    char oemId[6];
    uint64 oemTableId;
    uint32 oemRevision;
    uint32 creatorId;
    uint32 creatorRevision;
} __attribute__((packed));

struct rsdt
{
    descHeader header;
    uint32 firstEntryAddr;
} __attribute__((packed, aligned(sizeof(uint32))));

struct xsdt
{
    descHeader header;
    uint64 firstEntryAddr;
} __attribute__((packed, aligned(sizeof(uint32))));

struct rsdp
{
    char signature[8];
    uint8 checksum;
    char oemId[6];
    uint8 revision;
    uint32 rsdtAddress;
    uint32 length;
    uint32 xsdtAddress;
    uint8 extendedChecksum;
    char reserved[3];
} __attribute__((packed));

class DescriptorTable
{

};

class Entry
{
    private:
        uint32 sizeHeadersInBytes;
        const struct descHeader **headers;
        // DescriptorTable &tables;
    public:
        Entry() = delete;
        Entry(const uint32 sizeEntriesBytes, const uint32 *entryAddress);
        Entry(const nulltype null);
};

class Rsdt
{
    private:
        const struct rsdt* rsdtStruct;
        Entry entry;
    public:
        Rsdt() = delete;
        Rsdt(const uint32 addr);
        Rsdt(const nulltype null);
        const Entry& getEntries();
};

class Xsdt
{
    private:
        const struct xsdt* xsdtStruct;
    public:
        Xsdt() = delete;
        Xsdt(const uint32 addr);
        Xsdt(const nulltype null);
};

class Rsdp
{
    private:
        const uint8 validFieldRevision = 2;
        // RSDP memory address areas in IA-PC systems
        const char *rsdpSign = "RSD PTR ";
        const MemArea rsdpRomMemArea = MemArea(0xe0000, 0xfffff);
        const MemArea rsdpEbdaMemArea = MemArea(0x80000, 0x803ff);

        const struct rsdp *rsdpStruct;
        Rsdt rsdtObj;
        Xsdt xsdtObj;
    public:
        Rsdp();
        const Rsdt *getRsdt() const;
        const Xsdt *getXsdt() const;

};
