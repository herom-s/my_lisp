#include "../include/print.h"
#include "../include/eval.h"
#include <stdio.h>


void print_res(struct eval_result *e_res) {
  switch (e_res->type) {
  case int_type:
    printf("%lld\n", e_res->data.int_res);
    break;
  case double_type:
    printf("%f\n", e_res->data.double_res);
    break;
  case str_type:
    printf("%s\n", e_res->data.str_res);
    break;
  };
}
