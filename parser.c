#include "parser.h"
#include "lang.h"
#include "toks.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define expect(pred) do { if (!(pred)) goto error; } while (0);

static const unsigned int argc_max = 8;

struct stmt *parse_stmt(const char **toks);

struct expr *parse_expr(const char **toks)
{
  return NULL;
}

struct stmt *parse_varass(const char **toks)
{
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(struct stmt));
  out->kind = varass;
  
  out->varass.var = next(toks);
  expect (is_id(out->varass.var))
  expect (streq(next(toks) ,"="))
  out->varass.val = parse_expr(toks);
  expect (out->varass.val)
  expect (streq(next(toks), ";"))
  return out;

error:
  free(out->varass.val);
  free(out);
  *toks = toks_pre;
  return NULL;
}

struct stmt *parse_defunc(const char **toks)
{
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(struct stmt));
  out->kind = defunc;

  expect (streq(next(toks), "@"))
  out->defunc.name = next(toks);
  expect (is_id(out->defunc.name))
  expect (streq(next(toks), "(")) 

  out->defunc.args = malloc(sizeof(char *) * argc_max);
  int argc = 0;
  while (1) {
    expect (argc < argc_max); //TODO: resize
    const char *arg = next(toks);
    if (streq(arg, ")") && argc == 0)
      break;
    expect (is_id(arg))
    out->defunc.args[argc++] = arg;
    const char *delim = next(toks);
    if (streq(delim, ")"))
      break;
    expect (streq(delim, ","))
  }

  out->defunc.argc = argc;
  out->defunc.body = parse_stmt(toks);
  expect (out->defunc.body)
  return out;

error:
 free(out->defunc.args);
 free(out->defunc.body);
 free(out);
 *toks = toks_pre;
 return NULL;
}


struct stmt *parse_stmt(const char **toks)
{
  struct stmt *out;
  if ((out = parse_defunc(toks)))
    return out;
  if ((out = parse_varass(toks)))
    return out;
  
  return NULL;
}

struct stmt *parse(FILE *file) 
{
  //TODO
  assert (file != NULL);
  const char *toks = ftoks(file);
  struct stmt *fst = parse_stmt(&toks);
  return fst;
}
