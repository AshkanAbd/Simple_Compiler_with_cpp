#include "parser.cpp"

struct ReadAST {
private:
    Var *vars = nullptr;

    static void out(double d) {
        printf(">>> %.6g\n", d);
    }

public:
    ReadAST() {
        ReadAST::vars = new Var(nullptr);
    }

    int read(AST *ast, int line = 1) {
        if (ast->get_condition() == EOL_FLAG) {
            if (read((AST *) ast->get_left(), line)) {
                if (ast->get_right() != nullptr) {
                    read((AST *) ast->get_right(), line + 1);
                }
            }
        }
        if (ast->get_condition() == PRINT_FLAG) {
            double d = 0;
            if (read_exp((AST *) ast->get_left(), &d, line)) {
                out(d);
                return 1;
            }
            return 0;
        }
        if (ast->get_condition() == EQU_FLAG) {
            double d = 0;
            if (read_exp((AST *) ast->get_right(), &d, line)) {
                auto symbol = (Symbol *) ast->get_left();
                char *variable = symbol->get_char_value();
                save_var(variable, vars, &d);
                return 1;
            }
            return 0;
        }
        return 0;
    }

    int read_exp(AST *ast, double *d, int line) {
        if (ast->get_left_type() == AST_TYPE) {
            double d1 = 0;
            if (read_exp((AST *) ast->get_left(), &d1, line)) {
                double d2 = 0;
                if (read_exp((AST *) ast->get_right(), &d2, line)) {
                    if (ast->get_condition() == PLUS_FLAG) {
                        d1 = d1 + d2;
                    }
                    if (ast->get_condition() == MINUS_FLAG) {
                        d1 = d1 - d2;
                    }
                    if (ast->get_condition() == MULTI_FLAG) {
                        d1 = d1 * d2;
                    }
                    if (ast->get_condition() == DIV_FLAG) {
                        if (d2 == 0) {
                            printf("Runtime error on line %d: Divide on 0", line);
                            return 0;
                        }
                        d1 = d1 / d2;
                    }
                    memcpy(d, &d1, sizeof(double));
                    return 1;
                }
            }
        } else {
            auto *symbol = (Symbol *) ast->get_left();
            double d1 = 0;
            if (str_check(symbol->get_type(), NUM_T)) {
                d1 = symbol->get_num_value();
                memcpy(d, &d1, sizeof(double));
                return 1;
            }
            if (str_check(symbol->get_type(), VAR_T)) {
                char *variable = symbol->get_char_value();
                if (get_var(variable, vars, d)) {
                    return 1;
                } else {
                    printf("Runtime error on line %d: Undefined variable '%s'", line, variable);
                    return 0;
                }
            }
        }
    }
};
