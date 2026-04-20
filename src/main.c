#include "my.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  sha_t *result;

  while ((read = getline(&line, &len, stdin)) != -1) {
    if (read > 0 && line[read - 1] == '\n')
      line[read - 1] = '\0';
    result = sha_256_create(line);
    if (result) {
      printf("%s\n", result->hex);
      free(result);
    }
  }
  free(line);
  return 0;
}
