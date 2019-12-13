#include "read_ast.cpp"

int main(int argc, char **argv) {
    if (argc >= 2) {
        auto *symbols = (Symbol *) malloc(1000 * sizeof(Symbol));
        memset(symbols, 0, 1000 * sizeof(Symbol));
        int symbols_size = 0;
        std::ifstream input_file(*(argv + 1));
        std::string input;
        while (std::getline(input_file, input)) {
            auto *lexer = new Lexer(input.c_str());
            while (lexer->has_next()) {
                lexer->next();
                while (lexer->check()) {
                    lexer->next();
                }
                lexer->back();
                Symbol symbol;
                lexer->get_symbol(&symbol);
                *(symbols + symbols_size++) = symbol;
                if (symbols_size >= 1000) {
                    realloc(symbols, 2000 * sizeof(Symbol));
                }
                lexer->clear();
            }
        }
        realloc(symbols, symbols_size * sizeof(Symbol));
        AST *ast = new AST;
        auto *parser = new Parser(symbols, symbols_size, ast);
        parser->start();
        auto *readAst = new ReadAST;
        readAst->read(ast);
    } else {
        while (true) {
            auto *symbols = (Symbol *) malloc(1000 * sizeof(Symbol));
            memset(symbols, 0, 1000 * sizeof(Symbol));
            int symbols_size = 0;
            std::string input;
            while (std::getline(std::cin, input)) {
                auto *lexer = new Lexer(input.c_str());
                while (lexer->has_next()) {
                    lexer->next();
                    while (lexer->check()) {
                        lexer->next();
                    }
                    lexer->back();
                    Symbol symbol;
                    lexer->get_symbol(&symbol);
                    *(symbols + symbols_size++) = symbol;
                    if (symbols_size >= 1000) {
                        realloc(symbols, 2000 * sizeof(Symbol));
                    }
                    lexer->clear();
                }
            }
            realloc(symbols, symbols_size * sizeof(Symbol));
            AST *ast = new AST;
            auto *parser = new Parser(symbols, symbols_size, ast);
            parser->start();
            auto *readAst = new ReadAST;
            readAst->read(ast);
        }
    }
}
