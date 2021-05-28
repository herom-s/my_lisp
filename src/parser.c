#include "../include/parser.h"
#include "../include/lexer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void abst_print_data(struct abs_tree *tree) {
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
  }
}

void abst_print_tree(struct abs_tree *tree) {
  printf("Tree_a:%p:token:%s:Data: ", (void *)tree, print_token(tree->token));
  abst_print_data(tree);
  printf("\n");
  if(tree->node)
    abst_print_tree(tree->node);
}

void abst_init(struct abs_tree **tree) {
  struct abs_tree *tmp = (struct abs_tree *) malloc(sizeof(struct abs_tree));
  if (!tmp)
    exit(EXIT_FAILURE);
  tmp->token = empty;
  tmp->node = NULL;
  tmp->line = 0;
  *tree = tmp;
}

/*
	abst_add is bugged need to work more on it,
	trying to add always to the end of lis and
	checking for a null at end dont work, i need
	make a way to check if the currety tree in
	fuction is not null and the next node is not
	null i need head store pointer
*/
void abst_add(struct abs_tree **tree, enum tree_token token, void *data) {
  struct abs_tree **tracer = tree;
  struct abs_tree *new = NULL;
  abst_init(&new);

  new->token = token;

  switch (token) {
  case num:
  case neg_num:
    new->data.int_data = *(int64_t *) data;
    break;
  case flo_num:
    new->data.double_data = *(double *)data;
    break;
  case string:
    new->data.str_data = (char *)data;
    break;
  default:
    if (data) {
      new->data.str_data = "ERROR: IN Data Token";
    }
    break;
  }

  while ((*tracer)){
    tracer = &(*tracer)->node;
  }


  new->node = *tracer;
  *tracer = new;

}

void abst_remove_node(struct abs_tree *tree) {
  if (tree->token == string)
    free(tree->data.str_data);

  tree->token = empty;
  free(tree);
}

void abst_destroy(struct abs_tree *tree) {
  if (tree) {
    abst_destroy(tree->node);
    abst_remove_node(tree);
  }
}

struct abs_tree *parser(char *input) {
  struct abs_tree *parsed_str = NULL;
  enum tree_token token = program_start;

  abst_init(&parsed_str);

  parsed_str->token = token;

  while ((token = get_token(input++))!= program_end){
    /* printf("input=%s token=%s i=%lu ic=%c\n", input, print_token(token), i, *input); */
    switch (token) {
    case list_start:
      abst_add(&parsed_str, token, NULL); break;
    case list_end:
      abst_add(&parsed_str, token, NULL); break;
    case num: {
      int64_t numb = 0;
      char *end;
      input--;
      numb = strtoll(input, &end, 10);
      input = end;
      abst_add(&parsed_str, token, (void *)&numb);
      break;
    }
    case neg_num: {
      int64_t numb = 0;
      char *end;
      input--;
      numb = strtoll(input, &end, 10);
      input = end;
      abst_add(&parsed_str, token, (void *)&numb);
      break;
    }
    case flo_num: {
      double fnum;
      char *end;
      input--;
      fnum = strtod(input, &end);
      input = end;
      abst_add(&parsed_str, token, (void *)&fnum);
      break;
    }
    case op_plus:
      abst_add(&parsed_str, token, NULL); break;
    case op_minu:
      abst_add(&parsed_str, token, NULL); break;
    }
  }

  abst_add(&parsed_str, token, NULL);

  return parsed_str;
}
