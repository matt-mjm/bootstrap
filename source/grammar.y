%{
#include "Node.hpp"

int yylex(void);
void yyerror(const char *);
%}

%define parse.error verbose

%union {
    Node *node;
    GenericNode *generic;
}

%start prog
/* Keywords */
%token USING VAR
%token FUN RETURN EXTERN
%token GOTO IF ELSE FOR WHILE DO BREAK CONTINUE
%token STRUCT ENUM
/* Literals */
%token IDENTIFIER INTEGER
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

%type <generic> IDENTIFIER INTEGER
%type <generic> fun args argc arg stmts stmt expr

%%

prog
  : fun { yylval.node = $1; }
  ;

fun
  : FUN IDENTIFIER LPAREN args RPAREN ARROW expr stmt { $$ = new GenericNode("__fun__", { $2, $4, $7, $8 }); }
  ;

args
  : arg argc { $$ = $2; $$->children.insert($$->children.begin(), $1); }
  | /* NOTHING */ { $$ = new GenericNode("__args__", {}); }
  ;

argc
  : COMMA arg argc { $$ = $3; $$->children.insert($$->children.begin(), $2); }
  | /* NOTHING */ { $$ = new GenericNode("__args__", {}); }
  ;

arg
  : IDENTIFIER { $$ = new GenericNode("__binding__", { $1 }); }
  | IDENTIFIER COLON expr { $$ = new GenericNode("__binding__", { $1, $3 }); }
  ;

stmts
  : stmt stmts { $$ = $2; $$->children.insert($$->children.begin(), $1); }
  | /* NOTHING */ { $$ = new GenericNode("__block__", {}); }
  ;

stmt
  : LBRACE stmts RBRACE { $$ = $2; }
  | RETURN expr SEMICOLON { $$ = new GenericNode("__return__", { $2 }); }
  ;

expr
  : LPAREN expr RPAREN { $$ = $2; }
  | expr ADD expr { $$ = new GenericNode("__add__", { $1, $3 }); }
  | expr SUB expr { $$ = new GenericNode("__sub__", { $1, $3 }); }
  | expr MUL expr { $$ = new GenericNode("__mul__", { $1, $3 }); }
  | expr DIV expr { $$ = new GenericNode("__div__", { $1, $3 }); }
  | expr MOD expr { $$ = new GenericNode("__mod__", { $1, $3 }); }
  | SUB expr { $$ = new GenericNode("__negate__", { $2 }); }
  | MUL expr { $$ = new GenericNode("__deref__", { $2 }); }
  | IDENTIFIER { $$ = $1; }
  | INTEGER { $$ = $1; }
  ;

%%
