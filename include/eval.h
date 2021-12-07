#ifndef EVAL_H
#define EVAL_H
#include "../include/parser.h"
#include <sys/types.h>

enum res_type { int_type = 0, double_type, str_type };

struct eval_result {
  enum res_type type;
  union {
    int64_t int_res;
    char *str_res;
    double double_res;
  } data;
};

struct eval_result *eval(struct abs_tree *parsed_abst);
void eval_add_op(struct abs_tree ***t, struct eval_result *e_res);
void eval_minu_op(struct abs_tree ***t, struct eval_result *e_res);
void eval_list(struct abs_tree ***t, struct eval_result *e_res);
#endif
