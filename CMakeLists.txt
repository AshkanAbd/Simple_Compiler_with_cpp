cmake_minimum_required(VERSION 3.14)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler main.cpp lexer.cpp tokens.h symbol.cpp parser.cpp var.cpp functions.cpp ast.cpp read_ast.cpp)

set_target_properties(Compiler PROPERTIES LINK_FLAGS -Wl, --stack, 10000000)
target_compile_options(Compiler PRIVATE "SHELL:--param ggc-min-expand=1")
target_compile_options(Compiler PRIVATE "SHELL:--param ggc-min-heapsize=32768")
