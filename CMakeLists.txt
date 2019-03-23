project(CRawl)
add_executable(crawl main.c lang.c parser.c toks.c)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
