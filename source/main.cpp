#include "Node.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include "Visitor.hpp"
#include "Printer.hpp"

#include <iostream>

void yyerror(const char *msg) {
  std::cout << "Error: " << msg << std::endl;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
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

  Ast::Printer printer;
  Ast::Node *root = yylval.node;
  printer(*root);
  delete root;

  return 0;
}
