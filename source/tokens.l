%{
#include "Node.hpp"
#include "parser.hpp"
%}

%option noyywrap
%option nounput noinput

/* Keywords */
USING       "using"
VAR         "var"
FUN         "fun"
RETURN      "return"
EXTERN      "extern"
GOTO        "goto"
IF          "if"
ELSE        "else"
FOR         "for"
WHILE       "while"
DO          "do"
BREAK       "break"
CONTINUE    "continue"
STRUCT      "struct"
ENUM        "enum"
/* Literals */
IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*
INTEGER     [0-9]+
STRING      ["]([^"\\\r\n]|\\(.|\n))*["]
/* Punctuation */
LPAREN      "("
RPAREN      ")"
LBRACKET    "["
RBRACKET    "]"
LBRACE      "{"
RBRACE      "}"
SEMICOLON   ";"
COLON       ":"
COMMA       ","
DOT         "."
QUESTION    "?"
ARROW       "=>"
RESOLVE     "::"
ELLIPSIS    "..."
/* Statement Operators */
ASSIGN      "="
/* Expression Operators */
ADD         "+"
SUB         "-"
MUL         "*"
DIV         "/"
MOD         "%"
EQU         "=="
NEQ         "!="
GTE         ">="
LTE         "<="
GT          ">"
LT          "<"
BAND        "&&"
BOR         "||"
BNOT        "!"
AND         "&"
OR          "|"
XOR         "^"
NOT         "~"
SHL         "<<"
SHR         ">>"

%%

{USING}     { return USING; }
{VAR}       { return VAR; }
{FUN}       { return FUN; }
{RETURN}    { return RETURN; }
{EXTERN}    { return EXTERN; }
{GOTO}      { return GOTO; }
{IF}        { return IF; }
{ELSE}      { return ELSE; }
{FOR}       { return FOR; }
{WHILE}     { return WHILE; }
{DO}        { return DO; }
{BREAK}     { return BREAK; }
{CONTINUE}  { return CONTINUE; }
{STRUCT}    { return STRUCT; }
{ENUM}      { return ENUM; }
{IDENTIFIER}    { yylval.identifier = new IdentifierLiteral(yytext); return IDENTIFIER; }
{INTEGER}   { yylval.integer = new IntegerLiteral(atoi(yytext)); return INTEGER; }
{STRING}    { auto tmp = std::string(yytext); yylval.string = new StringLiteral(tmp.substr(1, tmp.size() - 2)); return STRING; }
{LPAREN}    { return LPAREN; }
{RPAREN}    { return RPAREN; }
{LBRACKET}  { return LBRACKET; }
{RBRACKET}  { return RBRACKET; }
{LBRACE}    { return LBRACE; }
{RBRACE}    { return RBRACE; }
{SEMICOLON} { return SEMICOLON; }
{RESOLVE}   { return RESOLVE; }
{COLON}     { return COLON; }
{COMMA}     { return COMMA; }
{DOT}       { return DOT; }
{QUESTION}  { return QUESTION; }
{ARROW}     { return ARROW; }
{ELLIPSIS}  { return ELLIPSIS; }
{ADD}       { return ADD; }
{SUB}       { return SUB; }
{MUL}       { return MUL; }
{DIV}       { return DIV; }
{MOD}       { return MOD; }
{EQU}       { return EQU; }
{NEQ}       { return NEQ; }
{GTE}       { return GTE; }
{LTE}       { return LTE; }
{GT}        { return GT; }
{LT}        { return LT; }
{BAND}      { return BAND; }
{BOR}       { return BOR; }
{BNOT}      { return BNOT; }
{AND}       { return AND; }
{OR}        { return OR; }
{XOR}       { return XOR; }
{NOT}       { return NOT; }
{SHL}       { return SHL; }
{SHR}       { return SHR; }
{ASSIGN}    { return ASSIGN; }

[ \t\r\n\v]     {}
%%
