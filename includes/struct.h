#ifndef STRUCT_H
    #define STRUCT_H
    #include "stdlib.h"
    #include "stdint.h"

typedef struct sha_s {
    char *s;
    uint32_t *states;
    uint8_t *msg;
    uint8_t *msg_pad;

    //infos
    size_t *len;
    size_t *len_pad;

} sha_t;

#endif /*STRUCT_H*/