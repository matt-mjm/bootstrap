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

    Ast::BindingList *binding_list;
    Ast::Binding *binding;
    Ast::BlockStatement *block;
}

%start prog
%token COMMA COLON ARROW
%token PLUS MINUS STAR SLASH
%token LPAREN RPAREN LBRACE RBRACE
%token FUN RETURN
%token NUMBER IDENTIFIER

%type <identifier> IDENTIFIER
%type <integer> NUMBER
%type <expression> expr0 expr1 expr2
%type <statement> statement block return_statement
%type <statement> global_statement function_declaration
%type <binding> binding
%type <binding_list> binding_list
%type <expression> arg_type ret_type
%type <block> statement_list

%%

prog
  : global_statement { auto temp = new Ast::ProgramNode(); temp->statements.push_back($1); yylval.node = temp; }
  ;

global_statement
  : function_declaration { $$ = $1; }
  ;

function_declaration
  : FUN IDENTIFIER LPAREN binding_list RPAREN ret_type statement { $$ = new Ast::FunctionDeclaration($2, $4, $6, $7); }
  ;

binding_list
  : binding COMMA binding_list { $$ = $3; $$->bindings.insert($$->bindings.begin(), $1); }
  | binding { $$ = new Ast::BindingList(); $$->bindings.push_back($1); }
  | /* NOTHING */ { $$ = new Ast::BindingList(); }
  ;

binding
  : IDENTIFIER arg_type { $$ = new Ast::Binding($1, $2); }
  ;

arg_type
  : COLON expr0 { $$ = $2; }
  ;

ret_type
  : ARROW expr0 { $$ = $2; }
  ;

statement_list
  : statement statement_list { $$ = $2; $$->statements.insert($$->statements.begin(), $1); }
  | /* NOTHING */ { $$ = new Ast::BlockStatement(); }
  ;

statement
  : block { $$ = $1; }
  | return_statement { $$ = $1; }
  ;

block
  : LBRACE statement_list RBRACE { $$ = $2; }
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
  | STAR expr2 { $$ = new Ast::UnaryExpression(Ast::Operation::MULTIPLY, $2); }
  | LPAREN expr0 RPAREN { $$ = $2; }
  | IDENTIFIER { $$ = $1; }
  | NUMBER { $$ = $1; }
  ;

%%
