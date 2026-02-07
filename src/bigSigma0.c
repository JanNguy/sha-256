#include "my.h"

uint32_t bigSigma0(uint32_t x)
{
    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t c = 0;

    a = rotr32(x, 2);
    b = rotr32(x, 13);
    c = rotr32(x, 22);
    return xor32(xor32(a, b), c);
}
