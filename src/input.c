#include "../include/input.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#define open _open
#define close _close
#define read _read
#define write _write
#else
#include <unistd.h>
#endif

char *get_line() {
  char *res = malloc(INPUT_BUFF_SIZE);
  if (!res) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }
  memset(res, 0, INPUT_BUFF_SIZE);

  ssize_t bytes_read = read(STDIN_FILENO, res, INPUT_BUFF_SIZE - 1);
  if (bytes_read < 0) {
    free(res);
    return NULL;
  }
  res[INPUT_BUFF_SIZE - 1] = '\0';
  size_t len = strlen(res);
  if (len > 0 && res[len - 1] == '\n') {
    res[len - 1] = '\0';
  }
  return res;
}

void prompt(char *promp_string, char **input) {
  fprintf(stdout, "%s", promp_string);
  *input = get_line();
}
