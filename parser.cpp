#include "ast.cpp"

struct Parser {
private:
    Symbol *symbols;
    size_t symbols_size;
    int pose = 0;
    Var *vars = nullptr;
    int line = 1;

    static void out(double d) {
        printf(">>> %.6g\n", d);
    }

    void move_to_eol() {
        while (true) {
            if (str_check((symbols + pose)->get_type(), EOL_T)) {
                break;
            }
            pose++;
        }
    }

    int stmts() {
        if (symbols_size <= pose) {
            return 1;
        }
        if (stmt()) {
            return stmts();
        }
        return 0;
    }

    int stmt() {
        if (str_check((symbols + pose)->get_type(), EOL_T)) {
            pose++;
            line++;
            return 1;
        }
        if (var()) {
            if (str_check((symbols + pose)->get_type(), EOL_T)) {
                pose++;
                line++;
                return 1;
            }
            printf("Line %d: Got '%s', but need '%s'\n", line, (symbols + pose)->get_type(), EOL_T);
            return 0;
        }
        double d = 0;
        if (exp(&d)) {
            if (str_check((symbols + pose)->get_type(), EOL_T)) {
                pose++;
                line++;
                out(d);
                return 1;
            }
            printf("Line %d: Got '%s', but need '%s'\n", line, (symbols + pose)->get_type(), EOL_T);
            return 0;
        }
        return 1;
    }

    int var() {
        if (!(pose + 1 < symbols_size && str_check((symbols + pose + 1)->get_type(), EQU_T))) {
            return 0;
        }
        if (str_check((symbols + pose)->get_type(), VAR_T)) {
            char *variable = (symbols + pose)->get_char_value();
            pose++;
            if (str_check((symbols + pose)->get_type(), EQU_T)) {
                pose++;
                double d = 0;
                if (exp(&d)) {
                    save_var(variable, vars, &d);
                    return 1;
                }
                return 0;
            } else {
                double d1 = 0;
                if (get_var(variable, vars, &d1)) {
                    out(d1);
                } else {
                    printf("Line %d: Undefined variable: %s\n", line, variable);
                }
            }
            return 1;
        }
        return 0;
    }

    int exp(double *d) {
        double d1 = 0;
        if (term(&d1)) {
            if (str_check((symbols + pose)->get_type(), PLUS_T)) {
                pose++;
                double d2 = 0;
                if (exp(&d2)) {
                    d1 = d1 + d2;
                    memcpy(d, &d1, sizeof(double));
                    return 1;
                }
                return 0;
            }
            if (str_check((symbols + pose)->get_type(), MINUS_T)) {
                pose++;
                double d2 = 0;
                if (exp(&d2)) {
                    d1 = d1 - d2;
                    memcpy(d, &d1, sizeof(double));
                    return 1;
                }
                return 0;
            }
            memcpy(d, &d1, sizeof(double));
            return 1;
        }
        return 0;
    }

    int term(double *d) {
        double d1 = 0;
        if (factor(&d1)) {
            if (str_check((symbols + pose)->get_type(), MULTI_T)) {
                pose++;
                double d2 = 0;
                if (term(&d2)) {
                    d1 = d1 * d2;
                    memcpy(d, &d1, sizeof(double));
                    return 1;
                }
                return 0;
            }
            if (str_check((symbols + pose)->get_type(), DIV_T)) {
                pose++;
                double d2 = 0;
                if (term(&d2)) {
                    if (d2 == 0) {
                        printf("Line %d: Divide on 0!!!\n", line);
                        return 1;
                    }
                    d1 = d1 / d2;
                    memcpy(d, &d1, sizeof(double));
                    return 1;
                }
                return 0;
            }
            memcpy(d, &d1, sizeof(double));
            return 1;
        }
        return 0;
    }

    int factor(double *d) {
        double d1 = 0;
        if (parents(&d1)) {
            memcpy(d, &d1, sizeof(double));
            return 1;
        }
        if (id(&d1)) {
            memcpy(d, &d1, sizeof(double));
            return 1;
        }
        return 0;
    }

    int parents(double *d) {
        if (str_check((symbols + pose)->get_type(), P_O_T)) {
            pose++;
            double d1 = 0;
            if (exp(&d1)) {
                if (str_check((symbols + pose)->get_type(), P_C_T)) {
                    pose++;
                    memcpy(d, &d1, sizeof(double));
                    return 1;
                }
            }
        }
        return 0;
    }

    int id(double *d) {
        if (str_check((symbols + pose)->get_type(), NUM_T)) {
            Symbol *symbol = (symbols + pose);
            double d1 = symbol->get_num_value();
            memcpy(d, &d1, sizeof(double));
            pose++;
            return 1;
        }
        if (str_check((symbols + pose)->get_type(), VAR_T)) {
            char *variable = (symbols + pose)->get_char_value();
            double d1 = 0;
            if (get_var(variable, vars, &d1)) {
                memcpy(d, &d1, sizeof(double));
            } else {
                printf("Line %d: Undefined variable: %s\n", line, variable);
            }
            pose++;
            return 1;
        }
        printf("Line %d: Got '%s', but need '%s' or '%s'\n", line, (symbols + pose)->get_type(), NUM_T, VAR_T);
        return 0;
    }

public:
    Parser(Symbol *symbols, size_t symbols_size) : symbols_size(symbols_size) {
        Parser::symbols = (Symbol *) malloc((symbols_size + 1) * sizeof(Symbol));
        memset(Parser::symbols, 0, (symbols_size + 1) * sizeof(Symbol));
        memcpy(Parser::symbols, symbols, (symbols_size + 1) * sizeof(Symbol));
        vars = new Var(nullptr);
    }

    void start() {
        stmts();
    }
};
