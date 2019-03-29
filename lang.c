#include "lang.h"
#include "list/list.h"
#include <stdlib.h>
#include <stdio.h>

void free_stmt(struct stmt *stmt)
{
  if (!stmt)
    return;
  switch (stmt->kind) {
    case assign:
      free_expr(stmt->assign.lhs);
      free_expr(stmt->assign.rhs);
      break;

    case funcall:
      free_expr(stmt->funcall.funcexpr);
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
      l_free(stmt->block.stmts, (void (*) (void *)) free_stmt);
      break;

    case defunc:
      free(stmt->defunc.args);
      free_stmt(stmt->defunc.body);
      break;
  }
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

    case list:
      l_free(expr->list.exprs, (void (*) (void *)) free_expr);
      break;

    case var:
    case num:
    case str:
      break;
  }

  free(expr);
}

void print_stmt(struct stmt *stmt)
{
  switch (stmt->kind) {
    case assign:
      print_expr(stmt->assign.lhs);
      printf(" = ");
      print_expr(stmt->assign.rhs);
      printf(";\n");
      break;

    case funcall:
      print_expr(stmt->funcall.funcexpr);
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
      struct stmt *elem;
      L_FOREACH(stmt->block.stmts, elem)
        print_stmt(elem);
      printf("}\n");
      break;

    case defunc:
      printf("def %s", stmt->defunc.name);
      print_expr(stmt->defunc.args);
      printf("\n");
      print_stmt(stmt->defunc.body);
      break;
  }
}

void print_expr(struct expr *expr)
{
  switch (expr->kind) {
    case var:
      printf("%s", expr->var.name);
      break;

    case arrel:
      printf("%s", expr->arrel.name);
      printf("[");
      print_expr(expr->arrel.index);
      printf("]");
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
      struct expr *elem;
      bool fst = true;
      L_FOREACH(expr->list.exprs, elem) {
        if (fst) 
          fst = false;
        else
          printf(", ");
        print_expr(elem);
      }
      printf(")");
      break;
  }
}
