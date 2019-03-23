#pragma once

#include "lang.h"
#include <stdio.h>

struct stmt *parse(FILE *file);
char *ftoks(FILE *file);
void print_toks(const char *fst_tok);
