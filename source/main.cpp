#include <cstdint>
#include <string>

#include "Node.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include "Visitor.hpp"
#include "Printer.hpp"
#include "CodeGenerator.hpp"

#include <iostream>

void yyerror(const char *msg) {
    std::cout << "Error: " << msg << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <infile> <outfile>" << std::endl;
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    if (source == NULL){
        std::cout << "Error: " << argv[1] << " not found." << std::endl;
        return 1;
    }

    yyin = source;
    int result = yyparse();
    if (result != 0) {
        std::cout << "Error: yyparse returned " << result << std::endl;
        return result;
    }

    yylex_destroy();
    fclose(source);

    std::error_code ec;
    llvm::raw_fd_ostream outfile(argv[2], ec);

    Ast::Printer printer;
    Ast::CodeGenerator codeGenerator{outfile};

    Ast::Node *root = yylval.node;
    printer(*root);
    codeGenerator(*root);
    delete root;

  return 0;
}
