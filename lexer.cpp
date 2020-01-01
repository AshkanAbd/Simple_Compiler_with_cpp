#include "symbol.cpp"

bool num_exp(const char *chars);

bool plus_exp(const char *chars);

bool minus_exp(const char *chars);

bool multi_exp(const char *chars);

bool div_exp(const char *chars);

bool div_i_exp(const char *chars);

bool mod_exp(const char *chars);

bool pow_exp(const char *chars);

bool pi_exp(const char *chars);

bool neper_exp(const char *chars);

bool sin_exp(const char *chars);

bool cos_exp(const char *chars);

bool tan_exp(const char *chars);

bool cot_exp(const char *chars);

bool log_exp(const char *chars);

bool exp_exp(const char *chars);

bool sqr_exp(const char *chars);

bool sqrt_exp(const char *chars);

bool p_o_exp(const char *chars);

bool p_c_exp(const char *chars);

bool equ_exp(const char *chars);

bool var_exp(const char *chars);

bool eol_exp(const char *chars);

struct Lexer {
private:
public:
    char *input;
    char *tmp;
    int line = 1;
    int pose = 0;
    int tmp_pose;
    size_t input_size;
    size_t tmp_size;
    std::regex *regex = nullptr;
    std::smatch *match = nullptr;

public:
    explicit Lexer(char *input) {
        Lexer::input_size = strlen(input);
        Lexer::input = (char *) (malloc(input_size * sizeof(char)));
        memcpy(Lexer::input, input, input_size * sizeof(char));
        clear();
    }

    void clear() {
        tmp_size = input_size - pose;
        tmp = (char *) (malloc(tmp_size * sizeof(char)));
        memset(tmp, 0, tmp_size * sizeof(char));
        tmp_pose = 0;
    }

    int next() {
        char c = *(input + pose++);
        *(tmp + tmp_pose++) = c;
        *(tmp + tmp_pose) = 0;
        return c != 0;
    }

    void back() {
        pose--;
        *(tmp + --tmp_pose) = 0;
    }

    bool check() {
        if (*tmp == ' ') {
            clear();
            return true;
        }
        if (num_exp(tmp)) {
            return true;
        }
        if (plus_exp(tmp)) {
            return true;
        }
        if (minus_exp(tmp)) {
            return true;
        }
        if (multi_exp(tmp)) {
            return true;
        }
        if (div_exp(tmp)) {
            return true;
        }
        if (div_i_exp(tmp)) {
            return true;
        }
        if (mod_exp(tmp)) {
            return true;
        }
        if (pow_exp(tmp)) {
            return true;
        }
        if (pi_exp(tmp)) {
            return true;
        }
        if (neper_exp(tmp)) {
            return true;
        }
        if (sin_exp(tmp)) {
            return true;
        }
        if (cos_exp(tmp)) {
            return true;
        }
        if (tan_exp(tmp)) {
            return true;
        }
        if (cot_exp(tmp)) {
            return true;
        }
        if (log_exp(tmp)) {
            return true;
        }
        if (exp_exp(tmp)) {
            return true;
        }
        if (sqr_exp(tmp)) {
            return true;
        }
        if (sqrt_exp(tmp)) {
            return true;
        }
        if (p_o_exp(tmp)) {
            return true;
        }
        if (p_c_exp(tmp)) {
            return true;
        }
        if (equ_exp(tmp)) {
            return true;
        }
        if (var_exp(tmp)) {
            return true;
        }
        if (eol_exp(tmp)) {
            return true;
        }
        return false;
    }

    bool get_symbol(Symbol *symbol) {
        std::string tokens[23] = {NUM_T, PLUS_T, MINUS_T, MULTI_T, DIV_T, DIV_I_T, MOD_T, POW_T, PI_T, NEPER_T,
                                  SIN_T, COS_T, TAN_T, COT_T, LOG_T, EXP_T, SQR_T, SQRT_T, P_O_T, P_C_T, EQU_T, VAR_T,
                                  EOL_T};
        if (strlen(tmp) == 0) {
            printf("Compile error in line %d: Bad input '%c'.\n", line, *(input + pose));
            return false;
        }
        int i = 0;
        if (num_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            double d = atof(tmp);
            symbol->set_double_value(&d);
            return true;
        }
        i++;
        if (plus_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (minus_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (multi_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (div_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (div_i_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (mod_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (pow_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (pi_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (neper_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (sin_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (cos_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (tan_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (cot_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (log_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (exp_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (sqr_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (sqrt_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (p_o_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (p_c_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (equ_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            return true;
        }
        i++;
        if (var_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_char_value(tmp);
            return true;
        }
        i++;
        if (eol_exp(tmp)) {
            symbol->set_type(tokens[i].c_str());
            symbol->set_value(tmp);
            line++;
            return true;
        }
        return false;
    }

    bool has_next() {
        return pose < input_size;
    }

    char *get_temp() {
        return tmp;
    }
};

