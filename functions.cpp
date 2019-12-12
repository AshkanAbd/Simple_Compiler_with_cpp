#include "var.cpp"

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

char *remove_space(const char *input) {
    char *chars = (char *) malloc(strlen(input) * sizeof(char));
    memset(chars, 0, strlen(input) * sizeof(char));
    int i = 0, j = 0;
    for (; i < strlen(input); i++) {
        if (*(input + i) == ' ') continue;
        char c = *(input + i);
        *(chars + j++) = c;
        *(chars + j) = 0;
    }
    return chars;
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
