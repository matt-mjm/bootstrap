%{
#include <cstdint>
#include <string>

#include "Node.hpp"
#include "lexer.hpp"

void yyerror(const char *);
%}

%union {
    Ast::IdentifierLiteral *identifier;
    Ast::IntegerLiteral *integer;

    Ast::Node *node;
    Ast::Statement *statement;
    Ast::Expression *expression;
    Ast::Literal *literal;
}

%start prog
%token FUN RETURN
%token NUMBER IDENTIFIER
%token PLUS MINUS STAR SLASH
%token LPAREN RPAREN LBRACE RBRACE

%type <identifier> IDENTIFIER
%type <integer> NUMBER
%type <expression> expr0 expr1 expr2
%type <statement> statement block return_statement
%type <statement> global_statement function_declaration

%%

prog
  : global_statement { auto temp = new Ast::ProgramNode(); temp->statements.push_back($1); yylval.node = temp; }
  ;

global_statement
  : function_declaration { $$ = $1; }
  ;

function_declaration
  : FUN IDENTIFIER LPAREN RPAREN statement { $$ = new Ast::FunctionDeclaration($2, $5); }
  ;

statement
  : block { $$ = $1; }
  | return_statement { $$ = $1; }
  ;

block
  : LBRACE statement RBRACE { auto temp = new Ast::BlockStatement(); temp->statements.push_back($2); $$ = temp; }
  ;

return_statement
  : RETURN expr0 { $$ = new Ast::ReturnStatement($2); }
  ;

expr0
  : expr1 PLUS expr0 { $$ = new Ast::BinaryExpression(Ast::Operation::ADD, $1, $3); }
  | expr1 MINUS expr0 { $$ = new Ast::BinaryExpression(Ast::Operation::SUBTRACT, $1, $3); }
  | expr1 { $$ = $1; }
  ;

expr1
  : expr2 STAR expr1 { $$ = new Ast::BinaryExpression(Ast::Operation::MULTIPLY, $1, $3); }
  | expr2 SLASH expr1 { $$ = new Ast::BinaryExpression(Ast::Operation::DIVIDE, $1, $3); }
  | expr2 { $$ = $1; }
  ;

expr2
  : MINUS expr2 { $$ = new Ast::UnaryExpression(Ast::Operation::SUBTRACT, $2); }
  | LPAREN expr0 RPAREN { $$ = $2; }
  | IDENTIFIER { $$ = $1; }
  | NUMBER { $$ = $1; }
  ;

%%
