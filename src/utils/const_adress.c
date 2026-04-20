#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "my.h"

// retourne un tableau de 8 constantes + NULL
char **const_adress(void)
{
    char **buf = malloc(sizeof(char *) * 9);
    int nb_const = 8;
    int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
    double r = 0.0;
    double frac = 0;
    double scale = 0;
    uint32_t constant = 0;

    if (buf == NULL) {
        return NULL;
    }
    for (int i = 0; i < nb_const; i++) {
        buf[i] = malloc(9);
        if (buf[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(buf[j]);
            free(buf);
            return NULL;
        }
        r = sqrt(primes[i]); //récupération de la partie fractionnaire
        frac = r - floor(r);     // floor remove the int part
        scale = frac * 4294967296.0; // 2^32
        constant = (uint32_t)scale;
        snprintf(buf[i], 9, "%08X", constant); // hexa padded
    }
    buf[8] = NULL;
    return buf;
}
