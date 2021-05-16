#include <stdio.h>
#include "../include/input.h"

void read_curr_line(char *input){
  fgets(input, INPUT_BUFF_SIZE, stdin);
}
