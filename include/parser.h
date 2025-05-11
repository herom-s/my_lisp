#ifndef PARSER_H
#define PARSER_H
#include "../include/lexer.h"
#include <stddef.h>
#include <stdint.h>


struct abs_tree {
  size_t line;
  enum tree_token token;
  union {
    char *str_data;
    int64_t int_data;
    double double_data;
  } data;
  struct abs_tree *node;
};

void abst_init(struct abs_tree **tree);
void abst_destroy(struct abs_tree *tree);
void abst_add(struct abs_tree **tree, enum tree_token token, void *data);
void abst_remove_node(struct abs_tree *tree);

void abst_print_data(struct abs_tree *tree);
void abst_print_tree(struct abs_tree *tree);

struct abs_tree *parse_list(char **input);
struct abs_tree *parser(char *input);

#endif
