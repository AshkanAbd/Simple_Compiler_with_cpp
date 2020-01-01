#include "ast.cpp"

bool str_check(const char *c1, const char *c2) {
    if (c1 == nullptr || c2 == nullptr) {
        return false;
    }
    try {
        return !strcmp(c1, c2);
    } catch (std::exception exception) {
        return false;
    }
}

void remove_space(char *input) {
    const char *str = input;
    do {
        while (*str == ' ') {
            ++str;
        }
    } while (*input++ = *str++);
}

int get_var(char *variable, Var *vars, double *res) {
    VarName *varName = vars->get_var(variable);
    if (varName != nullptr) {
        memcpy(res, varName->get_value(), sizeof(double));
        return 1;
    }
    return 0;
}

int save_var(char *variable, Var *vars, double *value) {
    VarName *varName = vars->get_var(variable);
    if (varName != nullptr) {
        varName->set_value(value);
    } else {
        varName = new VarName(variable, value);
        vars->add(varName);
    }
    return 1;
}

size_t ast_size = 0;

void add_ast_size(size_t size) {
    ast_size += size;
}

size_t get_ast_size() {
    return ast_size;
}

void infix_to_postfix(Symbol *symbol, int symbol_pose, int size, int line) {
    printf("Postfix line %d: ", line);
    char *stack = (char *) malloc(size * sizeof(char));
    memset(stack, 0, size * sizeof(char));
    int stack_pose = 0;
    while (true) {
        Symbol *s = (symbol + symbol_pose);
        if (str_check((symbol + symbol_pose++)->get_type(), EOL_T)) {
            break;
        }
        if (str_check(s->get_type(), NUM_T)) {
            double d = s->get_num_value();
            printf("<%.6g>", d);
        } else if (str_check(s->get_type(), VAR_T)) {
            printf("<%s>", s->get_char_value());
        } else if (str_check(s->get_type(), PI_T)) {
            printf("<PI>");
        } else if (str_check(s->get_type(), NEPER_T)) {
            printf("<E>");
        } else if (str_check(s->get_type(), PLUS_T) || str_check(s->get_type(), MINUS_T)) {
            while (*(stack + stack_pose - 1) == '+' || *(stack + stack_pose - 1) == '-' ||
                   *(stack + stack_pose - 1) == '^' || *(stack + stack_pose - 1) == '*' ||
                   *(stack + stack_pose - 1) == '/' || *(stack + stack_pose - 1) == 'm' ||
                   *(stack + stack_pose - 1) == 'd') {
                stack_pose--;
                printf("%c", *(stack + stack_pose));
                *(stack + stack_pose) = 0;
            }
            *(stack + stack_pose++) = *s->get_type();
        } else if (str_check(s->get_type(), MULTI_T) || str_check(s->get_type(), DIV_T)
                   || str_check(s->get_type(), DIV_I_T) || str_check(s->get_type(), MOD_T)) {
            while (*(stack + stack_pose - 1) == '^' || *(stack + stack_pose - 1) == '*' ||
                   *(stack + stack_pose - 1) == '/' || *(stack + stack_pose - 1) == 'm' ||
                   *(stack + stack_pose - 1) == 'd') {
                stack_pose--;
                printf("%c", *(stack + stack_pose));
                *(stack + stack_pose) = 0;
            }
            *(stack + stack_pose++) = *s->get_type();
        } else if (str_check(s->get_type(), POW_T)) {
            *(stack + stack_pose++) = *s->get_type();
        } else if (str_check(s->get_type(), P_O_T)) {
            *(stack + stack_pose++) = '(';
        } else if (str_check(s->get_type(), SIN_T)) {
            *(stack + stack_pose++) = 's';
        } else if (str_check(s->get_type(), COS_T)) {
            *(stack + stack_pose++) = 'c';
        } else if (str_check(s->get_type(), TAN_T)) {
            *(stack + stack_pose++) = 't';
        } else if (str_check(s->get_type(), COT_T)) {
            *(stack + stack_pose++) = 'o';
        } else if (str_check(s->get_type(), LOG_T)) {
            *(stack + stack_pose++) = 'l';
        } else if (str_check(s->get_type(), EXP_T)) {
            *(stack + stack_pose++) = 'e';
        } else if (str_check(s->get_type(), SQR_T)) {
            *(stack + stack_pose++) = 'q';
        } else if (str_check(s->get_type(), SQRT_T)) {
            *(stack + stack_pose++) = 'r';
        } else if (str_check(s->get_type(), P_C_T)) {
            stack_pose--;
            while (*(stack + stack_pose) != '(' && *(stack + stack_pose) != 's' && *(stack + stack_pose) != 'c'
                   && *(stack + stack_pose) != 'l' && *(stack + stack_pose) != 'o' && *(stack + stack_pose) != 't'
                   && *(stack + stack_pose) != 'e' && *(stack + stack_pose) != 'q' && *(stack + stack_pose) != 'r'
                    ) {
                char c = *(stack + stack_pose);
                if (c == 's') {
                    printf("sin");
                }
                if (c == 'c') {
                    printf("cos");
                }
                if (c == 't') {
                    printf("tan");
                }
                if (c == 'o') {
                    printf("cot");
                }
                if (c == 'l') {
                    printf("log");
                }
                if (c == 'e') {
                    printf("exp");
                }
                if (c == 'r') {
                    printf("sqrt");
                }
                if (c == 'q') {
                    printf("sqr");
                } else {
                    printf("%c", *(stack + stack_pose));
                }
                *(stack + stack_pose--) = 0;
            }
            *(stack + stack_pose) = 0;
            if (*(stack + stack_pose - 1) == 's' || *(stack + stack_pose - 1) == 'c' &&
                                                    *(stack + stack_pose - 1) == 'l' ||
                *(stack + stack_pose - 1) == 'o' &&
                *(stack + stack_pose - 1) == 't' || *(stack + stack_pose - 1) == 'e' &&
                                                    *(stack + stack_pose - 1) == 'q' ||
                *(stack + stack_pose - 1) == 'r') {
                char c = *(stack + stack_pose - 1);
                if (c == 's') {
                    printf("sin");
                }
                if (c == 'c') {
                    printf("cos");
                }
                if (c == 't') {
                    printf("tan");
                }
                if (c == 'o') {
                    printf("cot");
                }
                if (c == 'l') {
                    printf("log");
                }
                if (c == 'e') {
                    printf("exp");
                }
                if (c == 'r') {
                    printf("sqrt");
                }
                if (c == 'q') {
                    printf("sqr");
                }
                *(stack + stack_pose - 1) = 0;
                stack_pose--;
            }
        }
    }
    stack_pose--;
    while (stack_pose != -1) {
        printf("%c", *(stack + stack_pose--));
    }
    printf("\n");
}

