#include "my.h"
#include "struct.h"
#include <stdlib.h>

static void define_letter(uint32_t *l, uint32_t *state)
{
    for (int i = 0; i < 8; i++) {
        l[i] = state[i];
    }
}

void compression(sha_t *s)
{
    uint32_t *l = malloc(sizeof(uint32_t) * 8);
    uint32_t t1 = 0;
    uint32_t t2 = 0;
    uint32_t *w = build_message_schedule(s->msg_pad);
    uint32_t *k = init_k();

    define_letter(l, s->states);
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
    s->states[0] = add32(s->states[0], l[0]);
    s->states[1] = add32(s->states[1], l[1]);
    s->states[2] = add32(s->states[2], l[2]);
    s->states[3] = add32(s->states[3], l[3]);
    s->states[4] = add32(s->states[4], l[4]);
    s->states[5] = add32(s->states[5], l[5]);
    s->states[6] = add32(s->states[6], l[6]);
    s->states[7] = add32(s->states[7], l[7]);
    free(l);
    free(w);
    free(k);
}
