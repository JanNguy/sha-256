#include "my.h"
#include "struct.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

static void define_sha(sha_t *b, char *s)
{
    b->s = strdup(s);
    b->len = malloc(sizeof(size_t));
    *b->len = strlen(s);
    b->msg = (uint8_t *)s;
    b->msg_pad = NULL;
    b->states = init_h();
    b->hex = NULL;
    b->len_pad = malloc(sizeof(size_t));
}

void sha_256(char *s)
{
    sha_t *buf = sha_256_create(s);
    (void)buf;
}

sha_t *sha_256_create(char *s)
{
    sha_t *buf = malloc(sizeof(sha_t));

    if (!buf)
        return NULL;
    define_sha(buf, s);
    add_padding(buf);
    process_blocks(buf);
    buf->hex = digest_to_hex(buf->states);
    return buf;
}