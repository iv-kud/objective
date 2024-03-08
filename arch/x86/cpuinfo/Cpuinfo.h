#ifndef CPUID_H
#define CPUID_H
#include <types.h>
#include <MemoryOperations.h>


#ifdef __cplusplus
extern "C" {
#endif
extern bool CPUIDCHK();
#ifdef __cplusplus
};
#endif

struct cpuidOutputRegisters
{
    uint32 eax;
    uint32 ebx;
    uint32 ecx;
    uint32 edx;
};

/*  Some updates: 
//  1. Add ability to initialize all variables 
//     who depend on initial eax value in construction
*/

class Cpuinfo
{
    public:
        // Initial value passed to eax register
        enum cpuidFunctionIndex
        {
            BasicInfo = 0,
            VersionInfo = 0x1,
            InternalInfo = 0x2,
            SerialNumberInfo = 0x3,
            DeterministicCacheInfo = 0x4,
            MonitorMwaitInfo = 0x5,
            ThermalPowerInfo = 0x6,
            FeatureInfo = 0x7,
            DirectCacheAccessInfo = 0x9,
            PerformanceMonitoring = 0xA,
            ExtendedTopologyInfo = 0xB,
            ExtendedStateInfo = 0xD,
            RDTMonitoring = 0xF,
            AllocationInfo = 0x10,
            SGXInfo = 0x12,
            TraceInfo = 0x14,
            ClockInfo = 0x15,
            FrequencyInfo = 0x16,
            SOCInfo = 0x17,
            UnimplementedStart = 0x40000000,
            UnimplementedEnd = 0x4FFFFFFF,
            ExtendedCpuidStart = 0x80000000,
            ExtendedBasicInfo = 0x80000000,
            MoreFeatureInfo = 0x80000001,
            BrandStringLow = 0x80000002,
            BrandStringMiddle = 0x80000003,
            BrandStringHight = 0x80000004,
            NotInfo = 0x80000005,
            CacheInfo = 0x80000006,
            MiscFeatureInfo = 0x80000007,
            AddressSize = 0x80000008,
            ExtendedCpuidEnd = 0x80000008,
        };

        enum processorType
        {
            OriginalOEM = 0,
            IntelOneDrive = 1,
            Dual = 2,
            Reserved = 3,
            NotRead = 0xf
        };

        enum featureInformationEcx
        {
            SSE3 = 1,
            PCLMULDQDQ = 1 << 1,
            DTES64 = 1 << 2,
            MONITOR = 1 << 3,
            DS_CPL = 1 << 4,
            VMX = 1 << 5,
            SMX = 1 << 6,
            EIST = 1 << 7,
            TM2 = 1 << 8,
            SSSE3 = 1 << 9,
            CNXT_ID = 1 << 10,
            SDBG = 1 << 11,
            FMA = 1 << 12,
            CMPXCHG16B = 1 << 13,
            xTPRUpdateControl = 1 << 14,
            PDCM = 1 << 15,
            PCID = 1 << 17,
            DCA = 1 << 18,
            SSE4_1 = 1 << 19,
            SSE4_2 = 1 << 20,
            x2APIC = 1 << 21,
            MOVBE = 1 << 22,
            POPCNT = 1 << 23,
            TSC_Deadline = 1 << 24,
            AESNI = 1 << 25,
            XSAVE = 1 << 26,
            OSXSAVE = 1 << 27,
            AVX = 1 << 28,
            F16C = 1 << 29,
            RDRAND = 1 << 30
        };

        enum featureInformationEdx
        {
            FPU = 1,
            VME = 1 << 1,
            DE = 1 << 2,
            PSE = 1 << 3,
            TSC = 1 << 4,
            MSR = 1 << 5,
            PAE = 1 << 6,
            MCE = 1 << 7,
            CX8 = 1 << 8,
            APIC = 1 << 9,
            SEP = 1 << 11,
            MTRR = 1 << 12,
            PGE = 1 << 13,
            MCA = 1 << 14,
            CMOV = 1 << 15,
            PAT = 1 << 16,
            PSE_36 = 1 << 17,
            PSN = 1 << 18,
            CLFSH = 1 << 19,
            DS = 1 << 21,
            ACPI = 1 << 22,
            MMX = 1 << 23,
            FXSR = 1 << 24,
            SSE = 1 << 25,
            SSE2 = 1 << 26,
            SS = 1 << 27,
            HTT = 1 << 28,
            TM = 1 << 29,
            PBE = 1 << 31
        };

