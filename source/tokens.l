%{
#include <cstdint>
#include <string>

#include "Node.hpp"
#include "parser.hpp"
%}

%option noyywrap
%option nounput noinput

COMMA           ","
COLON           ":"
ARROW           "->"
PLUS            "+"
MINUS           "-"
STAR            "*"
SLASH           "/"
LPAREN          "("
RPAREN          ")"
LBRACE          "{"
RBRACE          "}"
FUN             "fun"
RETURN          "return"
NUMBER          [0-9]+
IDENTIFIER      [a-zA-Z_][a-zA-Z0-9_]*
SPACE           [ \t\n\r\v]
%%

{COMMA}         { return COMMA; }
{COLON}         { return COLON; }
{ARROW}         { return ARROW; }
{PLUS}          { return PLUS; }
{MINUS}         { return MINUS; }
{STAR}          { return STAR; }
{SLASH}         { return SLASH; }
{LPAREN}        { return LPAREN; }
{RPAREN}        { return RPAREN; }
{LBRACE}        { return LBRACE; }
{RBRACE}        { return RBRACE; }
{FUN}           { return FUN; }
{RETURN}        { return RETURN; }
{IDENTIFIER}    { yylval.identifier = new Ast::IdentifierLiteral(std::string(yytext)); return IDENTIFIER; }
{NUMBER}        { yylval.integer = new Ast::IntegerLiteral(atoi(yytext)); return NUMBER; }
{SPACE}         { }
.               { }
%%
