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
                    return read((AST *) ast->get_right(), line + 1);
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
        return 1;
    }

    int read_exp(AST *ast, double *d, int line) {
        if (ast->get_left_type() == AST_TYPE) {
            double d1 = 0;
            if (read_exp((AST *) ast->get_left(), &d1, line)) {
                if (ast->get_right_flag()) {
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
                                printf("Runtime error on line %d: Divide on 0.\n", line);
                                return 0;
                            }
                            d1 = d1 / d2;
                        }
                        if (ast->get_condition() == DIV_I_FLAG) {
                            if (d2 == 0) {
                                printf("Runtime error on line %d: Divide on 0.\n", line);
                                return 0;
                            }
                            if (d2 != floor(d2) || d1 != floor(d1)) {
                                printf("Runtime error on line %d: Integer division on float number.\n", line);
                                return 0;
                            }
                            d1 = floor(d1 / d2);
                        }
                        if (ast->get_condition() == MOD_FLAG) {
                            if (d2 != floor(d2) || d1 != floor(d1)) {
                                printf("Runtime error on line %d: Reminder on float number.\n", line);
                                return 0;
                            }
                            d1 = (int) d1 % (int) d2;
                        }
                        if (ast->get_condition() == POW_FLAG) {
                            d1 = pow(d1, d2);
                        }
                        memcpy(d, &d1, sizeof(double));
                        return 1;
                    }
                } else {
                    if (ast->get_condition() == UNARY_MINUS_FLAG) {
                        d1 = -1 * d1;
                    }
                    if (ast->get_condition() == SIN_FLAG) {
                        d1 = sin(d1 * M_PI / 180.0);
                    }
                    if (ast->get_condition() == COS_FLAG) {
                        d1 = cos(d1 * M_PI / 180.0);
                    }
                    if (ast->get_condition() == TAN_FLAG) {
                        d1 = tan(d1 * M_PI / 180.0);
                    }
                    if (ast->get_condition() == COT_FLAG) {
                        d1 = cos(d1 * M_PI / 180.0) / sin(d1 * M_PI / 180.0);
                    }
                    if (ast->get_condition() == LOG_FLAG) {
                        d1 = std::log(d1);
                    }
                    if (ast->get_condition() == EXP_FLAG) {
                        d1 = pow(M_E, d1);
                    }
                    if (ast->get_condition() == SQR_FLAG) {
                        d1 = pow(d1, 2);
                    }
                    if (ast->get_condition() == SQRT_FLAG) {
                        d1 = sqrt(d1);
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
            if (str_check(symbol->get_type(), PI_T)) {
                d1 = M_PI;
                memcpy(d, &d1, sizeof(double));
                return 1;
            }
            if (str_check(symbol->get_type(), NEPER_T)) {
                d1 = M_E;
                memcpy(d, &d1, sizeof(double));
                return 1;
            }
            if (str_check(symbol->get_type(), VAR_T)) {
                char *variable = symbol->get_char_value();
                if (get_var(variable, vars, d)) {
                    return 1;
                } else {
                    int undefined_var = undefined_vars;
                    if (undefined_var) {
                        printf("\nRuntime error on line %d: Undefined variable '%s'.\n", line, variable);
                        return 0;
                    }
                    if (!undefined_var) {
                        printf("Enter value for variable %s:\n", variable);
                        scanf("%lf", &d1);
                        save_var(variable, vars, &d1);
                        memcpy(d, &d1, sizeof(double));
                        return 1;
                    }
                }
            }
        }
    }
};
