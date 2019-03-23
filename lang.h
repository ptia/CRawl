#pragma once

struct stmt {
  enum {varass, arrass, ifels, wloop, retrn, defunc, block} kind;
  union {
    struct { const char *var; struct expr *val; } varass;
    struct { const char *var; struct expr *index; struct expr *val; } arrass;
    struct { struct expr *pred; struct stmt *then; struct stmt *els; } ifels;
    struct { struct expr *pred; struct stmt *body; } wloop;
    struct { struct expr *val; } retrn;
    struct { const char *name; int argc; const char **args; struct stmt *body; } defunc;
  };
  struct stmt *block_next;
};

struct expr {
  enum {var, arrel, num, str, list, funcall} kind;
  union {
    struct { const char *name; } var;
    struct { const char *name; int index; } arrel;
    struct { int val; } num;
    struct { const char *val; } str;
    struct { const char *name; struct expr *args; } funcall;
  };
  struct expr *list_next;
};

void free_stmt(struct stmt *stmt);
void free_expr(struct expr *expr);
