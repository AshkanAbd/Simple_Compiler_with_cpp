#include "var.cpp"

struct AST {
private:
    void *left = nullptr;
    int left_flag = 0;
    void *right = nullptr;
    int right_flag = 0;
    int condition = -1;
public:
    AST() = default;

    AST(void *left, size_t left_size, int condition) : condition(condition) {
        AST::left = malloc(left_size);
        memcpy(AST::left, left, left_size);
        left_flag = 1;
    }

    AST(void *left, size_t left_size, int condition, void *right, size_t right_size) : condition(condition) {
        AST::left = malloc(left_size);
        memcpy(AST::left, left, left_size);
        left_flag = 1;
        AST::right = malloc(right_size);
        memcpy(AST::right, right, right_size);
        right_flag = 1;
    }

    void set_left(void *left, size_t left_size) {
        AST::left = malloc(left_size);
        memcpy(AST::left, left, left_size);
        left_flag = 1;
    }

    void set_right(void *right, size_t right_size) {
        AST::right = malloc(right_size);
        memcpy(AST::right, right, right_size);
        right_flag = 1;
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
};
