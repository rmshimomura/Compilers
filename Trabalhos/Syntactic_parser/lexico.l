%option noyywrap

%{
    #include <stdio.h>
    #include <string.h>
    #include <sintatico.tab.h>
    extern YYSTYPE yylval;
    int total_lines = 1;
    int last_line = 0;
    int columns = 1;
    int column_start_comment = 1;
    int print_number = 0;
    char buffer[1024];
    void error_message_lexical(int last_line, int first_error_character, char* message);
    void warning_message(int last_line, int first_error_character, char* message);
    int check_errors(int total_lines, int columns, char* word);
%}

%x COMMENT

%%
      
<INITIAL>{

" "                     { columns++; }
"void"                  { columns += strlen(yytext); return VOID;}
"int"                   { columns += strlen(yytext); return INT;}
"char"                  { columns += strlen(yytext); return CHAR;}
"return"                { columns += strlen(yytext); return RETURN;}
"break"                 { columns += strlen(yytext); return BREAK;}
"switch"                { columns += strlen(yytext); return SWITCH;}
"case"                  { columns += strlen(yytext); return CASE;}
"default"               { columns += strlen(yytext); return DEFAULT;}
"do"                    { columns += strlen(yytext); return DO;}
"while"                 { columns += strlen(yytext); return WHILE;}
"for"                   { columns += strlen(yytext); return FOR;}
"if"                    { columns += strlen(yytext); return IF;}
"else"                  { columns += strlen(yytext); return ELSE;}
"typedef"               { columns += strlen(yytext); return TYPEDEF;}
"struct"                { columns += strlen(yytext); return STRUCT;}
"+"                     { columns += strlen(yytext); return PLUS;}
"-"                     { columns += strlen(yytext); return MINUS;}
"*"                     { columns += strlen(yytext); return MULTIPLY;}
"/"                     { columns += strlen(yytext); return DIV;}
"%"                     { columns += strlen(yytext); return REMAINDER;}
"++"                    { columns += strlen(yytext); return INC;}
"--"                    { columns += strlen(yytext); return DEC;}
"&"                     { columns += strlen(yytext); return BITWISE_AND;}
"|"                     { columns += strlen(yytext); return BITWISE_OR;}
"~"                     { columns += strlen(yytext); return BITWISE_NOT;}
"^"                     { columns += strlen(yytext); return BITWISE_XOR;}
"!"                     { columns += strlen(yytext); return NOT;}
"&&"                    { columns += strlen(yytext); return LOGICAL_AND;}
"||"                    { columns += strlen(yytext); return LOGICAL_OR;}
"=="                    { columns += strlen(yytext); return EQUAL;}
"!="                    { columns += strlen(yytext); return NOT_EQUAL;}
"<"                     { columns += strlen(yytext); return LESS_THAN;}
">"                     { columns += strlen(yytext); return GREATER_THAN;}
"<="                    { columns += strlen(yytext); return LESS_EQUAL;}
">="                    { columns += strlen(yytext); return GREATER_EQUAL;}
">>"                    { columns += strlen(yytext); return R_SHIFT;}
"<<"                    { columns += strlen(yytext); return L_SHIFT;}
"="                     { columns += strlen(yytext); return ASSIGN;}
"+="                    { columns += strlen(yytext); return ADD_ASSIGN;}
"-="                    { columns += strlen(yytext); return MINUS_ASSIGN;}
";"                     { columns += strlen(yytext); return SEMICOLON;}
","                     { columns += strlen(yytext); return COMMA;}
":"                     { columns += strlen(yytext); return COLON;}
"("                     { columns += strlen(yytext); return L_PAREN;}
")"                     { columns += strlen(yytext); return R_PAREN;}
"{"                     { columns += strlen(yytext); return L_CURLY_BRACKET;}
"["                     { columns += strlen(yytext); return L_SQUARE_BRACKET;}
"]"                     { columns += strlen(yytext); return R_SQUARE_BRACKET;}
"?"                     { columns += strlen(yytext); return TERNARY_CONDITIONAL;}
"#"                     { columns += strlen(yytext); return NUMBER_SIGN;}
"->"                    { columns += strlen(yytext); return POINTER;}
"printf"                { columns += strlen(yytext); return PRINTF;}
"scanf"                 { columns += strlen(yytext); return SCANF;}
"define"                { columns += strlen(yytext); return DEFINE;}
"exit"                  { columns += strlen(yytext); return EXIT;}
"/*"                    { last_line = total_lines; column_start_comment = columns; columns += strlen(yytext); BEGIN(COMMENT); }
"//".*                  
[_a-zA-Z][_a-zA-Z0-9]*  { check_errors(total_lines, columns, yytext) ? : (columns += strlen(yytext)); return IDENTIFIER; }
"0"[1-7][0-7]*          { check_errors(total_lines, columns, yytext) ? : (columns += strlen(yytext)); return NUM_OCTAL; }
[0-9][0-9]*             { check_errors(total_lines, columns, yytext) ? : (columns += strlen(yytext)); return NUM_INTEGER; }
"0"[x|X][a-fA-F0-9]+    { check_errors(total_lines, columns, yytext) ? : (columns += strlen(yytext)); return NUM_HEXA; }
\"([^"\\\n]|\\.|\\\n)*\"    { check_errors(total_lines, columns, yytext) ? : (columns += strlen(yytext)); return STRING; }
'([^'\\\n]|\\.)'        { check_errors(total_lines, columns, yytext) ? : (columns += strlen(yytext)); return CHARACTER; }
\a
\b
\f
\r
\t
\v
\\
\'
\"		
\n                      { columns = 1; column_start_comment = 1; total_lines++; update_buffer(total_lines);}
"}"                     { columns += strlen(yytext); return R_CURLY_BRACKET;}
.                       { error_message_lexical(total_lines, columns, yytext); }
}

<COMMENT>{
"/*/".*                 { last_line = total_lines; BEGIN(INITIAL); columns += strlen(yytext); column_start_comment = columns; }
" "                     { columns++; }
"//"
"/*"                    { last_line = total_lines; warning_message(last_line, columns, "'/*' within block comment"); columns += 2; unput('*'); }
"*/"                    { BEGIN(INITIAL); print_number++; columns += 2; }
"*"                     { columns++; }
[^\n]                   { columns += strlen(yytext); }
\n                      { columns = 1; total_lines++; column_start_comment = 1; }
<<EOF>>                 { error_message_lexical(last_line, column_start_comment, "unterminated comment"); print_number++; return -1; }
}

%%

int check_errors(int total_lines, int columns, char* word) {
    if(strlen(word) > 255) {
        error_message_lexical(total_lines, columns, "identifier too long");
        return 1;
    }
    return 0;

}

void error_message_lexical(int last_line, int first_error_character, char* message) {
    if(print_number > 0) printf("\n"); 
    printf("error:lexical:%d:%d: %s", last_line, first_error_character, message);
    print_number++;
}

void warning_message(int last_line, int first_error_character, char* message) {
    if(print_number > 0) printf("\n"); 
    printf("warning:%d:%d: %s", last_line, first_error_character, message);
    print_number++;
}

void update_buffer(int total_lines) {
    fseek(stdin, 0, SEEK_SET);
    for(int i = 0; i < total_lines; i++) {
        fgets(buffer, 1000, stdin);
    }
}
