#include "symbol.cpp"

struct Lexer {
private:
    char *input;
    char *tmp;
    int pose = 0;
    int tmp_pose;
    size_t input_size;
    size_t tmp_size;
    std::regex *regex = nullptr;
    std::smatch *match = nullptr;

public:
    explicit Lexer(const char *user_input) {
        char *main_input = remove_space(user_input);
        Lexer::input_size = strlen(main_input);
        Lexer::input = static_cast<char *>(malloc(input_size * sizeof(char)));
        memcpy(Lexer::input, main_input, input_size * sizeof(char));
        clear();
    }

    void clear() {
        tmp_size = input_size - pose;
        tmp = static_cast<char *>(malloc(tmp_size * sizeof(char)));
        memset(tmp, 0, tmp_size * sizeof(char));
        tmp_pose = 0;
    }

    void next() {
        char c = *(input + pose++);
        *(tmp + tmp_pose++) = c;
        *(tmp + tmp_pose) = 0;
    }

    void back() {
        pose--;
        *(tmp + --tmp_pose) = 0;
    }

    bool check() {
        std::string expressions[10] = {VAR, NUM, PLUS, MINUS, MULTI, DIV, P_O, P_C, EQU, EOL};
        for (const auto &expression : expressions) {
            regex = new std::regex(expression);
            match = new std::smatch;
            std::string str(tmp);
            std::regex_search(str, *match, *regex);
            if (match->size() == 1) {
                if (match[0].str() == str) {
                    return true;
                }
            }
        }
        return false;
    }

    bool get_symbol(Symbol *symbol) {
        std::string expressions[10] = {VAR, NUM, PLUS, MINUS, MULTI, DIV, P_O, P_C, EQU, EOL};
        std::string tokens[10] = {VAR_T, NUM_T, PLUS_T, MINUS_T, MULTI_T, DIV_T, P_O_T, P_C_T, EQU_T, EOL_T};
        int i = 0;
        for (const auto &expression : expressions) {
            regex = new std::regex(expression);
            match = new std::smatch;
            std::string str(tmp);
            std::regex_search(str, *match, *regex);
            if (match->size() == 1) {
                if (match[0].str() == str) {
                    symbol->set_type(tokens[i].c_str());
                    if (tokens[i] == NUM_T) {
                        double d = atof(tmp);
                        symbol->set_double_value(&d);
                    } else if (tokens[i] == VAR_T) {
                        symbol->set_char_value(tmp);
                    } else {
                        symbol->set_value(tmp);
                    }
                    return true;
                }
            }
            i++;
        }
        return false;
    }

    bool has_next() {
        return pose < input_size;
    }
};

