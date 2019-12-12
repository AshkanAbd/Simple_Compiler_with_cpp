#include "lexer.cpp"

struct VarName {
private:
    char *name = nullptr;
    VarName *next = nullptr;
    double *value = nullptr;

public:
    VarName(char *name, double *value) {
        size_t size = strlen(name);
        VarName::name = (char *) malloc(size * sizeof(char));
        memset(VarName::name, 0, (size + 1) * sizeof(char));
        memcpy(VarName::name, name, size * sizeof(char));
        VarName::value = (double *) malloc(sizeof(double));
        memcpy(VarName::value, value, sizeof(double));
    }

    double *get_value() {
        return value;
    }

    void set_value(double *value) {
        VarName::value = (double *) malloc(sizeof(double));
        memcpy(VarName::value, value, sizeof(double));
    }

    char *get_name() {
        return name;
    }

    void set_name(char *name) {
        size_t size = strlen(name);
        VarName::name = (char *) malloc(size * sizeof(char));
        memcpy(VarName::name, name, size * sizeof(char));
    }

    VarName *get_next() {
        return next;
    }

    void set_next(VarName *next) {
        VarName::next = next;
    }
};

struct Var {
private:
    VarName *head = nullptr;
    VarName *end = nullptr;

public:
    explicit Var(VarName *name) : head(name), end(name) {}

    void add(VarName *var) {
        if (head != nullptr) {
            end->set_next(var);
            end = var;
        } else {
            head = var;
            end = var;
        }
    }

    int contains(char *name) {
        VarName *var = head;
        if (var == nullptr)return 0;
        while (true) {
            if (str_check(name, var->get_name())) {
                return 1;
            }
            if (var->get_next() == nullptr) {
                break;
            }
            var = var->get_next();
        }
        return 0;
    }

    VarName *get_var(char *name) {
        VarName *var = head;
        if (var == nullptr)return nullptr;
        while (true) {
            if (str_check(name, var->get_name())) {
                return var;
            }
            if (var->get_next() == nullptr) {
                break;
            }
            var = var->get_next();
        }
        return nullptr;
    }
};

int get_var(char *variable, Var *vars, double *res);

int save_var(char *variable, Var *vars, double *value);
