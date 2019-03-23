#include "lang.h"
#include <stdlib.h>
#include <stdio.h>

void free_stmt(struct stmt *stmt)
{
  if (!stmt)
    return;
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
  if (!expr)
    return;
  switch (expr->kind) {
    case arrel:
      free_expr(expr->arrel.index);
      break;

    case funcval:
      free_expr(expr->funcval.args);
      break;

    case var:
    case num:
    case str:
    case list:
      break;
  }

  free_expr(expr->list_next);
  free(expr);
}

void print_stmt(struct stmt *stmt)
{
  switch (stmt->kind) {
    case varass:
      printf("%s = ", stmt->varass.var);
      print_expr(stmt->varass.val);
      printf(";\n");
      break;

    case arrass:
      printf("%s [", stmt->arrass.var);
      print_expr(stmt->arrass.index);
      printf("] = ");
      print_expr(stmt->arrass.val);
      printf(";\n");
      break;

    case ifels:
      printf("if (");
      print_expr(stmt->ifels.pred);
      printf(")\n");
      print_stmt(stmt->ifels.then);
      if (stmt->ifels.els) {
        printf("else\n");
        print_stmt(stmt->ifels.els);
      }
      break;

    case wloop:
      printf("while (");
      print_expr(stmt->wloop.pred);
      printf(") \n");
      print_stmt(stmt->wloop.body);
      break;

    case retrn:
      printf("return ");
      print_expr(stmt->retrn.val);
      printf(";\n");
      break;

    case block:
      printf("{\n");
      if (stmt->block.fst)
        print_stmt(stmt->block.fst);
      printf("}\n");
      break;

    case defunc:
      printf("def %s", stmt->defunc.name);
      print_expr(stmt->defunc.args);
      printf("\n");
      print_stmt(stmt->defunc.body);
      break;
  }

  if (stmt->block_next)
    print_stmt(stmt->block_next);
}

void print_expr(struct expr *expr)
{
  switch (expr->kind) {
    case var:
      printf("%s", expr->var.name);
      break;

    case arrel:
      printf("%s", expr->arrel.name);
      print_expr(expr->arrel.index);
      break;

    case num:
      printf("%d", expr->num.val);
      break;

    case str:
      printf("\"%s\"", expr->str.val);
      break;

    case funcval:
      printf("%s", expr->funcval.name);
      print_expr(expr->funcval.args);
      break;

    case list:
      printf("(");
      if (expr->list.fst)
        print_expr(expr->list.fst);
      printf(")");
      break;
  }

  if (expr->list_next) {
    printf(", ");
    print_expr(expr->list_next);
  }
}
