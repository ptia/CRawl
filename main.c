#include "lang.h"
#include "parse/parse.h"
#include <stdio.h>

int main(int argc, char **args) 
{
  if (!(argc == 2)) {
    printf("requires 1 argument\n");
    return 1;
  }
  struct stmt *prgm = parse(fopen(args[1], "r"));
  if (!prgm) {
    printf("parse error\n");
    return 1;
  }
  print_stmt(prgm);
}
