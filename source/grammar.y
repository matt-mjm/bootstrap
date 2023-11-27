%{
#include <stdint.h>
#include "Node.hpp"
#include "lexer.hpp"

void yyerror(const char *);
%}

%union {
    int32_t i32;
    Ast::Node *node;
}

%start prog
%token NUMBER
%token PLUS MINUS STAR SLASH
%token LPAREN RPAREN

%type <node> expr0 expr1 expr2
%type <i32> NUMBER

%%

prog
  : expr0 { yylval.node = $1; }
  ;

expr0
  : expr0 PLUS expr0 { $$ = new Ast::BinaryNode(Ast::Operation::ADD, $1, $3); }
  | expr0 MINUS expr0 { $$ = new Ast::BinaryNode(Ast::Operation::SUBTRACT, $1, $3); }
  | expr1 { $$ = $1; }
  ;

expr1
  : expr1 STAR expr1 { $$ = new Ast::BinaryNode(Ast::Operation::MULTIPLY, $1, $3); }
  | expr1 SLASH expr1 { $$ = new Ast::BinaryNode(Ast::Operation::DIVIDE, $1, $3); }
  | expr2 { $$ = $1; }
  ;

expr2
  : MINUS expr2 { $$ = new Ast::UnaryNode(Ast::Operation::SUBTRACT, $2); }
  | LPAREN expr0 RPAREN { $$ = $2; }
  | NUMBER { $$ = new Ast::IntegerNode($1); }
  ;

%%
