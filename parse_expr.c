#include "parse_expr.h"
#include "lang.h"
#include "toks.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define expect(pred) do { if (!(pred)) goto error; } while (0)

struct expr *parse_var(const char **toks)
{
  const char *toks_pre = *toks;
  struct expr *out = calloc(1, sizeof(*out));
  out->kind = var;

  out->var.name = next(toks);
  expect (is_id(out->var.name));
  return out;

error:
  free_expr(out);
  *toks = toks_pre;
  return NULL;
}

struct expr *parse_num(const char **toks)
{
  const char *toks_pre = *toks;
  struct expr *out = calloc(1, sizeof(*out));
  out->kind = num;

  const char *val = next(toks);
  expect (is_digits(val));
  out->num.val = atoi(val);
  return out;

error:
  free_expr(out);
  *toks = toks_pre;
  return NULL;
}

struct expr *parse_list(const char **toks)
{
  const char *toks_pre = *toks;
  struct expr *out = calloc(1, sizeof(*out));
  out->kind = list;

  expect (streq(next(toks) ,"("));
  struct expr *curr = out;
  while ((curr->list_next = parse_expr(toks))) {
    curr = curr->list_next;
    const char *delim = peek_next(toks);
    if (streq(delim, ",")) {
      next(toks);
      continue;
    }
  }
  expect (streq(next(toks) ,")"));
  return out;

error:
  free_expr(out);
  *toks = toks_pre;
  return NULL;
}

struct expr *parse_expr(const char **toks)
{
  struct expr *out;
  if ((out = parse_var(toks)))
    return out;
  if ((out = parse_num(toks)))
    return out;
  if ((out = parse_list(toks)))
    return out;
  return NULL;
}
