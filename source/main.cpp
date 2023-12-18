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
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <infile> [outfile]" << std::endl;
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

    Node *root = yylval.node;

    Printer printer;
    root->accept(printer);

    if (argc >= 3) {
        std::error_code ec;
        llvm::raw_fd_ostream outs(argv[2], ec);
        CodeGenerator codeGenerator{outs};
        root->accept(codeGenerator);
    } else {
        CodeGenerator codeGenerator{llvm::outs()};
        root->accept(codeGenerator);
    }

    delete root;

  return 0;
}
