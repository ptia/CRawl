project(CRawl)
add_executable(crawl main.c lang.c parse.c toks.c parse_stmt.c parse_expr.c)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
