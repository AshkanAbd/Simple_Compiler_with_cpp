#include "ast.cpp"

struct Parser {
private:
    Symbol *symbols;
    size_t symbols_size;
    int pose = 0;
    int line = 1;
    AST *head_ast = nullptr;

    void move_to_eol() {
        while (true) {
            if (str_check((symbols + pose)->get_type(), EOL_T)) {
                break;
            }
            pose++;
        }
    }

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
        if (str_check((symbols + pose)->get_type(), EOL_T)) {
            pose++;
            line++;
            return 1;
        }
        if (var(ast)) {
            if (str_check((symbols + pose)->get_type(), EOL_T)) {
                pose++;
                line++;
                return 1;
            }
            printf("Compile error in line %d: Got '%s', but need '%s'\n", line, (symbols + pose)->get_type(), EOL_T);
            return 0;
        }
        AST *ast1 = new AST;
        if (exp(ast1)) {
            if (str_check((symbols + pose)->get_type(), EOL_T)) {
                pose++;
                line++;
                ast->set_left(ast1, sizeof(AST), AST_TYPE);
                ast->set_condition(PRINT_FLAG);
                return 1;
            }
            printf("Compile error in line %d: Got '%s', but need '%s'\n", line, (symbols + pose)->get_type(), EOL_T);
            return 0;
        }
        return 1;
    }

    int var(AST *ast) {
        if (!(pose + 1 < symbols_size && str_check((symbols + pose + 1)->get_type(), EQU_T))) {
            return 0;
        }
        if (str_check((symbols + pose)->get_type(), VAR_T)) {
            Symbol *symbol = (symbols + pose);
            ast->set_left(symbol, sizeof(Symbol), SYMBOL_TYPE);
            pose++;
            if (str_check((symbols + pose)->get_type(), EQU_T)) {
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
            }
            return 1;
        }
        return 0;
    }

    int exp(AST *ast) {
        AST *ast2 = new AST;
        if (term(ast2)) {
            if (str_check((symbols + pose)->get_type(), PLUS_T)) {
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
            if (str_check((symbols + pose)->get_type(), MINUS_T)) {
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
        if (factor(ast2)) {
            if (str_check((symbols + pose)->get_type(), MULTI_T)) {
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
            if (str_check((symbols + pose)->get_type(), DIV_T)) {
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
            memcpy(ast, ast2, sizeof(AST));
            return 1;
        }
        return 0;
    }

    int factor(AST *ast) {
        AST *ast1 = new AST;
        if (parents(ast1)) {
            memcpy(ast, ast1, sizeof(AST));
            return 1;
        }
        if (id(ast1)) {
            memcpy(ast, ast1, sizeof(AST));
            return 1;
        }
        return 0;
    }

    int parents(AST *ast) {
        if (str_check((symbols + pose)->get_type(), P_O_T)) {
            pose++;
            AST *ast1 = new AST;
            if (exp(ast1)) {
                if (str_check((symbols + pose)->get_type(), P_C_T)) {
                    pose++;
                    memcpy(ast, ast1, sizeof(AST));
                    return 1;
                }
            }
        }
        return 0;
    }

    int id(AST *ast) {
        if (str_check((symbols + pose)->get_type(), NUM_T)) {
            Symbol *symbol = (symbols + pose);
            ast->set_left(symbol, sizeof(Symbol), SYMBOL_TYPE);
            pose++;
            return 1;
        }
        if (str_check((symbols + pose)->get_type(), VAR_T)) {
            Symbol *symbol = (symbols + pose);
            ast->set_left(symbol, sizeof(Symbol), SYMBOL_TYPE);
            pose++;
            return 1;
        }
        printf("Compile error in line %d: Got '%s', but need '%s' or '%s'\n", line, (symbols + pose)->get_type(), NUM_T,
               VAR_T);
        return 0;
    }

public:
    Parser(Symbol *symbols, size_t symbols_size, AST *ast) : symbols_size(symbols_size), head_ast(ast) {
        Parser::symbols = (Symbol *) malloc((symbols_size + 1) * sizeof(Symbol));
        memset(Parser::symbols, 0, (symbols_size + 1) * sizeof(Symbol));
        memcpy(Parser::symbols, symbols, (symbols_size + 1) * sizeof(Symbol));
    }

    void start() {
        stmts(head_ast);
    }
};
