#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "my.h"

uint32_t *init_k(void)
{
    uint32_t *buf = malloc(sizeof(uint32_t) * 64);

    double scale = 0.0;
    int primes[64] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
        127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
        191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
        257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317
    };
    double r = 0.0;
    double frac = 0.0;
    uint32_t constant = 0;

    if (buf == NULL) {
        return NULL;
    }
    for (int i = 0; i < 64; i++) {
        r = cbrt(primes[i]);
        frac = r - floor(r);
        scale = frac * 4294967296.0;
        constant = (uint32_t)scale;
        buf[i] = constant;
    }
    return buf;
}