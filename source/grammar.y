%{
#include "Node.hpp"

int yylex(void);
void yyerror(const char *);
%}

%define parse.error verbose

%union {
    Node *node;
    ListNode *list;

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
%token SEMICOLON COLON COMMA DOT QUESTION ARROW RESOLVE ELLIPSIS
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
%type <node> decl stmt expr arg0 arg1
%type <list> decls stmts exprs args
%type <node> fun returnType body
%type <list> argumentList

%%

prog
  : decls { yylval.node = new ProgramNode($1); }
  ;

decls
  : decls decl { $$ = $1; $$->push($2); }
  | /* NOTHING */ { $$ = new ListNode(); }
  ;

decl
  : fun { $$ = $1; }
  | EXTERN decl { $$ = new ModifierNode("__extern__", $2); }
  ;

fun
  : FUN IDENTIFIER argumentList returnType body { $$ = new FunctionDeclaration($2, $3, $4, $5); }
  ;

returnType
  : ARROW expr { $$ = $2; }
  | /* NOTHING */ { $$ = nullptr; }
  ;

body
  : stmt { $$ = $1; }
  | SEMICOLON { $$ = nullptr; }
  ;

argumentList
  : LPAREN RPAREN { $$ = new ListNode(); }
  | LPAREN args RPAREN { $$ = $2; }
  ;

args
  : arg0 { $$ = new ListNode(); $$->push($1); }
  | args COMMA arg0 { $$ = $1; $$->push($3); }
  ;

arg0
  : arg1 { $$ = $1; }
  | ELLIPSIS arg1 { $$ = new ModifierNode("__variable__", $2); }
  ;

arg1
  : IDENTIFIER { $$ = new VariableDeclaration("param", $1, nullptr); }
  | IDENTIFIER COLON expr { $$ = new VariableDeclaration("param", $1, $3); }
  ;

stmts
  : stmts stmt { $$ = $1; $$->push($2); }
  | /* NOTHING */ { $$ = new ListNode(); }
  ;

stmt
  : LBRACE stmts RBRACE { $$ = $2; }
  | RETURN expr SEMICOLON { $$ = new ModifierNode("__return__", $2); }
  | expr SEMICOLON { $$ = new ModifierNode("__eval__", $1); }
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
