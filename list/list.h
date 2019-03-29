#pragma once

#include <stdbool.h>

struct list {
  struct l_node *fst;
  struct l_node *lst;
  unsigned int size;
};

struct l_node {
  void *content;
  struct l_node *prv;
  struct l_node *nxt;
};

void l_push(struct list *l, void *el);
void *l_pop(struct list *l);

void *l_get(struct list *l, int i);
void l_set(struct list *l, void *el, int i);

void l_add(struct list *l, void *el, int i);
bool l_rmv(struct list *l, int i);

void l_free(struct list *l, void (* free_elem) (void *));

#define L_FOREACH(LIST, ELEM) \
  for (struct l_node * ELEM ## _l_node  = LIST->fst; \
       ELEM ## _l_node  && ((ELEM =  ELEM ## _l_node ->content) || true); \
       ELEM ## _l_node  =  ELEM ## _l_node ->nxt)
