cmake_minimum_required(VERSION 3.14)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler main.cpp lexer.cpp tokens.h symbol.cpp parser.cpp var.cpp functions.cpp ast.cpp)