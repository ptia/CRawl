#include "lang.h"
#include <stdlib.h>

void free_stmt(struct stmt *stmt)
{
  switch (stmt->kind) {
    case varass:
      free_expr(stmt->varass.val);
      break;

    case arrass:
      free_expr(stmt->arrass.index);
      free_expr(stmt->arrass.val);
      break;

    case ifels:
      free_expr(stmt->ifels.pred);
      free_stmt(stmt->ifels.then);
      free_stmt(stmt->ifels.els);
      break;

    case wloop:
      free_expr(stmt->wloop.pred);
      free_stmt(stmt->wloop.body);
      break;

    case retrn:
      free_expr(stmt->retrn.val);
      break;

    case block:
      break;

    case defunc:
      free(stmt->defunc.args);
      free_stmt(stmt->defunc.body);
      break;

  }

  free_stmt(stmt->block_next);
  free(stmt);
}

void free_expr(struct expr *expr)
{

}
