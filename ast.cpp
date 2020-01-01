#include "var.cpp"

struct AST {
public:
    void *left = nullptr;
    int left_flag = 0;
    int left_type = 0;
    void *right = nullptr;
    int right_flag = 0;
    int right_type = 0;
    int condition = -1;

public:
    AST() = default;

    void set_left(void *left, size_t left_size, int left_type) {
        AST::left = malloc(left_size);
        memcpy(AST::left, left, left_size);
        left_flag = 1;
        AST::left_type = left_type;
        add_ast_size(left_size);
    }

    void set_right(void *right, size_t right_size, int right_type) {
        AST::right = malloc(right_size);
        memcpy(AST::right, right, right_size);
        right_flag = 1;
        AST::right_type = right_type;
        add_ast_size(right_size);
    }

    void set_condition(int condition) {
        AST::condition = condition;
    }

    int get_condition() {
        return AST::condition;
    }

    int get_left_flag() {
        return AST::left_flag;
    }

    int get_right_flag() {
        return AST::right_flag;
    }

    void *get_left() {
        return AST::left;
    }

    void *get_right() {
        return AST::right;
    }

    int get_left_type() {
        return AST::left_type;
    }

    int get_right_type() {
        return AST::right_type;
    }
};
