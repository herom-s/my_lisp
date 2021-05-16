#include "../include/parser.h"
#include "../include/lexer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void abst_print_data(struct abs_tree *tree) {
  switch (tree->token) {
  case num:
  case neg_num:
    printf("%d", *((int *)tree->data.int_data));
    break;
  case flo_num:
    printf("%f", *((double *)tree->data.double_data));
    break;
  case string:
    printf("%s", (char *)tree->data.str_data);
    break;
  }
}

void abst_print_tree(struct abs_tree *tree) {
  printf("Tree_a:%p:Data: ", (void *)tree);
  abst_print_data(tree);
  printf("\n");
  if(tree->node)
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

  switch (token) {
  case num:
  case neg_num:
    new->data.int_data = (int64_t *) data;
    printf("Token = %s data=%ld new_D=%ld  \n", print_token(token), *((int64_t *) data), *new->data.int_data);
    abst_print_data(new);
    break;
  case flo_num:
    new->data.double_data = (double *)data;
    break;
  case string:
    new->data.str_data = (char *)data;
    break;
    /*
  default:
    if (data) {
      new->data.str_data = "ERROR: IN Data Token";
    } else {
      new->node->data.str_data = data;
    }
    break;
    */
  }

  abst_print_tree(new);

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
  size_t i = 0;

  abst_init(&parsed_str);

  while (token != program_end && i <= 10){
    printf("input=%s token=%s i=%lu ic=%c\n", input, print_token(token), i, *input);
    i++;
    switch (token) {
    case list_start:
      abst_add(&parsed_str, token, NULL); break;
    case list_end:
      abst_add(&parsed_str, token, NULL); break;
    case num: {
      /* int numb; */
      /* char *end; */
      /* numb = strtol(input, &end, 10); */
      /* input = end; */
      /* printf("Number = %d\n", numb); */
      /* abst_add(&parsed_str, token, (void *)&numb); */
      /* break; */
    }
    case neg_num: {
      int numb;
      char *end;
      numb = strtol(input, &end, 10);
      input = end;
      abst_add(&parsed_str, token, (void *)&numb);
      break;
    }
    case flo_num: {
      double fnum;
      char *end;
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
    token = get_token(input++);
  }
  return parsed_str;
}

