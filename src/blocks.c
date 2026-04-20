#include "my.h"
#include "struct.h"
#include "stdlib.h"

void process_blocks(sha_t *s)
{
    size_t offset;

    offset = 0;
    while (offset < *s->len_pad) {
        build_message_schedule(s->msg_pad + offset);
        compression(s);
        offset += 64;
    }
}