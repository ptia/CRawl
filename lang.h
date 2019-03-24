#pragma once

struct stmt {
  enum {assign, ifels, wloop, retrn, defunc, block} kind;
  union {
    struct { struct expr *lhs; struct expr *rhs; } assign;
    struct { struct expr *pred; struct stmt *then; struct stmt *els; } ifels;
    struct { struct expr *pred; struct stmt *body; } wloop;
    struct { struct expr *val; } retrn;
    struct { const char *name; struct expr *args; struct stmt *body; } defunc;
    struct { struct stmt *fst; } block;
  };
  struct stmt *block_next;
};

struct expr {
  enum {var, arrel, num, str, funcval, list} kind;
  union {
    struct { const char *name; } var;
    struct { const char *name; struct expr *index; } arrel;
    struct { int val; } num;
    struct { const char *val; } str;
    struct { const char *name; struct expr *args; } funcval;
    struct { struct expr *fst; } list;
  };
  struct expr *list_next;
};

void free_stmt(struct stmt *stmt);
void free_expr(struct expr *expr);
void print_stmt(struct stmt *stmt);
void print_expr(struct expr *expr);
