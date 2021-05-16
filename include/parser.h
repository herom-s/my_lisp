#ifndef PARSER_H
#define PARSER_H
#include <sys/types.h>
#include <stdlib.h>
#include "../include/lexer.h"

struct abs_tree{
  u_int64_t line;
  enum tree_token token;
  union{
    char *str_data;
    int64_t *int_data;
    double *double_data;
  }data;
  struct abs_tree *node;
};

void abst_init(struct abs_tree **tree);
void abst_destroy(struct abs_tree *tree);
void abst_add(struct abs_tree **tree, enum tree_token token, void *data);
void abst_remove_node(struct abs_tree *tree);

void abst_print_data(struct abs_tree *tree);
void abst_print_tree(struct abs_tree *tree);

struct abs_tree *parser(char *input);

#endif
