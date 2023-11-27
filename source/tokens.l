%{
#include "Node.hpp"
#include "parser.hpp"
%}

%option noyywrap
%option nounput noinput

SPACE       [ \t\n\r\v]
DIGIT       [0-9]
PLUS        "+"
MINUS       "-"
STAR        "*"
SLASH       "/"
LPAREN      "("
RPAREN      ")"

%%

{SPACE}     { }
{DIGIT}+    { yylval.i32 = atoi(yytext); return NUMBER; }
{PLUS}      { return PLUS; }
{MINUS}     { return MINUS; }
{STAR}      { return STAR; }
{SLASH}     { return SLASH; }
{LPAREN}    { return LPAREN; }
{RPAREN}    { return RPAREN; }
.           { }
%%
