#include <stdint.h>
#include <stdlib.h>

#define FNV_PRIME_64 ((1ULL<<40)+(1<<8)+0xb3)
#define FNV_OFFSET_BASIS_64 (14695981039346656037ULL)

uint64_t
FNV1a(size_t n, const unsigned char *bytes)
{
    uint64_t h = FNV_OFFSET_BASIS_64;

    for(size_t i = 0; i < n; i++) {
        h ^= bytes[i];
        h *= FNV_PRIME_64;
    }

    return h;
}