        enum generalDescriptors
        {
            NullDescriptor = 0,
            NotreportInformation = 0xFF
        };

        enum TlbDescriptors
        {
            // TLB + type _ page size _ associative _ amount entries _ array (not necessary)
            TLBI_4Kb_4WSA_32E = 0x1,
            TLBI_4Mb_fullyA_32E = 0x2,
            TLBD_4Kb_4WSA_64E = 0x3,
            TLBD_4Mb_4WSA_8E = 0x4,
            TLBD_4Mb_4WSA_32E = 0x5,
            TLBI_4Mb_4WSA_4E = 0xB,
            TLBI_4Kb_32E = 0x4F,
            TLBI_4Kb2Mb_64E = 0x50,
            TLBI_4Mb_64E = 0x50,
            TLBI_4Kb2Mb_128E = 0x51,
            TLBI_4Mb_128E = 0x51,
            TLBI_4Kb2Mb_256E = 0x52,
            TLBI_4Mb_256E = 0x52,
            TLBI_2Mb_fully_7E = 0x55,
            TLBI_4Mb_fully_7E = 0x55,
            TLB0D_4Mb_4WSA_16E = 0x56,
            TLB0D_4Kb_4WA_16E = 0x57,
            TLB0D_4Kb_fully_16E = 0x59,
            TLB0D_2Mb_4WSA_32E = 0x5A,
            TLB0D_4Mb_4WSA_32E = 0x5A,
            TLBD_4Kb4Mb_64E = 0x5B,
            TLBD_4Kb4Mb_128E = 0x5C,
            TLBD_4Kb4Mb_256E = 0x5D,
            TLBI_4Kb_fully_48E = 0x61,
            TLBD_2Mb_4WSA_32E_1GbArray4E = 0x63,
            TLBD_4Mb_4WSA_32E_1GbArray4E = 0x63,
            TLBD_4Kb_4WSA_512E = 0x64,
            TLBI_2Mb_fully_8E = 0x76,
            TLBI_4Mb_fully_8E = 0x76,
            DTLB_4Kb_fully_32E = 0xA0,
            TLBI_4Kb_4WSA_128E = 0xB0,
            TLBI_2Mb_4WA_8E = 0xB1,
            TLBI_4Mb_4WA_4E = 0xB1,
            TLBI_4Kb_4WSA_64E = 0xB2,
            TLBD_4Kb_4WSA_128E = 0xB3,
            TLB1D_4Kb_4WSA_256E = 0xB4,
            TLBI_4Kb_8WSA_64E = 0xB5,
            TLBI_4Kb_8WSA_128E = 0xB6,
            TLBD_4Kb_4WA_64E = 0xBA,
            TLBD_4Kb4Mb_4WA_8E = 0xC0,
            STLB_4Kb_8WA_1024 = 0xC1,
            STLB_2Mb_8WA_1024 = 0xC1,
            DTLB_4Kb_4WA_16E = 0xC2,
            DTLB_2Mb_4WA_16E = 0xC2,
            STLB_4Kb_6WA_1536E = 0xC3,
            STLB_2Mb_6WA_1536E = 0xC3,
            STLB_1Gb_4WA_16E = 0xC3,
            DTLB_2Mb_4WA_32E = 0xC4,
            DTLB_4Mb_4WA_32E = 0xC4,
            STLB_4Kb_4WA_512E = 0xCA
        };

