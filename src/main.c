#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/input.h"
#include "../include/eval.h"
#include "../include/print.h"

int main(int argv, char **argc){
  struct abs_tree *input_abs;
  char *input = malloc(INPUT_BUFF_SIZE);

  while(true){
    printf("HlispC>");
    read_curr_line(input);

    if (strcmp(input, "exit\n") == 0)
      exit(EXIT_SUCCESS);

    input_abs = parser(input);
    /* abst_print_tree(input_abs); */

    print_res(eval(input_abs));

  }

  return EXIT_SUCCESS;
}
