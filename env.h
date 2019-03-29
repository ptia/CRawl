#pragma once

struct envmt {
  struct list *assmts;
  struct list *fundefs;
}

struct assmt {
  char *var;
  void *val;
  enum {num, str, err} type;
};

struct fundef {
  char *name;
  struct list *args;
}