        enum CacheDescriptors
        {
            // CACHE _ lvl + type (if 1 lvl) _ size _ associative ways _ line size in bytes
            CACHE_1lvlI_8Kb_4w_32b = 0x06,
            CACHE_1lvlI_16Kb_4w_32b = 0x08,
            CACHE_1lvlI_32Kb_4w_64b = 0x09,
            CACHE_1lvlD_8Kb_2w_32b = 0x0A,
            CACHE_1lvlD_16Kb_4w_32b = 0x0C,
            CACHE_1lvlD_16Kb_4w_64b = 0x0D,
            CACHE_1lvlD_24Kb_6w_64b = 0x0E,
            CACHE_2lvl_128Kb_2w_64b = 0x1D,
            CACHE_2lvl_256Kb_8w_64b = 0x21,
            CACHE_3lvl_512_4w_64b_2lines = 0x22,
            CACHE_3lvl_1Mb_8w_64b_2lines = 0x23,
            CACHE_2lvl_1Mb_16w_64b = 0x24,
            CACHE_3lvl_2Mb_8w_64b_2lines = 0x25,
            CACHE_3lvl_4Mb_8w_64b_2lines = 0x29,
            CACHE_1lvlD_32Kb_8w_64b = 0x2C,
            CACHE_1lvlI_32Kb_8w_64b = 0x30,
            CACHE_No2lvl_or_No3lvl = 0x40,
            CACHE_2lvl_128Kb_4w_32b = 0x41,
            CACHE_2lvl_256Kb_4w_32b = 0x42,
            CACHE_2lvl_512Kb_4w_32b = 0x43,
            CACHE_2lvl_1Mb_4w_32b = 0x44,
            CACHE_2lvl_2Mb_4w_32b = 0x45,
            CACHE_3lvl_4Mb_4w_64b = 0x46,
            CACHE_3lvl_8Mb_8w_64b = 0x47,
            CACHE_2lvl_3Mb_12w_64b = 0x48,
            CACHE_3lvl_4Mb_16w_64b = 0x49,
            CACHE_2lvl_4Mb_16w_64b = 0x49,
            CACHE_3lvl_6Mb_12w_64b = 0x4A,
            CACHE_3lvl_8Mb_16w_64b = 0x4B,
            CACHE_3lvl_12Mb_12w_64b = 0x4C,
            CACHE_3lvl_16Mb_16w_64b = 0x4D,
            CACHE_2lvl_6Mb_24w_64b = 0x4E,
            CACHE_1lvlD_16Kb_8w_64b = 0x60,
            CACHE_1lvlD_8Kb_4w_64b = 0x66,
            CACHE_1lvlD_16Kb_4w_64b_Repeat = 0x67,
            CACHE_1lvlD_32Kb_4w_64b = 0x68,
            CACHE_uTLB_4Kb_8w_64E = 0x6A,
            CACHE_DTLB_4Kb_8w_256E = 0x6B,
            CACHE_DTLB_2Mb_8w_128E = 0x6C,
            CACHE_DTLB_4Mb_8w_128E = 0x6C,
            CACHE_DTLB_1Gb_fully_16E = 0x6D,
            CACHE_Trace_12K_8w = 0x70,
            CACHE_Trace_16K_8w = 0x71,
            CACHE_Trace_32K_8w = 0x72,
            CACHE_2lvl_1Mb_4w_64b = 0x78,
            CACHE_2lvl_128Kb_8w_64b_2lines = 0x79,
            CACHE_2lvl_256Kb_8w_64b_2lines = 0x7A,
            CACHE_2lvl_512Kb_8w_64b_2lines = 0x7B,
            CACHE_2lvl_1Mb_8w_64b_2lines = 0x7C,
            CACHE_2lvl_2Mb_8w_64b = 0x7D,
            CACHE_2lvl_512Kb_2w_64b = 0x7F,
            CACHE_2lvl_512Kb_8w_64b = 0x80,
            CACHE_2lvl_256Kb_8w_32b = 0x82,
            CACHE_2lvl_512Kb_8w_32b = 0x83,
            CACHE_2lvl_1Mb_8w_32b = 0x84,
            CACHE_2lvl_2Mb_8w_32b = 0x85,
            CACHE_2lvl_512Kb_4w_64b = 0x86,
            CACHE_2lvl_1Mb_8w_64b = 0x87,
            CACHE_3lvl_512Kb_4w_64b = 0xD0,
            CACHE_3lvl_1Mb_4w_64b = 0xD1,
            CACHE_3lvl_2Mb_4w_64b = 0xD2,
            CACHE_3lvl_1Mb_8w_64b = 0xD6,
            CACHE_3lvl_2Mb_8w_64b = 0xD7,
            CACHE_3lvl_4Mb_8w_64b = 0xD8,
            CACHE_3lvl_1536Kb_12w_64b = 0xDC,
            CACHE_3lvl_3Mb_12w_64b = 0xDD,
            CACHE_3lvl_6Mb_12w_64b_Repeat = 0xDE,
            CACHE_3lvl_2Mb_16w_64b = 0xE2,
            CACHE_3lvl_4Mb_16w_64b_Repeat = 0xE3,
            CACHE_3lvl_8Mb_16w_64b_Repeat = 0xE4,
            CACHE_3lvl_12Mb_24w_64b = 0xEA,
            CACHE_3lvl_18Mb_24w_64b = 0xEB,
            CACHE_3lvl_24Mb_24w_64b = 0xEC
        };

