#include "list.h"
#include <stdlib.h>
#include <assert.h>

void l_push(struct list *l, void *el)
{
  struct l_node *new_node = malloc(sizeof(struct l_node));
  *new_node = (struct l_node) {el, l->lst, NULL};
  if (!l->size)
    l->fst = l->lst = new_node;
  else
    l->lst = l->lst->nxt = new_node;
  l->size++;
}

void *l_pop(struct list *l)
{
  if (!l->size)
    return NULL;
  void *out = l->lst->content;
  if (l->size == 1)
    l->fst = NULL;
  else
    l->lst->prv->nxt = NULL;
  struct l_node *new_last = l->lst->prv;
  free(l->lst);
  l->lst = new_last;
  l->size--;
  return out;
}

void *l_get(struct list *l, int i)
{
  assert (i < l->size);
  for (struct l_node *node = l->fst; node; node = node->nxt)
    if (!i--)
      return node->content;
  return NULL;
}

void l_set(struct list *l, void *el, int i)
{
  assert (i < l->size);
  for (struct l_node *node = l->fst; node; node = node->nxt)
    if (!i--)
      node->content = el;
}

void l_free(struct list *l, void (* free_elem) (void *))
{
  while (l->size)
    if (free_elem)
      free_elem(l_pop(l));
  free(l);
}
