#include "tokens.h"

struct Symbol {
private:
    char *type;
    void *value;
public:
    explicit Symbol(const char *type, const void *value) {
        size_t type_size = strlen(type) * sizeof(char);
        Symbol::type = static_cast<char *>(malloc(type_size));
        memcpy(Symbol::type, type, type_size);
        Symbol::value = malloc(sizeof(value));
        memcpy(Symbol::value, value, sizeof(value));
    }

    Symbol() {
        type = nullptr;
        value = nullptr;
    }

    void set_type(const char *type) {
        size_t type_size = strlen(type) * sizeof(char);
        Symbol::type = static_cast<char *>(malloc(type_size * sizeof(char)));
        memcpy(Symbol::type, type, type_size * sizeof(char));
        *(Symbol::type + type_size) = 0;
    }

    void set_value(const void *value) {
        Symbol::value = malloc(sizeof(value));
        memcpy(Symbol::value, value, sizeof(value));
    }

    void set_double_value(const void *value) {
        Symbol::value = malloc(sizeof(double));
        memcpy(Symbol::value, value, sizeof(double));
    }

    void set_char_value(const char *value) {
        size_t size = strlen(value);
        Symbol::value = malloc(size * sizeof(char));
        memset(Symbol::value, 0, (size + 1) * sizeof(char));
        memcpy(Symbol::value, value, size * sizeof(char));
    }

    char *get_type() {
        return type;
    }

    double get_num_value() {
        return *((double *) value);
    }

    char *get_char_value() {
        return (char *) value;
    }

    void *get_value() {
        return value;
    }
};

bool str_check(const char *c1, const char *c2);

char *remove_space(const char *input);
