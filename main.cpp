#include "read_ast.cpp"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: ./Compiler [source] [output]\n");
    } else {
        size_t symbols_max = 1000;
        auto *symbols = (Symbol *) malloc(symbols_max * sizeof(Symbol));
        memset(symbols, 0, symbols_max * sizeof(Symbol));
        int symbols_size = 0;
        std::ifstream input_file(*(argv + 1));
        std::cout << "Compiling...\n";
        std::string line;
        char *input = nullptr;
        size_t input_size = 0;
        memset(input, 0, input_size);
        size_t pre_size = 0;
        size_t init_size = 1000;
        bool is_cmt = false;
        while (std::getline(input_file, line)) {
            if (line.empty()) {
                line = ";";
            }
            size_t line_size = line.length();
            while (true) {
                int cmt = line.find('{');
                int cmt1 = line.find('}');
                int cmt2 = line.find("//");
                if (is_cmt) {
                    if (cmt1 != std::string::npos) {
                        line = line.substr(cmt1 + 1);
                        line_size = line.length();
                        is_cmt = false;
                    } else {
//                    line = ";";
//                    line_size = 1;
                        continue;
                    }
                }
                if (!is_cmt) {
                    if ((cmt < cmt2 && cmt != std::string::npos) ||
                        (cmt != std::string::npos && cmt2 == std::string::npos)) {
                        if (cmt1 != std::string::npos) {
                            line = line.substr(0, cmt) + line.substr(cmt1 + 1);
                            line_size = line.length();
                        } else {
                            is_cmt = true;
                            if (cmt == 0) {
                                line = ";";
                                cmt++;
                            }
                            line_size = cmt;
                        }
                    }
                    if ((cmt2 < cmt && cmt2 != std::string::npos) ||
                        (cmt2 != std::string::npos && cmt == std::string::npos)) {
                        cmt2 = line.find("//");
                        if (cmt2 == 0) {
                            line = ";";
                            cmt2++;
                        }
                        line = line.substr(0, cmt2);
                        line_size = cmt2;
                    }
                }
                if (cmt == std::string::npos && cmt2 == std::string::npos) break;
            }
            pre_size = input_size;
            input_size += line_size;
            if (input == nullptr) {
                input = (char *) malloc(init_size * sizeof(char));
            }
            if (input_size >= init_size) {
                init_size += 1000;
                realloc(input, init_size);
            }
            memcpy(input + pre_size, line.c_str(), line_size * sizeof(char));
        }
        realloc(input, input_size + 1);
        *(input + input_size) = 0;
        input_size = strlen(input);
        realloc(input, input_size + 1);
        *(input + input_size) = 0;
        auto *lexer = new Lexer(input);
        while (lexer->has_next()) {
            lexer->next();
            while (lexer->check()) {
                if (!lexer->next()) break;
            }
            lexer->back();
            Symbol symbol;
            if (!lexer->get_symbol(&symbol)) {
                std::cout << "Compile ends with status code 1.\n";
                return 0;
            }
            *(symbols + symbols_size++) = symbol;
            if (symbols_size >= symbols_max) {
                symbols_max += 1000;
                realloc(symbols, symbols_max * sizeof(Symbol));
            }
            lexer->clear();
        }
        realloc(symbols, symbols_size * sizeof(Symbol));
        AST *ast = new AST;
        auto *parser = new Parser(symbols, symbols_size, ast);
        int res = parser->start();
        if (!res) {
            std::cout << "Compile ends with status code " << !res << ".\n";
            return 0;
        }
        std::cout << "Compiled successfully.\n";
        std::cout << "Running..." << "\n";
        auto *readAst = new ReadAST;
        readAst->read(ast);
    }
}
