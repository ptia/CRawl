struct stmt {
  enum {varas, arras, defunc, ifels, wloop, retrn, block} kind;
  union {
    struct { char *lhs; struct expr *rhs; } varas;
    struct { char *lhs; int index; struct expr *rhs; } arras;
    struct { char *name; int argc; char **args; } defunc;
    struct { struct expr *pred; struct stmt *then; struct stmt *els; } ifels;
    struct { struct expr *pred; struct stmt *code; } wloop;
    struct { struct expr *expr; } retrn;
    struct { struct stmt *fst; } block;
  };
  struct stmt *next;
};

struct expr {
  enum {var, arr, num, str} kind;
  union {
    struct { char *name; } var;
    struct { char *name; int index; } arr;
    struct { int val; } num;
    struct { char *val; } str;
  };
};
