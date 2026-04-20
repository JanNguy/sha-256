#include "my.h"
#include "struct.h"
#include "string.h"

static void define_sha(sha_t *b, char *s)
{
    b->s = strdup(s);
    b->states = NULL;
    b->buf = NULL;
}

void sha_256(char *s)
{
    sha_t *buf = NULL;

    define_sha(buf, s);
    add_padding(buf);
}