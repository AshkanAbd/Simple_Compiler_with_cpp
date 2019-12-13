#include "read_ast.cpp"

int main() {
    Symbol *symbols = (Symbol *) malloc(1000 * sizeof(Symbol));
    memset(symbols, 0, 1000 * sizeof(Symbol));
    int symbols_size = 0;
    std::ifstream input_file(R"(D:\Developer\Cpp\Compiler\test.txt)");
    std::string input;
    while (std::getline(input_file, input)) {
        Lexer *lexer = new Lexer(input.c_str());
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
    Parser *parser = new Parser(symbols, symbols_size, ast);
    parser->start();
    ReadAST *readAst = new ReadAST;
    readAst->read(ast);
}
