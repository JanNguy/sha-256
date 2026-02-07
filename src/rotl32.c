#include "my.h"

uint32_t rotl32(uint32_t x, int r)
{
    uint32_t temp = 0;

    for (int i = 0; i != r; i++) {
        temp = (x >> 31) & 1;
        x <<= 1;
        x |= temp;
    }
    return x;
}
