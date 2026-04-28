#include "my.h"

uint32_t maj32(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = 0;
    int count = 0;

    for (int i = 0; i < 32; i++) {
        count = 0;
        if (((x >> i) & 1) == 1)
            count++;
        if (((y >> i) & 1) == 1)
            count++;
        if (((z >> i) & 1) == 1)
            count++;
        if (count >= 2) {
            result |= (1 << i);
        } else {
            result |= (0 << i);
        }
    }
    return result;
}