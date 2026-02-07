#include "my.h"

uint32_t ch32(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t byte = 0;
    uint32_t result = 0;

    for (int i = 0; i < 32; i++) {
        byte = (x >> i) & 1;

        if (byte == 1) {
            byte = (y >> i) & 1;
            result = add32(result, byte << i);
        } else {
            byte = (z >> i) & 1;
            result = add32(result, byte << i);
        }
    }
    return result;
}
