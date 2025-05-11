#ifndef LEXER_H
#define LEXER_H

enum tree_token {
  program_start,
  program_end,
  list_start,
  list_end,
  op_plus,
  op_minu,
  op_divi,
  op_mult,
  decrement,
  increment,
  num,
  neg_num,
  flo_num,
  string,
  new_line,
  point,
  comma,
  space,
  error_token,
  empty
};

char *print_token(enum tree_token token);
enum tree_token get_token(char *input);
enum tree_token look_ahead(char *input);
#endif
