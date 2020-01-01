#include "ast.cpp"

struct Parser {
private:
    Symbol *symbols = nullptr;
    size_t symbols_size = 0;
    int pose = 0;
    int line = 1;
    AST *head_ast = nullptr;

    int stmts(AST *ast) {
        if (symbols_size <= pose) {
            return 1;
        }
        AST *ast1 = new AST;
        if (stmt(ast1)) {
            ast->set_left(ast1, sizeof(AST), AST_TYPE);
            ast->set_condition(EOL_FLAG);
            AST *ast2 = new AST;
            if (stmts(ast2)) {
                ast->set_right(ast2, sizeof(AST), AST_TYPE);
                return 1;
            }
        }
        return 0;
    }

    int stmt(AST *ast) {
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), EOL_T)) {
            pose++;
            line++;
            return 1;
        }
        int pre_pose = pose;
        if (var(ast)) {
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), EOL_T)) {
                pose++;
                infix_to_postfix(symbols, pre_pose, pose - pre_pose, line);
                line++;
                return 1;
            }
            if (symbols_size > pose) {
                printf("Compile error in line %d: Got '%s', but need '%s'.\n", line, (symbols + pose)->get_type(),
                       EOL_T);
            } else {
                printf("Compile error in line %d: Got nothing, but need '%s'.\n", line, EOL_T);
            }
            return 0;
        }
        AST *ast1 = new AST;
        if (exp(ast1)) {
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), EOL_T)) {
                pose++;
                infix_to_postfix(symbols, pre_pose, pose - pre_pose, line);
                line++;
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(PRINT_FLAG);
                return 1;
            }
            if (symbols_size > pose) {
                printf("Compile error in line %d: Got '%s', but need '%s'.\n", line, (symbols + pose)->get_type(),
                       EOL_T);
            } else {
                printf("Compile error in line %d: Got nothing, but need '%s'.\n", line, EOL_T);
            }
            return 0;
        }
        return 0;
    }

    int var(AST *ast) {
        if (!(pose + 1 < symbols_size && str_check((symbols + pose + 1)->get_type(), EQU_T))) {
            return 0;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), VAR_T)) {
            Symbol *symbol = (symbols + pose);
            ast->set_left(symbol, sizeof(Symbol), SYMBOL_TYPE);
            pose++;
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), EQU_T)) {
                pose++;
                AST *ast1 = new AST;
                if (exp(ast1)) {
                    ast->set_right(ast1, sizeof(AST), AST_TYPE);
                    ast->set_condition(EQU_FLAG);
                    return 1;
                }
                return 0;
            } else {
                ast->set_condition(PRINT_FLAG);
                return 1;
            }
        }
        return 0;
    }

    int exp(AST *ast) {
        AST *ast3 = new AST;
        AST *ast2 = new AST;
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), MINUS_T)) {
            pose++;
            if (term(ast2)) {
                ast3->set_left(ast2, sizeof(AST), AST_TYPE);
                ast3->set_condition(UNARY_MINUS_FLAG);
                if (symbols_size > pose && str_check((symbols + pose)->get_type(), PLUS_T)) {
                    pose++;
                    AST *ast1 = new AST;
                    if (exp(ast1)) {
                        ast->set_left(ast3, sizeof(AST), AST_TYPE);
                        ast->set_right(ast1, sizeof(AST), AST_TYPE);
                        ast->set_condition(PLUS_FLAG);
                        return 1;
                    }
                    return 0;
                }
                if (symbols_size > pose && str_check((symbols + pose)->get_type(), MINUS_T)) {
                    pose++;
                    AST *ast1 = new AST;
                    if (exp(ast1)) {
                        ast->set_left(ast3, sizeof(AST), AST_TYPE);
                        ast->set_right(ast1, sizeof(AST), AST_TYPE);
                        ast->set_condition(MINUS_FLAG);
                        return 1;
                    }
                    return 0;
                }
                memcpy(ast, ast3, sizeof(AST));
                return 1;
            }
            return 0;
        }
        if (term(ast2)) {
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), PLUS_T)) {
                pose++;
                AST *ast1 = new AST;
                if (exp(ast1)) {
                    ast->set_left(ast2, sizeof(AST), AST_TYPE);
                    ast->set_right(ast1, sizeof(AST), AST_TYPE);
                    ast->set_condition(PLUS_FLAG);
                    return 1;
                }
                return 0;
            }
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), MINUS_T)) {
                pose++;
                AST *ast1 = new AST;
                if (exp(ast1)) {
                    ast->set_left(ast2, sizeof(AST), AST_TYPE);
                    ast->set_right(ast1, sizeof(AST), AST_TYPE);
                    ast->set_condition(MINUS_FLAG);
                    return 1;
                }
                return 0;
            }
            memcpy(ast, ast2, sizeof(AST));
            return 1;
        }
        return 0;
    }

    int term(AST *ast) {
        AST *ast2 = new AST;
        if (term_pow(ast2)) {
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), MULTI_T)) {
                pose++;
                AST *ast1 = new AST;
                if (term(ast1)) {
                    ast->set_left(ast2, sizeof(AST), AST_TYPE);
                    ast->set_right(ast1, sizeof(AST), AST_TYPE);
                    ast->set_condition(MULTI_FLAG);
                    return 1;
                }
                return 0;
            }
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), DIV_T)) {
                pose++;
                AST *ast1 = new AST;
                if (term(ast1)) {
                    ast->set_left(ast2, sizeof(AST), AST_TYPE);
                    ast->set_right(ast1, sizeof(AST), AST_TYPE);
                    ast->set_condition(DIV_FLAG);
                    return 1;
                }
                return 0;
            }
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), DIV_I_T)) {
                pose++;
                AST *ast1 = new AST;
                if (term(ast1)) {
                    ast->set_left(ast2, sizeof(AST), AST_TYPE);
                    ast->set_right(ast1, sizeof(AST), AST_TYPE);
                    ast->set_condition(DIV_I_FLAG);
                    return 1;
                }
                return 0;
            }
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), MOD_T)) {
                pose++;
                AST *ast1 = new AST;
                if (term(ast1)) {
                    ast->set_left(ast2, sizeof(AST), AST_TYPE);
                    ast->set_right(ast1, sizeof(AST), AST_TYPE);
                    ast->set_condition(MOD_FLAG);
                    return 1;
                }
                return 0;
            }
            memcpy(ast, ast2, sizeof(AST));
            return 1;
        }
        return 0;
    }

    int term_pow(AST *ast) {
        AST *ast2 = new AST;
        if (factor(ast2)) {
            if (symbols_size > pose && str_check((symbols + pose)->get_type(), POW_T)) {
                pose++;
                AST *ast1 = new AST;
                if (term_pow(ast1)) {
                    ast->set_left(ast2, sizeof(AST), AST_TYPE);
                    ast->set_right(ast1, sizeof(AST), AST_TYPE);
                    ast->set_condition(POW_FLAG);
                    return 1;
                }
                return 0;
            }
            memcpy(ast, ast2, sizeof(AST));
            return 1;
        }
        return 0;
    }

    int factor(AST *ast) {
        AST *ast1 = new AST;
        if (unary_minus(ast1)) {
            memcpy(ast, ast1, sizeof(AST));
            return 1;
        }
        if (parents(ast1)) {
            memcpy(ast, ast1, sizeof(AST));
            return 1;
        }
        if (functions(ast1)) {
            memcpy(ast, ast1, sizeof(AST));
            return 1;
        }
        if (id(ast1)) {
            memcpy(ast, ast1, sizeof(AST));
            return 1;
        }
        return 0;
    }

    int unary_minus(AST *ast) {
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), MINUS_T)) {
            pose++;
            AST *ast1 = new AST;
            if (exp(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(UNARY_MINUS_FLAG);
                return 1;
            }
            return 0;
        }
        return 0;
    }

    int functions(AST *ast) {
        AST *ast1 = new AST;
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), SIN_T)) {
            pose++;
            if (parents(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(SIN_FLAG);
                return 1;
            }
            return 0;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), COS_T)) {
            pose++;
            if (parents(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(COS_FLAG);
                return 1;
            }
            return 0;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), TAN_T)) {
            pose++;
            if (parents(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(TAN_FLAG);
                return 1;
            }
            return 0;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), COT_T)) {
            pose++;
            if (parents(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(COT_FLAG);
                return 1;
            }
            return 0;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), LOG_T)) {
            pose++;
            if (parents(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(LOG_FLAG);
                return 1;
            }
            return 0;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), EXP_T)) {
            pose++;
            if (parents(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(EXP_FLAG);
                return 1;
            }
            return 0;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), SQR_T)) {
            pose++;
            if (parents(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(SQR_FLAG);
                return 1;
            }
            return 0;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), SQRT_T)) {
            pose++;
            if (parents(ast1)) {
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(SQRT_FLAG);
                return 1;
            }
            return 0;
        }
        return 0;
    }

    int parents(AST *ast) {
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), P_O_T)) {
            pose++;
            AST *ast1 = new AST;
            if (exp(ast1)) {
                if (symbols_size > pose && str_check((symbols + pose)->get_type(), P_C_T)) {
                    pose++;
                    memcpy(ast, ast1, sizeof(AST));
                    return 1;
                }
                return 0;
            }
        }
        return 0;
    }

    int id(AST *ast) {
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), NUM_T)) {
            Symbol *symbol = (symbols + pose);
            ast->set_left(symbol, sizeof(Symbol), SYMBOL_TYPE);
            pose++;
            return 1;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), PI_T)) {
            Symbol *symbol = (symbols + pose);
            ast->set_left(symbol, sizeof(Symbol), SYMBOL_TYPE);
            pose++;
            return 1;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), NEPER_T)) {
            Symbol *symbol = (symbols + pose);
            ast->set_left(symbol, sizeof(Symbol), SYMBOL_TYPE);
            pose++;
            return 1;
        }
        if (symbols_size > pose && str_check((symbols + pose)->get_type(), VAR_T)) {
            Symbol *symbol = (symbols + pose);
            ast->set_left(symbol, sizeof(Symbol), SYMBOL_TYPE);
            pose++;
            return 1;
        }
        if (symbols_size > pose) {
            printf("Compile error in line %d: Got '%s', but need '%s' or '%s or '%s' or '%s'.\n", line,
                   (symbols + pose)->get_type(), NUM_T, PI_T, NEPER_T, VAR_T);
        } else {
            printf("Compile error in line %d: Got nothing, but need '%s'.\n", line, EOL_T);
        }

        return 0;
    }

public:
    Parser(Symbol *symbols, size_t symbols_size, AST *ast) : symbols_size(symbols_size), head_ast(ast) {
        Parser::symbols = (Symbol *) malloc((symbols_size + 1) * sizeof(Symbol));
        memset(Parser::symbols, 0, (symbols_size + 1) * sizeof(Symbol));
        memcpy(Parser::symbols, symbols, (symbols_size + 1) * sizeof(Symbol));
    }

    int start() {
        return stmts(head_ast);
    }
};
