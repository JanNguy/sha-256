#include "my.h"

uint32_t bigSigma1(uint32_t x)
{
    uint32_t a = 0;
    uint32_t b = 0;
    uint32_t c = 0;

    a = rotr32(x, 6);
    b = rotr32(x, 11);
    c = rotr32(x, 25);
    return xor32(xor32(a, b), c);
}