bool num_exp(const char *chars) {
    size_t char_size = strlen(chars);
    bool dot = false;
    bool e = false;
    for (size_t i = 0; i < char_size; ++i) {
        char c = *(chars + i);
        if (c >= '0' && c <= '9') {
            continue;
        }
        if (!dot && !e && c == '.' && i != 0) {
            dot = true;
            continue;
        }
        if (!e && c == 'e' && *(chars + char_size) != '.' && i != 0) {
            e = true;
            continue;
        }
        return false;
    }
    return true;
};

bool plus_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != '+') {
        return false;
    }
    return true;
};

bool minus_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != '-') {
        return false;
    }
    return true;
};

bool multi_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != '*') {
        return false;
    }
    return true;
};

bool div_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != '/') {
        return false;
    }
    return true;
};

bool div_i_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 'd' || *(chars) == 'D')) {
        return false;
    }
    if (!(*(chars + 1) == 'i' || *(chars + 1) == 'I')) {
        return false;
    }
    if (!(*(chars + 2) == 'v' || *(chars + 2) == 'V')) {
        return false;
    }
    return true;
};

bool mod_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 'm' || *(chars) == 'M')) {
        return false;
    }
    if (!(*(chars + 1) == 'o' || *(chars + 1) == 'O')) {
        return false;
    }
    if (!(*(chars + 2) == 'd' || *(chars + 2) == 'D')) {
        return false;
    }
    return true;
};

