#include "../include/parser.h"
#include "../include/lexer.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abst_print_data(struct abs_tree *tree) {
  if (!tree)
    return;
  switch (tree->token) {
  case num:
  case neg_num:
    printf("%ld", tree->data.int_data);
    break;
  case flo_num:
    printf("%lf", tree->data.double_data);
    break;
  case string:
    printf("%s", (char *)tree->data.str_data);
    break;
  case op_plus:
    printf("+");
    break;
  case op_minu:
    printf("-");
    break;
  case op_divi:
    printf("/");
    break;
  case op_mult:
    printf("*");
    break;
  default:
    break;
  }
}

void abst_print_tree(struct abs_tree *tree) {
  if (!tree) {
    printf("(null tree)\n");
    return;
  }

  printf("Tree:%p token:%s Data: ", (void *)tree, print_token(tree->token));
  abst_print_data(tree);
  printf("\n");

  if (tree->node)
    abst_print_tree(tree->node);
}

void abst_init(struct abs_tree **tree) {
  struct abs_tree *tmp = (struct abs_tree *)malloc(sizeof(struct abs_tree));
  if (!tmp)
    exit(EXIT_FAILURE);
  tmp->token = empty;
  tmp->node = NULL;
  tmp->line = 0;
  *tree = tmp;
}

void abst_add(struct abs_tree **tree, enum tree_token token, void *data) {
  if (!tree)
    return;

  struct abs_tree **tracer = tree;
  struct abs_tree *new = NULL;
  abst_init(&new);

  new->token = token;

  switch (token) {
  case num:
  case neg_num:
    new->data.int_data = *(int64_t *)data;
    break;
  case flo_num:
    new->data.double_data = *(double *)data;
    break;
  case string:
    new->data.str_data = data ? strdup((char *)data) : NULL;
    break;
  case op_plus:
  case op_minu:
  case op_divi:
  case op_mult:
    break;
  default:
    if (data) {
      new->data.str_data = strdup("ERROR: IN Data Token");
    }
    break;
  }

  while ((*tracer)) {
    tracer = &(*tracer)->node;
  }

  *tracer = new;
}

void abst_remove_node(struct abs_tree *tree) {
  if (!tree)
    return;

  if (tree->token == string && tree->data.str_data)
    free(tree->data.str_data);

  free(tree);
}

void abst_destroy(struct abs_tree *tree) {
  if (tree) {
    struct abs_tree *next = tree->node;
    abst_remove_node(tree);
    abst_destroy(next);
  }
}

void parse_number(char **input, struct abs_tree **current) {
  if (!input || !*input || !current || !*current)
    return;

  int negative = 0;
  if (**input == '-') {
    negative = 1;
    (*input)++;
  }

  int64_t value = 0;
  while (isdigit(**input)) {
    value = value * 10 + (**input - '0');
    (*input)++;
  }

  if (negative) {
    value = -value;
    (*current)->token = neg_num;
  } else {
    (*current)->token = num;
  }

  (*current)->data.int_data = value;
}

struct abs_tree *parse_list(char **input) {
  if (!input || !*input)
    return NULL;

  struct abs_tree *list_node = NULL;
  abst_init(&list_node);
  list_node->token = list_start;

  (*input)++;

  while (**input && isspace(**input)) {
    (*input)++;
  }

  if (**input == ')') {
    (*input)++;
    struct abs_tree *end_node = NULL;
    abst_init(&end_node);
    end_node->token = list_end;
    list_node->node = end_node;
    return list_node;
  }

  struct abs_tree *op_node = NULL;
  abst_init(&op_node);

  if (**input == '+') {
    op_node->token = op_plus;
    (*input)++;
  } else if (**input == '-') {
    op_node->token = op_minu;
    (*input)++;
  } else if (**input == '*') {
    op_node->token = op_mult;
    (*input)++;
  } else if (**input == '/') {
    op_node->token = op_divi;
    (*input)++;
  } else {
    printf("ERROR: Expected operator at the beginning of list\n");
    abst_destroy(list_node);
    abst_destroy(op_node);
    return NULL;
  }

  list_node->node = op_node;
  struct abs_tree **current = &(op_node->node);

  while (**input && **input != ')') {
    while (**input && isspace(**input)) {
      (*input)++;
    }

    if (**input == ')')
      break;

    if (**input == '(') {
      struct abs_tree *nested = parse_list(input);
      if (nested) {
        *current = nested;
        while (*current) {
          current = &((*current)->node);
        }
      }
      continue;
    }

    struct abs_tree *arg_node = NULL;
    abst_init(&arg_node);

    if (**input == '-' || isdigit(**input)) {
      parse_number(input, &arg_node);
    } else {
      printf("ERROR: Unrecognized token: %c\n", **input);
      abst_destroy(arg_node);
      (*input)++;
      continue;
    }

    *current = arg_node;
    current = &(arg_node->node);
  }

  if (**input == ')') {
    (*input)++;
  }

  struct abs_tree *end_node = NULL;
  abst_init(&end_node);
  end_node->token = list_end;
  *current = end_node;

  return list_node;
}

struct abs_tree *parser(char *input) {
  if (!input)
    return NULL;

  struct abs_tree *root = NULL;
  abst_init(&root);
  root->token = program_start;

  struct abs_tree **current = &(root->node);

  while (*input && isspace(*input)) {
    input++;
  }

  while (*input) {
    if (*input == '(') {
      struct abs_tree *list = parse_list(&input);
      if (list) {
        *current = list;
        while (*current) {
          current = &((*current)->node);
        }
      }
    } else if (isdigit(*input) || (*input == '-' && isdigit(*(input + 1)))) {
      struct abs_tree *num_node = NULL;
      abst_init(&num_node);
      parse_number(&input, &num_node);
      *current = num_node;
      current = &(num_node->node);
    } else {
      input++;
    }
    while (*input && isspace(*input)) {
      input++;
    }
  }

  struct abs_tree *end_node = NULL;
  abst_init(&end_node);
  end_node->token = program_end;
  *current = end_node;

  return root;
}