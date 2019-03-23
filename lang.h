#pragma once

struct stmt {
  enum {varass, arrass, defunc, ifels, wloop, retrn, block} kind;
  union {
    struct { const char *var; struct expr *val; } varass;
    struct { const char *var; int index; struct expr *val; } arrass;
    struct { const char *name; int argc; const char **args; struct stmt *body; } defunc;
    struct { struct expr *pred; struct stmt *then; struct stmt *els; } ifels;
    struct { struct expr *pred; struct stmt *body; } wloop;
    struct { struct expr *expr; } retrn;
    struct { struct stmt *fst; } block;
  };
  struct stmt *next;
};

struct expr {
  enum {var, arrel, num, str} kind;
  union {
    struct { const char *name; } var;
    struct { const char *name; int index; } arrel;
    struct { int val; } num;
    struct { const char *val; } str;
    struct { const char *name; int argc; struct expr **args; } funcall;
  };
};
