#include "my.h"

uint32_t or32(uint32_t a, uint32_t b)
{
    uint32_t result = 0;
    uint32_t t_a = 0;
    uint32_t t_b = 0;
    uint32_t byte = 0;

    for (int i = 0; i < 32; i++) {
        t_a = (a >> i) & 1;
        t_b = (b >> i) & 1;

        byte = (t_a == 1 || t_b == 1);
        result |= (byte << i);
    }
    return result;
}