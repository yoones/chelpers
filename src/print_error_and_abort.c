#include <stdio.h>
#include <stdlib.h>

void print_error_and_abort(char *func_name)
{
  perror(func_name);
  exit(EXIT_FAILURE);
}
