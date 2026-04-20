#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "my.h"

uint32_t *init_h(void)
{
    uint32_t *buf = malloc(sizeof(uint32_t) * 8);
    int nb_const = 8;
    int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
    double r = 0.0;
    double frac = 0;
    double scale = 0;
    uint32_t constant = 0;

    if (buf == NULL) {
        return NULL;
    }
    for (int i = 0; i < 8; i++) {
        r = sqrt(primes[i]);
        frac = r - floor(r);
        scale = frac * 4294967296.0;
        constant = (uint32_t)scale;
        buf[i] = constant;
    }
    return buf;
}
