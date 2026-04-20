#include "my.h"
#include <stdio.h>

char *digest_to_hex(uint32_t *digest)
{
    static char hex[65];
    int j = 0;

    for (int i = 0; i < 8; i++) {
        snprintf(hex + j, 9, "%08x", digest[i]);
        j += 8;
    }
    hex[64] = '\0';
    return hex;
}
