#include "lang.h"
#include "parser.h"
#include "toks.h"
#include <stdio.h>

int main(int argc, char **args) 
{
  char *toks = ftoks(fopen("test/def.cr", "r"));
  print_toks(toks);
}
