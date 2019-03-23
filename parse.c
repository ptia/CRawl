#include "parse.h"
#include "parse_stmt.h"
#include "lang.h"
#include "toks.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

struct stmt *parse(FILE *file) 
{
  assert (file != NULL);
  const char *toks = ftoks(file);
  return parse_stmt(&toks);
}
