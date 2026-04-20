#include "math.h"
#include "my.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

char **const_adress(void) {
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
    r = sqrt(primes[i]);
    frac = r - floor(r);
    scale = frac * 4294967296.0;
    constant = (uint32_t)scale;
    snprintf(buf[i], 9, "%08X", constant);
  }
  buf[8] = NULL;
  return buf;
}
