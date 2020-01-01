#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <strings.h>
#include <regex>
#include <fstream>
#include <cmath>

// tokens
#define VAR_T "variable"
#define NUM_T "number"
#define PLUS_T "+"
#define MINUS_T "-"
#define MULTI_T "*"
#define DIV_T "/"
#define DIV_I_T "div"
#define MOD_T "mod"
#define POW_T "^"
#define PI_T "pi"
#define NEPER_T "neper"
#define SIN_T "sin"
#define COS_T "cos"
#define TAN_T "tan"
#define COT_T "cot"
#define LOG_T "log"
#define EXP_T "exp"
#define SQR_T "sqr"
#define SQRT_T "sqrt"
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
#define DIV_I_FLAG 12
#define MOD_FLAG 13
#define POW_FLAG 14
#define UNARY_MINUS_FLAG 15
#define SIN_FLAG 16
#define COS_FLAG 17
#define TAN_FLAG 18
#define COT_FLAG 19
#define LOG_FLAG 20
#define EXP_FLAG 21
#define SQR_FLAG 22
#define SQRT_FLAG 23

// types
#define AST_TYPE 0
#define SYMBOL_TYPE 1

// undefined vars behavior;
#define undefined_vars  0;

