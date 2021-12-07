#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/eval.h"
#include "../include/parser.h"

void eval_add_op(struct abs_tree ***t, struct eval_result *e_res) {
  int64_t tmp_val = 0;
  e_res->type = int_type;
  while (((*(*t))->token) != list_end && ((*(*t))->token) != program_end) {
    if (((*(*t))->token) == list_start) {
      *t = &((*(*t))->node);
      eval_list(t, e_res);
      tmp_val += e_res->data.int_res;
    } else if (((*(*t))->token) == num || (*(*t))->token == neg_num) {
      printf("+1:%ld\n", tmp_val);
      tmp_val += (*(*t))->data.int_data;
      printf("+2:%ld\n", tmp_val);
    }
    *t = &((*(*t))->node);
  }
  printf("+3:%ld\n", tmp_val);
  e_res->data.int_res = tmp_val;
}

void eval_minu_op(struct abs_tree ***t, struct eval_result *e_res) {
  int64_t tmp_val = 0;
  e_res->type = int_type;
  while (((*(*t))->token) != list_end && ((*(*t))->token) != program_end) {
    if (((*(*t))->token) == list_start) {
      *t = &((*(*t))->node);
      eval_list(t, e_res);
      tmp_val -= e_res->data.int_res;
    } else if (((*(*t))->token) == num || (*(*t))->token == neg_num) {
      printf("-1:%ld\n", tmp_val);
      tmp_val -= (*(*t))->data.int_data;
      printf("-2:%ld\n", tmp_val);
    }
    *t = &((*(*t))->node);
  }
  printf("-3:%ld\n", tmp_val);
  e_res->data.int_res = tmp_val;
}

void eval_list(struct abs_tree ***t, struct eval_result *e_res) {
  if (((*(*t))->token) == list_end) {
    e_res->type = str_type;
    e_res->data.str_res = "()";
  } else if (((*(*t))->token) == list_start) {
    *t = &((*(*t))->node);
    eval_list(t, e_res);
  } else if (((*(*t))->token) == op_plus) {
    *t = &((*(*t))->node);
    eval_add_op(t, e_res);
  } else if (((*(*t))->token) == op_minu) {
    *t = &((*(*t))->node);
    eval_minu_op(t, e_res);
  }
}

struct eval_result *eval(struct abs_tree *parsed_abst) {
  struct eval_result *e_res =
      (struct eval_result *)malloc(sizeof(struct eval_result));
  struct abs_tree **tracer = &parsed_abst;

  while ((*tracer)->token != program_end) {
    if ((*tracer)->token == list_start) {
      eval_list(&tracer, e_res);
    } else if ((*tracer)->token == op_plus) {
      eval_add_op(&tracer, e_res);
    } else if ((*tracer)->token == op_minu) {
      eval_minu_op(&tracer, e_res);
    }
    tracer = &(*tracer)->node;
  }
  return e_res;
}
