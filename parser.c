#include "parser.h"
#include "syntax.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

static const int line_len = 128;

void skip_space(char **str)
{
  while (**str && isspace(**str))
    (*str)++;
}

struct stmt *parse_stmt(char *str)
{
  struct stmt *out = malloc(sizeof(str));
}

struct stmt *parse(FILE *file) 
// Pre: file != NULL
{
  struct stmt *fst;

  char line[line_len];
  while (fgets(line, line_len, file)) {
    fst = parse_stmt(line);
  }
}
