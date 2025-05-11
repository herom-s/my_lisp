#include "../include/eval.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/print.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  struct abs_tree *input_abs;
  char *input = NULL;
  struct eval_result *result = NULL;

  while (true) {
    prompt("MYLisp> ", &input);

    if (input && strcmp(input, "exit") == 0) {
      free(input);
      exit(EXIT_SUCCESS);
    }

    if (!input || strlen(input) == 0) {
      if (input)
        free(input);
      continue;
    }

    printf("DEBUG: Raw input: '%s'\n", input);

    input_abs = parser(input);

    if (!input_abs) {
      printf("Parse error: Failed to create abstract syntax tree\n");
      free(input);
      input = NULL;
      continue;
    }

    printf("DEBUG: Parsed tree structure:\n");
    abst_print_tree(input_abs);

    result = eval(input_abs);

    if (result) {
      printf("Result: ");
      print_res(result);
      free(result);
      result = NULL;
    } else {
      printf("Evaluation error: Failed to evaluate expression\n");
    }

    abst_destroy(input_abs);
    input_abs = NULL;

    free(input);
    input = NULL;
  }

  return EXIT_SUCCESS;
}
