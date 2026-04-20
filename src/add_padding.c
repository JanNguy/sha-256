#include <stdint.h>
#include <stddef.h>
#include "struct.h"

static size_t add_len(sha_t *s, size_t i)
{
    uint64_t bit_len = (uint64_t)s->len * 8;

    for (int j = 7; j >= 0; j--)
        s->msg_pad[i++] = (bit_len >> (j * 8)) & 0xFF;
    return i;
}

void add_padding(sha_t *s)
{
    size_t i;

    for (i = 0; i < s->len; i++)
        s->msg_pad[i] = s->msg[i];

    s->msg_pad[i++] = 0x80;

    while ((i % 64) != 56)
        s->msg_pad[i++] = 0x00;

    i = add_len(s, i);
    s->len_pad = i;
}
