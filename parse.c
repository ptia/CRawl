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
  //TODO
  assert (file != NULL);
  const char *toks = ftoks(file);
  struct stmt *fst = parse_stmt(&toks);
  return fst;
}
