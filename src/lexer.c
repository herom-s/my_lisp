#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"

char *print_token(enum tree_token token) {
  char * tmp;
  switch (token) {
  case program_start: tmp = "program_start"; break;
  case program_end: tmp = "program_end"; break;
  case list_start: tmp = "list_start"; break;
  case list_end: tmp = "list_end"; break;
  case op_plus: tmp = "op_plus"; break;
  case op_minu: tmp = "op_minu"; break;
  case op_divi: tmp = "op_divi"; break;
  case op_mult: tmp = "op_mult"; break;
  case decrement: tmp = "decrement"; break;
  case increment: tmp = "increment"; break;
  case num: tmp = "num"; break;
  case neg_num: tmp = "neg_num"; break;
  case flo_num: tmp = "flo_num"; break;
  case string: tmp = "string"; break;
  case error_token: tmp = "error_token"; break;
  case empty: tmp = "empty"; break;
  }
  return tmp;
}


enum tree_token get_token(char *input){
  enum tree_token token, ahead_token;
  token = program_end;
  ahead_token = program_end;

  switch (*input) {
  case '(': token = list_start; break;
  case ')': token = list_end;   break;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9': token = num;        break;
  case '-':{
    ahead_token = look_ahead(input);
    if (ahead_token == num) {
      token = neg_num;
    }else if(ahead_token == space){
      token = op_minu;
    }else if(ahead_token == op_minu){
      token = decrement;
    }else{
      token = op_minu;
    }
    break;
  }
  case '+': token = op_plus;    break;
  case '/': token = op_divi;    break;
  case '*': token = op_mult;    break;
  case ' ': token = space;      break;
  case '\n': token = new_line;  break;
  case '\0': token = program_end; break;
  default: token = error_token; break;
  }
  return token;
}

enum tree_token look_ahead(char *input) {
  enum tree_token token;
  token = get_token((++input));
  return token;
}
