#include "parse_stmt.h"
#include "lang.h"
#include "toks.h"
#include "parse_expr.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define expect(pred) do { if (!(pred)) goto error; } while (0)

struct stmt *parse_varass(const char **toks)
{
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(*out));
  out->kind = varass;
  
  out->varass.var = next(toks);
  expect (is_id(out->varass.var));
  expect (streq(next(toks) ,"="));
  out->varass.val = parse_expr(toks);
  expect (out->varass.val);
  expect (streq(next(toks), ";"));
  return out;

error:
  free_stmt(out);
  *toks = toks_pre;
  return NULL;
}

struct stmt *parse_arrass(const char **toks)
{
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(*out));
  out->kind = arrass;
  
  out->arrass.var = next(toks);
  expect (is_id(out->varass.var));
  expect (streq(next(toks) ,"["));
  out->arrass.index = parse_expr(toks);
  expect (streq(next(toks), "]"));
  expect (streq(next(toks) ,"="));
  out->arrass.val = parse_expr(toks);
  expect (out->arrass.val);
  expect (streq(next(toks), ";"));
  return out;

error:
  free_stmt(out);
  *toks = toks_pre;
  return NULL;
}

struct stmt *parse_ifels(const char **toks) {
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(*out));
  out->kind = ifels;

  expect (streq(next(toks), "if"));
  expect (streq(next(toks), "("));
  out->ifels.pred = parse_expr(toks);
  expect (out->ifels.pred);
  expect (streq(next(toks), ")"));
  out->ifels.then = parse_stmt(toks);
  expect (out->ifels.then);
  if (streq(next(toks), "else")) {
    out->ifels.els = parse_stmt(toks);
    expect (out->ifels.els);
  }
  return out;
  
error:
  free_stmt(out);
  *toks = toks_pre;
  return NULL;
}

struct stmt *parse_wloop(const char **toks) {
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(*out));
  out->kind = wloop;

  expect (streq(next(toks), "while"));
  expect (streq(next(toks), "("));
  out->wloop.pred = parse_expr(toks);
  expect (out->wloop.pred);
  expect (streq(next(toks), ")"));
  out->wloop.body = parse_stmt(toks);
  expect (out->wloop.body);
  return out;
  
error:
  free_stmt(out);
  *toks = toks_pre;
  return NULL;
}

struct stmt *parse_retrn(const char **toks) {
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(*out));
  out->kind = retrn;

  expect (streq(next(toks), "return"));
  out->retrn.val = parse_expr(toks);
  expect (out->retrn.val);
  out->wloop.body = parse_stmt(toks);
  expect (out->wloop.body);
  expect (streq(next(toks), ";"));
  return out;
  
error:
  free_stmt(out);
  *toks = toks_pre;
  return NULL;
}

struct stmt *parse_defunc(const char **toks)
{
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(*out));
  out->kind = defunc;

  expect (streq(next(toks), "def"));
  out->defunc.name = next(toks);
  expect (is_id(out->defunc.name));
  expect (streq(next(toks), "("));
  out->defunc.args = parse_list(toks);
  expect (out->defunc.args);
  for (struct expr *arg = out->defunc.args->list_next;
       arg;
       arg = arg->list_next)
    expect (arg->kind == var);
  out->defunc.body = parse_stmt(toks);
  expect (out->defunc.body);
  return out;

error:
  free_stmt(out);
  *toks = toks_pre;
  return NULL;
}

struct stmt *parse_block(const char **toks)
{
  const char *toks_pre = *toks;
  struct stmt *out = calloc(1, sizeof(*out));
  out->kind = block;

  expect (streq(next(toks) ,"{"));
  struct stmt *curr = out;
  while ((curr->block_next = parse_stmt(toks))) {
    curr = curr->block_next;
  }
  expect (streq(next(toks) ,"}"));

error:
  free_stmt(out);
  *toks = toks_pre;
  return NULL;
}

struct stmt *parse_stmt(const char **toks)
{
  struct stmt *out;
  if ((out = parse_varass(toks)))
    return out;
  if ((out = parse_arrass(toks)))
    return out;
  if ((out = parse_ifels(toks)))
    return out;
  if ((out = parse_wloop(toks)))
    return out;
  if ((out = parse_retrn(toks)))
    return out;
  if ((out = parse_defunc(toks)))
    return out;
  if ((out = parse_block(toks)))
    return out;
  return NULL;
}
