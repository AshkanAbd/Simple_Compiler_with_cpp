#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <strings.h>
#include <regex>
#include <fstream>

// regex
#define VAR "[a-zA-Z][a-zA-Z0-9]*"
#define NUM "[0-9]+[.]?[0-9]*"
#define PLUS "[+]"
#define MINUS "[-]"
#define MULTI "[*]"
#define DIV "[/]"
#define P_O "[(]"
#define P_C "[)]"
#define EQU "[=]"
#define EOL "[;]"

// tokens
#define VAR_T "variable"
#define NUM_T "number"
#define PLUS_T "plus"
#define MINUS_T "minus"
#define MULTI_T "multiply"
#define DIV_T "divide"
#define P_O_T "open_p"
#define P_C_T "close_p"
#define EQU_T "equals"
#define EOL_T ";"

// flags
#define AST_FLAG 0
#define VAR_FLAG 1
#define NUM_FLAG 2
#define PLUS_FLAG 3
#define MINUS_FLAG 4
#define MULTI_FLAG 5
#define DIV_FLAG 6
#define PAR_FLAG 7
#define EQU_FLAG 8
#define SYMBOL_FLAG 9
#define PRINT_FLAG 10
#define EOL_FLAG 11

//types
#define AST_TYPE 0
#define SYMBOL_TYPE 1