        enum PrefetchDescriptors
        {
            PREFETCH_64 = 0xF0,
            PREFETCH_128 = 0xF1
        };

        enum brandStringPart
        {
            brandString_low = 0,
            brandString_middle = 16,
            brandString_hight = 32
        };

    public:
        const static uint8 amountBytesRegisters = 16;
        const static uint8 amountDescriptors = 16;
        // 12 ASCII-symbols + null symbol
        const constexpr static uint8 vendorStringSize = 12 + 1;
        const constexpr static uint8 brandStringSize = (3 * 4 * 4) + 1;
        // Optional
        const static uint8 amountRegisters = 4;
        const static uint8 amountBytesInRegister = 4;

    private:
        
        bool cpuidAvailable;
        // Saved data of cpuid for eax = 0
        char vendorString[vendorStringSize];
        uint8 maximumInputValue;
        // The result of using the method cpuid last time 
        uint32 eax, ebx, ecx, edx;
        // Saved data of cpuid for eax = 1
        uint8 displayFamily, displayModel, stepping, brandIndex;
        // clflushLineSize - cache line size in bytes, max number variables for logical processors
        uint8 maxNumberProcessorsIds, maxNumberApicsIds, initialApicId;
        uint16 clflushLineSize; 
        processorType currentCpuType;
        // Saved data of cpuid eax = 2
        uint8 internalInfoDescriptors[amountBytesRegisters];
        // Saved data of cpuid eax = 3
        uint64 serialNumber;
        // Saved data for processor brand string function
        uint8 brandString[brandStringSize];
        // Saved daata for extended basic data function
        bool isBrandStringSupported;
        uint32 maximumInputValueExtended;

        // If eax value correct - true, else false
        bool isEaxValueCorrect(const cpuidFunctionIndex eaxValue);
        // Decode and set local properties after cpuid command
        // False result if cpuid result successfully decode, otherwise true
        bool decodeCpuidResult(const cpuidFunctionIndex eaxValue);
        // Cpuid command with decode result
        bool decodeCpuidCommand(const cpuidFunctionIndex eaxValue);
        // Below methods read data from registers and set some properties
        void setBasicData();
        void setVersionData();
        void setSerialData();
        void setInternalData();
        void setExtendedBasicData();
        void setBrandString(brandStringPart part);

        void dataFilling(cpuidFunctionIndex startValue, 
                         cpuidFunctionIndex endValue);

    public:
        Cpuinfo();
        // false - if value in eax correct, else true
        bool cpuid(const cpuidFunctionIndex eaxValue);
        bool cpuid(const cpuidFunctionIndex eaxValue, uint32 ecxValue);
        bool isCommandSupportSubLeaf(const cpuidFunctionIndex eaxValue);
        cpuidOutputRegisters getRegs();
        const char* getVendorString();
        processorType getProcessorType();
        uint8 getDisplayFamily();
        uint8 getDisplayModel();
        uint8 getStepping();
        uint8 getMaxFunctionIndex();
        uint32 getMaxFunctionIndexExtended();
        const char* getBrandString();
        uint8* getInternalDescriptors();
};
#endif
