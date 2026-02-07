
#include "my.h"
#include <stdlib.h>

static void define_letter(uint32_t *l, uint32_t *state)
{
    for (int i = 0; i < 8; i++) {
        l[i] = state[i];
    }
}

void compress(uint32_t *state, uint32_t *w, uint32_t *k)
{
    uint32_t *l = malloc(sizeof(uint32_t) * 8);
    uint32_t t1 = 0;
    uint32_t t2 = 0;

    define_letter(l, state);
    for (int i = 0; i < 64; i++) {
        t1 = l[7];
        t1 = add32(t1, bigSigma1(l[4]));
        t1 = add32(t1, ch32(l[4], l[5], l[6]));
        t1 = add32(t1, k[i]);
        t1 = add32(t1, w[i]);
        t2 = bigSigma0(l[0]);
        t2 = add32(t2, maj32(l[0], l[1], l[2]));
        l[7] = l[6];
        l[6] = l[5];
        l[5] = l[4];
        l[4] = add32(l[3], t1);
        l[3] = l[2];
        l[2] = l[1];
        l[1] = l[0];
        l[0] = add32(t1, t2);
    }
    state[0] = add32(state[0], l[0]);
    state[1] = add32(state[1], l[1]);
    state[2] = add32(state[2], l[2]);
    state[3] = add32(state[3], l[3]);
    state[4] = add32(state[4], l[4]);
    state[5] = add32(state[5], l[5]);
    state[6] = add32(state[6], l[6]);
    state[7] = add32(state[7], l[7]);
    free(l);
}
