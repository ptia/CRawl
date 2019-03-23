#include "toks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

bool streq(const char *s1, const char *s2)
{
  return !strcmp(s1, s2);
}

bool is_id(const char *str)
{
  if (!isalpha(*str))
    return false;
  for (; *str; str++)
    if (!isalnum(*str))
      return false;
  return true;
}

bool is_digits(const char *str)
{
  for (; *str; str++)
    if (!isdigit(*str))
      return false;
  return true;
}

unsigned int fsize(FILE *file)
{
  fseek(file, 0, SEEK_END);
  unsigned int size = ftell(file);
  fseek(file, 0, SEEK_SET);
  return size;
}

char *ftoks(FILE *file)
{
  char *out = malloc(2 * fsize(file));
  unsigned int i = 0;
  char c = fgetc(file);
  while (c != EOF) {
    if (isspace(c)) {
      c = fgetc(file);
    } else if (isalnum(c)) {
      for (; isalnum(c); c = fgetc(file)) 
        out[i++] = c;
      out[i++] = '\0';
    } else {
      out[i++] = c;
      out[i++] = '\0';
      c = fgetc(file);
    }
  }
  out[i] = EOF;
  return out;
}

const char *next(const char **toks)
{
  if (**toks == EOF)
    return *toks;
  const char *prev = *toks;
  while (**toks)
    (*toks)++;
  (*toks)++;
  return prev;
}

const char *peek_next(const char **toks)
{
  return *toks;
}

void print_toks(const char *fst_tok)
{
  while (*fst_tok != EOF)
    printf("%s ", next(&fst_tok));
}

