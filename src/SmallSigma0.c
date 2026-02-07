#include "my.h"

uint32_t smallSigma0(uint32_t x)
{
    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t c = 0;

    a = rotr32(x, 7);
    b = rotr32(x, 18);
    c = shr32(x, 3);
    return xor32(xor32(a, b), c);
}