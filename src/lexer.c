#include "../include/lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *print_token(enum tree_token token) {
  char *tmp = NULL;
  switch (token) {
  case program_start:
    tmp = "program_start";
    break;
  case program_end:
    tmp = "program_end";
    break;
  case list_start:
    tmp = "list_start";
    break;
  case list_end:
    tmp = "list_end";
    break;
  case op_plus:
    tmp = "op_plus";
    break;
  case op_minu:
    tmp = "op_minu";
    break;
  case op_divi:
    tmp = "op_divi";
    break;
  case op_mult:
    tmp = "op_mult";
    break;
  case decrement:
    tmp = "decrement";
    break;
  case increment:
    tmp = "increment";
    break;
  case num:
    tmp = "num";
    break;
  case neg_num:
    tmp = "neg_num";
    break;
  case flo_num:
    tmp = "flo_num";
    break;
  case string:
    tmp = "string";
    break;
  case new_line:
    tmp = "new_line";
    break;
  case point:
    tmp = "point";
    break;
  case comma:
    tmp = "comma";
    break;
  case space:
    tmp = "space";
    break;
  case error_token:
    tmp = "error_token";
    break;
  case empty:
    tmp = "empty";
    break;
  }
  return tmp;
}

enum tree_token look_ahead(char *input) {
  if (!input || !*input)
    return program_end;

  char next_char = *(input + 1);

  if (next_char == '\0')
    return program_end;

  if (isdigit(next_char))
    return num;

  switch (next_char) {
  case '(':
    return list_start;
  case ')':
    return list_end;
  case '+':
    return op_plus;
  case '-':
    return op_minu;
  case '*':
    return op_mult;
  case '/':
    return op_divi;
  case '.':
    return point;
  case ',':
    return comma;
  case ' ':
    return space;
  case '\n':
    return new_line;
  default:
    if (isalpha(next_char))
      return string;
    return error_token;
  }
}

enum tree_token get_token(char *input) {
  if (!input || !*input)
    return program_end;

  enum tree_token token = program_end;
  enum tree_token ahead_token;

  switch (*input) {
  case '(':
    token = list_start;
    break;
  case ')':
    token = list_end;
    break;
  case '.':
    token = point;
    break;
  case ',':
    token = comma;
    break;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    ahead_token = look_ahead(input);
    if (ahead_token == point || ahead_token == comma) {
      token = flo_num;
    } else {
      token = num;
    }
    break;
  case '-':
    ahead_token = look_ahead(input);
    if (isdigit(*(input + 1))) {
      token = neg_num;
    } else if (ahead_token == space || ahead_token == list_start) {
      token = op_minu;
    } else if (ahead_token == op_minu) {
      token = decrement;
    } else {
      token = op_minu;
    }
    break;
  case '+':
    token = op_plus;
    break;
  case '/':
    token = op_divi;
    break;
  case '*':
    token = op_mult;
    break;
  case ' ':
    token = space;
    break;
  case '\n':
    token = new_line;
    break;
  case '\0':
    token = program_end;
    break;
  default:
    if (isalpha(*input)) {
      token = string;
    } else {
      token = error_token;
    }
    break;
  }
  return token;
}
