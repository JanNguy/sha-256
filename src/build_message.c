#include "my.h"
#include "struct.h"

static void define_message(uint32_t *w, uint8_t *m)
{
    for (int i = 0; i < 16; i++) {
        w[i] = ((uint32_t)m[i * 4] << 24) |
               ((uint32_t)m[i * 4 + 1] << 16) |
               ((uint32_t)m[i * 4 + 2] << 8) |
               ((uint32_t)m[i * 4 + 3]);
    }
}

uint32_t *build_message_schedule(uint8_t *m)
{
    uint32_t *w = malloc(sizeof(uint32_t) * 64);
    uint32_t temp = 0;

    if (w == NULL)
        return NULL;
    define_message(w, m);
    for (int i = 16; i < 64; i++) {
        w[i] = smallSigma1(w[i - 2]);
        w[i] = add32(w[i], w[i - 7]);
        temp = smallSigma0(w[i - 15]);
        w[i] = add32(w[i], w[i - 16]);
        w[i] = add32(temp, w[i]);
    }
    return w;
}