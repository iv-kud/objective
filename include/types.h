#define NULL 0


typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

#if defined(__x86_64)
    typedef uint64 memAddr;
#else
    typedef uint32 memAddr;
#endif
