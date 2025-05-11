#include "../include/eval.h"
#include "../include/parser.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void eval_list(struct abs_tree **t, struct eval_result *e_res);

void eval_add_op(struct abs_tree **t, struct eval_result *e_res) {
  if (!t || !*t || !e_res)
    return;

  int64_t result = 0;
  e_res->type = int_type;

  while (*t && (*t)->token != list_end && (*t)->token != program_end) {
    if ((*t)->token == list_start) {
      *t = (*t)->node;
      struct eval_result inner;
      eval_list(t, &inner);

      if (inner.type == int_type) {
        result += inner.data.int_res;
      } else if (inner.type == double_type) {
        result += (int64_t)inner.data.double_res;
      }
    } else if ((*t)->token == num) {
      result += (*t)->data.int_data;
      *t = (*t)->node;
    } else if ((*t)->token == neg_num) {
      result += (*t)->data.int_data;
      *t = (*t)->node;
    } else {
      *t = (*t)->node;
    }
  }

  if (*t && (*t)->token == list_end) {
    *t = (*t)->node;
  }

  e_res->data.int_res = result;
}

void eval_minu_op(struct abs_tree **t, struct eval_result *e_res) {
  if (!t || !*t || !e_res)
    return;

  int64_t result = 0;
  bool first = true;
  e_res->type = int_type;

  while (*t && (*t)->token != list_end && (*t)->token != program_end) {
    if ((*t)->token == list_start) {
      *t = (*t)->node;
      struct eval_result inner;
      eval_list(t, &inner);

      if (inner.type == int_type) {
        if (first) {
          result = inner.data.int_res;
          first = false;
        } else {
          result -= inner.data.int_res;
        }
      } else if (inner.type == double_type) {
        if (first) {
          result = (int64_t)inner.data.double_res;
          first = false;
        } else {
          result -= (int64_t)inner.data.double_res;
        }
      }
    } else if ((*t)->token == num) {
      if (first) {
        result = (*t)->data.int_data;
        first = false;
      } else {
        result -= (*t)->data.int_data;
      }
      *t = (*t)->node;
    } else if ((*t)->token == neg_num) {
      if (first) {
        result = (*t)->data.int_data;
        first = false;
      } else {
        result -= (*t)->data.int_data;
      }
      *t = (*t)->node;
    } else {
      *t = (*t)->node;
    }
  }

  if (*t && (*t)->token == list_end) {
    *t = (*t)->node;
  }

  e_res->data.int_res = result;
}

void eval_list(struct abs_tree **t, struct eval_result *e_res) {
  if (!t || !*t || !e_res) {
    if (e_res) {
      e_res->type = str_type;
      e_res->data.str_res = "NULL";
    }
    return;
  }

  if ((*t)->token == list_start) {
    *t = (*t)->node;
  }

  if (!*t) {
    e_res->type = str_type;
    e_res->data.str_res = "()";
    return;
  }

  switch ((*t)->token) {
  case op_plus:
    *t = (*t)->node;
    eval_add_op(t, e_res);
    break;
  case op_minu:
    *t = (*t)->node;
    eval_minu_op(t, e_res);
    break;
  case num:
    e_res->type = int_type;
    e_res->data.int_res = (*t)->data.int_data;
    *t = (*t)->node;
    if (*t && (*t)->token == list_end) {
      *t = (*t)->node;
    }
    break;
  case neg_num:
    e_res->type = int_type;
    e_res->data.int_res = (*t)->data.int_data;
    *t = (*t)->node;
    if (*t && (*t)->token == list_end) {
      *t = (*t)->node;
    }
    break;
  case flo_num:
    e_res->type = double_type;
    e_res->data.double_res = (*t)->data.double_data;
    *t = (*t)->node;
    if (*t && (*t)->token == list_end) {
      *t = (*t)->node;
    }
    break;
  default:
    while (*t && (*t)->token != list_end && (*t)->token != program_end) {
      *t = (*t)->node;
    }
    if (*t && (*t)->token == list_end) {
      *t = (*t)->node;
    }
    e_res->type = str_type;
    e_res->data.str_res = "()";
  }
}

struct eval_result *eval(struct abs_tree *parsed_abst) {
  struct eval_result *e_res = malloc(sizeof(struct eval_result));
  if (!e_res)
    return NULL;

  e_res->type = str_type;
  e_res->data.str_res = "()";

  struct abs_tree *cursor = parsed_abst;

  while (cursor && cursor->token != program_end) {
    if (cursor->token == list_start) {
      cursor = cursor->node;
      eval_list(&cursor, e_res);
    } 
    else if (cursor->token == num) {
      e_res->type = int_type;
      e_res->data.int_res = cursor->data.int_data;
      cursor = cursor->node;
    }
    else if (cursor->token == neg_num) {
      e_res->type = int_type;
      e_res->data.int_res = cursor->data.int_data;
      cursor = cursor->node;
    }
    else if (cursor->token == flo_num) {
      e_res->type = double_type;
      e_res->data.double_res = cursor->data.double_data;
      cursor = cursor->node;
    }
    else {
      cursor = cursor->node;
    }
  }
  return e_res;
}