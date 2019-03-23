#include <stdbool.h>
#include <stdio.h>

bool streq(const char *s1, const char *s2);
bool is_id(const char *str);
char *ftoks(FILE *file);
const char *next(const char **toks);
void print_toks(const char *fst_tok);
