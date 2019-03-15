project(CRawl)
add_executable(crawl main.c parser.c)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
