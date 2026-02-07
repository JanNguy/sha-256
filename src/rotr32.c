#include "my.h"

uint32_t rotr32(uint32_t x, int r)
{
    uint32_t temp = 0;

    for (int i = 0; i != r; i++) {
        temp = x & 1;
        x >>= 1;
        x |= (temp << 31);
    }
    return x;
}
