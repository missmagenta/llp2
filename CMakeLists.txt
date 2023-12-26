cmake_minimum_required(VERSION 3.26)
project(llp2 C)

set(CMAKE_C_STANDARD 11)

add_executable(llp2
        lex.yy.c
        parser.tab.c
        src/lib/ast.c
        src/lib/printer.c)