bool pow_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != '^') {
        return false;
    }
    return true;
};

bool pi_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 2) {
        return false;
    }
    if (!(*(chars) == 'p' || *(chars) == 'P')) {
        return false;
    }
    if (!(*(chars + 1) == 'i' || *(chars + 1) == 'I')) {
        return false;
    }
    return true;
};

bool neper_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1) {
        return false;
    }
    if (!(*(chars) == 'e' || *(chars) == 'E')) {
        return false;
    }
    return true;
};

bool sin_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 's' || *(chars) == 'S')) {
        return false;
    }
    if (!(*(chars + 1) == 'i' || *(chars + 1) == 'I')) {
        return false;
    }
    if (!(*(chars + 2) == 'n' || *(chars + 2) == 'N')) {
        return false;
    }
    return true;
};

bool cos_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 'c' || *(chars) == 'C')) {
        return false;
    }
    if (!(*(chars + 1) == 'o' || *(chars + 1) == 'O')) {
        return false;
    }
    if (!(*(chars + 2) == 's' || *(chars + 2) == 'S')) {
        return false;
    }
    return true;
};

bool tan_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 't' || *(chars) == 'T')) {
        return false;
    }
    if (!(*(chars + 1) == 'a' || *(chars + 1) == 'A')) {
        return false;
    }
    if (!(*(chars + 2) == 'n' || *(chars + 2) == 'N')) {
        return false;
    }
    return true;
};

bool cot_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 'c' || *(chars) == 'C')) {
        return false;
    }
    if (!(*(chars + 1) == 'o' || *(chars + 1) == 'O')) {
        return false;
    }
    if (!(*(chars + 2) == 't' || *(chars + 2) == 'T')) {
        return false;
    }
    return true;
};

bool log_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 'l' || *(chars) == 'L')) {
        return false;
    }
    if (!(*(chars + 1) == 'o' || *(chars + 1) == 'O')) {
        return false;
    }
    if (!(*(chars + 2) == 'g' || *(chars + 2) == 'G')) {
        return false;
    }
    return true;
};

bool exp_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 'e' || *(chars) == 'E')) {
        return false;
    }
    if (!(*(chars + 1) == 'x' || *(chars + 1) == 'X')) {
        return false;
    }
    if (!(*(chars + 2) == 'p' || *(chars + 2) == 'P')) {
        return false;
    }
    return true;
};

bool sqr_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 3) {
        return false;
    }
    if (!(*(chars) == 's' || *(chars) == 'S')) {
        return false;
    }
    if (!(*(chars + 1) == 'q' || *(chars + 1) == 'Q')) {
        return false;
    }
    if (!(*(chars + 2) == 'r' || *(chars + 2) == 'R')) {
        return false;
    }
    return true;
};

bool sqrt_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 4) {
        return false;
    }
    if (!(*(chars) == 's' || *(chars) == 'S')) {
        return false;
    }
    if (!(*(chars + 1) == 'q' || *(chars + 1) == 'Q')) {
        return false;
    }
    if (!(*(chars + 2) == 'r' || *(chars + 2) == 'R')) {
        return false;
    }
    if (!(*(chars + 3) == 't' || *(chars + 3) == 'T')) {
        return false;
    }
    return true;
};

bool p_o_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != '(') {
        return false;
    }
    return true;
};

bool p_c_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != ')') {
        return false;
    }
    return true;
};

bool equ_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != '=') {
        return false;
    }
    return true;
};

bool var_exp(const char *chars) {
    size_t char_size = strlen(chars);
    for (size_t i = 0; i < char_size; ++i) {
        char c = *(chars + i);
        if (i == 0) {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) {
                continue;
            } else {
                return false;
            }
        } else {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
                || (c >= '0' && c <= '9') || (c == '_')) {
                continue;
            } else {
                return false;
            }
        }
    }
    return true;
};

bool eol_exp(const char *chars) {
    size_t char_size = strlen(chars);
    if (char_size != 1 || (*chars) != ';') {
        return false;
    }
    return true;
};
