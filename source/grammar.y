%{
#include "Node.hpp"

int yylex(void);
void yyerror(const char *);
%}

%define parse.error verbose

%union {
    Node *node;
    ListNode *list;

    GenericNode *generic;
    IdentifierLiteral *identifier;
    IntegerLiteral *integer;
    StringLiteral *string;
}

%start prog
/* Keywords */
%token USING VAR
%token FUN RETURN EXTERN
%token GOTO IF ELSE FOR WHILE DO BREAK CONTINUE
%token STRUCT ENUM
/* Literals */
%token IDENTIFIER INTEGER STRING
/* Punctuation */
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token SEMICOLON COLON COMMA DOT QUESTION ARROW
/* Statement Operators */
%token ASSIGN
/* Expression Operators */
%token ADD SUB MUL DIV MOD
%token EQU NEQ GTE LTE GT LT
%token BAND BOR BNOT
%token AND OR XOR NOT
%token SHL SHR

%left ADD SUB
%left MUL DIV MOD

%type <identifier> IDENTIFIER
%type <integer> INTEGER
%type <string> STRING
%type <list> decls stmts exprs args
%type <node> decl stmt expr arg
%type <node> fun

%%

prog
  : decls { yylval.node = $1; }
  ;

decls
  : decls decl { $$ = $1; $$->push($2); }
  | /* NOTHING */ { $$ = new ListNode(); }
  ;

decl
  : fun
  ;

fun
  : FUN IDENTIFIER LPAREN args RPAREN ARROW expr stmt { $$ = new GenericNode("__fun__", { $2, $4, $7, $8 }); }
  ;

args
  : arg { $$ = new ListNode(); $$->push($1); }
  | args COMMA arg { $$ = $1; $$->push($3); }
  | /* NOTHING */ { $$ = new ListNode(); }
  ;

arg
  : IDENTIFIER { $$ = new GenericNode("__binding__", { $1 }); }
  | IDENTIFIER COLON expr { $$ = new GenericNode("__binding__", { $1, $3 }); }
  ;

stmts
  : stmts stmt { $$ = $1; $$->push($2); }
  | /* NOTHING */ { $$ = new ListNode(); }
  ;

stmt
  : LBRACE stmts RBRACE { $$ = $2; }
  | RETURN expr SEMICOLON { $$ = new ModifiedStatement("__return__", $2); }
  | expr SEMICOLON { $$ = new ModifiedStatement("__eval__", $1); }
  ;

exprs
  : expr { $$ = new ListNode(); $$->push($1); }
  | exprs COMMA expr { $$ = $1; $$->push($3); }
  ;

expr
  : LPAREN expr RPAREN { $$ = $2; }
  | expr ADD expr { auto args = new ListNode(); args->push($1); args->push($3); $$ = new FunctionExpression(new IdentifierLiteral("__add__"), args); }
  | expr SUB expr { auto args = new ListNode(); args->push($1); args->push($3); $$ = new FunctionExpression(new IdentifierLiteral("__sub__"), args); }
  | expr MUL expr { auto args = new ListNode(); args->push($1); args->push($3); $$ = new FunctionExpression(new IdentifierLiteral("__mul__"), args); }
  | expr DIV expr { auto args = new ListNode(); args->push($1); args->push($3); $$ = new FunctionExpression(new IdentifierLiteral("__div__"), args); }
  | expr MOD expr { auto args = new ListNode(); args->push($1); args->push($3); $$ = new FunctionExpression(new IdentifierLiteral("__mod__"), args); }
  | SUB expr { auto args = new ListNode(); args->push($2); $$ = new FunctionExpression(new IdentifierLiteral("__negate__"), args); }
  | MUL expr { auto args = new ListNode(); args->push($2); $$ = new FunctionExpression(new IdentifierLiteral("__deref__"), args); }
  | expr LPAREN exprs RPAREN { $$ = new FunctionExpression($1, $3); }
  | IDENTIFIER { $$ = $1; }
  | INTEGER { $$ = $1; }
  | STRING { $$ = $1; }
  ;

%%
