#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/eval.h"
#include "../include/parser.h"

void eval_add_op(struct abs_tree ***t, struct eval_result *e_res) {
  e_res->type = int_type;

  if (((*(*t))->token) == list_start) {
    *t = &((*(*t))->node);
  }

  while (((*(*t))->token) != list_end && ((*(*t))->token) != list_start) {
    if (((*(*t))->token) == num || (*(*t))->token == neg_num) {
      e_res->data.int_res += (*(*t))->data.int_data;
    }
    *t = &((*(*t))->node);
  }
}

void eval_minu_op(struct abs_tree ***t, struct eval_result *e_res) {
  bool first_num = true;

  e_res->type = int_type;
  if (((*(*t))->token) == list_start) {
    *t = &((*(*t))->node);
  }

  while (((*(*t))->token) != list_end && ((*(*t))->token) != list_end) {
    if (((*(*t))->token) == num || (*(*t))->token == neg_num) {
      if (first_num) {
        e_res->data.int_res -= (*(*t))->data.int_data;
        first_num = false;
      } else {
        e_res->data.int_res += (*(*t))->data.int_data;
      }
    }
    *t = &((*(*t))->node);
  }
}

struct eval_result *eval(struct abs_tree *parsed_abst) {
  struct eval_result *e_res =
      (struct eval_result *)malloc(sizeof(struct eval_result));

  struct abs_tree **tracer = &parsed_abst;

  while ((*tracer)->token != program_end) {
    if ((*tracer)->token == op_plus) {
      eval_add_op(&tracer, e_res);
    } else if ((*tracer)->token == op_minu) {
      eval_minu_op(&tracer, e_res);
    }
    tracer = &(*tracer)->node;
  }
  return e_res;
}
