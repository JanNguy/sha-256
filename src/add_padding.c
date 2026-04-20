#include <stdint.h>
#include <stddef.h>
#include "my.h"

static size_t add_len(sha_t *s, size_t i)
{
    uint64_t bit_len = (uint64_t)(*s->len) * 8;

    for (int j = 7; j >= 0; j--)
        s->msg_pad[i++] = (bit_len >> (j * 8)) & 0xFF;
    return i;
}

void add_padding(sha_t *s)
{
    size_t msg_len = *s->len;
    size_t full_blocks = (msg_len + 8) / 64 + 1;
    size_t pad_len = full_blocks * 64;

    s->msg_pad = malloc(pad_len);
    if (!s->msg_pad)
        return;

    for (size_t i = 0; i < msg_len; i++)
        s->msg_pad[i] = s->msg[i];

    size_t i = msg_len;
    s->msg_pad[i++] = 0x80;

    while ((i % 64) != 56)
        s->msg_pad[i++] = 0x00;

    i = add_len(s, i);
    *s->len_pad = i;
}
