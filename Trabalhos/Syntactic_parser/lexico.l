%option noyywrap

%{
    #include <string.h>
    int total_lines = 1;
    int last_line = 0;
    int print_number = 0;
    int columns = 1;
    int column_start_comment = 1;
    void check_new_line(int print_number);
    char* fixed_string(char* string);
    void error_message(int last_line, int first_error_character, char* message);
    void warning_message(int last_line, int first_error_character, char* message);
    char* fix_char(char *string);
    int check_errors(int total_lines, int columns, char* word);
%}

%x COMMENT

%%
      
<INITIAL>{

" "                     { columns++;}
"void"                  { check_new_line(print_number); columns += strlen(yytext); printf("VOID"); print_number++; }
"int"                   { check_new_line(print_number); columns += strlen(yytext); printf("INT"); print_number++; }
"char"                  { check_new_line(print_number); columns += strlen(yytext); printf("CHAR"); print_number++; }
"return"                { check_new_line(print_number); columns += strlen(yytext); printf("RETURN"); print_number++; }
"break"                 { check_new_line(print_number); columns += strlen(yytext); printf("BREAK"); print_number++; }
"switch"                { check_new_line(print_number); columns += strlen(yytext); printf("SWITCH"); print_number++; }
"case"                  { check_new_line(print_number); columns += strlen(yytext); printf("CASE"); print_number++; }
"default"               { check_new_line(print_number); columns += strlen(yytext); printf("DEFAULT"); print_number++; }
"do"                    { check_new_line(print_number); columns += strlen(yytext); printf("DO"); print_number++; }
"while"                 { check_new_line(print_number); columns += strlen(yytext); printf("WHILE"); print_number++; }
"for"                   { check_new_line(print_number); columns += strlen(yytext); printf("FOR"); print_number++; }
"if"                    { check_new_line(print_number); columns += strlen(yytext); printf("IF"); print_number++; }
"else"                  { check_new_line(print_number); columns += strlen(yytext); printf("ELSE"); print_number++; }
"typedef"               { check_new_line(print_number); columns += strlen(yytext); printf("TYPEDEF"); print_number++; }
"struct"                { check_new_line(print_number); columns += strlen(yytext); printf("STRUCT"); print_number++; }
"+"                     { check_new_line(print_number); columns += strlen(yytext); printf("PLUS"); print_number++; }
"-"                     { check_new_line(print_number); columns += strlen(yytext); printf("MINUS"); print_number++; }
"*"                     { check_new_line(print_number); columns += strlen(yytext); printf("MULTIPLY"); print_number++; }
"/"                     { check_new_line(print_number); columns += strlen(yytext); printf("DIV"); print_number++; }
"%"                     { check_new_line(print_number); columns += strlen(yytext); printf("REMAINDER"); print_number++; }
"++"                    { check_new_line(print_number); columns += strlen(yytext); printf("INC"); print_number++; }
"--"                    { check_new_line(print_number); columns += strlen(yytext); printf("DEC"); print_number++; }
"&"                     { check_new_line(print_number); columns += strlen(yytext); printf("BITWISE_AND"); print_number++; }
"|"                     { check_new_line(print_number); columns += strlen(yytext); printf("BITWISE_OR"); print_number++; }
"~"                     { check_new_line(print_number); columns += strlen(yytext); printf("BITWISE_NOT"); print_number++; }
"^"                     { check_new_line(print_number); columns += strlen(yytext); printf("BITWISE_XOR"); print_number++; }
"!"                     { check_new_line(print_number); columns += strlen(yytext); printf("NOT"); print_number++; }
"&&"                    { check_new_line(print_number); columns += strlen(yytext); printf("LOGICAL_AND"); print_number++; }
"||"                    { check_new_line(print_number); columns += strlen(yytext); printf("LOGICAL_OR"); print_number++; }
"=="                    { check_new_line(print_number); columns += strlen(yytext); printf("EQUAL"); print_number++; }
"!="                    { check_new_line(print_number); columns += strlen(yytext); printf("NOT_EQUAL"); print_number++; }
"<"                     { check_new_line(print_number); columns += strlen(yytext); printf("LESS_THAN"); print_number++; }
">"                     { check_new_line(print_number); columns += strlen(yytext); printf("GREATER_THAN"); print_number++; }
"<="                    { check_new_line(print_number); columns += strlen(yytext); printf("LESS_EQUAL"); print_number++; }
">="                    { check_new_line(print_number); columns += strlen(yytext); printf("GREATER_EQUAL"); print_number++; }
">>"                    { check_new_line(print_number); columns += strlen(yytext); printf("R_SHIFT"); print_number++; }
"<<"                    { check_new_line(print_number); columns += strlen(yytext); printf("L_SHIFT"); print_number++; }
"="                     { check_new_line(print_number); columns += strlen(yytext); printf("ASSIGN"); print_number++; }
"+="                    { check_new_line(print_number); columns += strlen(yytext); printf("ADD_ASSIGN"); print_number++; }
"-="                    { check_new_line(print_number); columns += strlen(yytext); printf("MINUS_ASSIGN"); print_number++; }
";"                     { check_new_line(print_number); columns += strlen(yytext); printf("SEMICOLON"); print_number++; }
","                     { check_new_line(print_number); columns += strlen(yytext); printf("COMMA"); print_number++; }
":"                     { check_new_line(print_number); columns += strlen(yytext); printf("COLON"); print_number++; }
"("                     { check_new_line(print_number); columns += strlen(yytext); printf("L_PAREN"); print_number++; }
")"                     { check_new_line(print_number); columns += strlen(yytext); printf("R_PAREN"); print_number++; }
"{"                     { check_new_line(print_number); columns += strlen(yytext); printf("L_CURLY_BRACKET"); print_number++; }
"["                     { check_new_line(print_number); columns += strlen(yytext); printf("L_SQUARE_BRACKET"); print_number++; }
"]"                     { check_new_line(print_number); columns += strlen(yytext); printf("R_SQUARE_BRACKET"); print_number++; }
"?"                     { check_new_line(print_number); columns += strlen(yytext); printf("TERNARY_CONDITIONAL"); print_number++; }
"#"                     { check_new_line(print_number); columns += strlen(yytext); printf("NUMBER_SIGN"); print_number++; }
"->"                    { check_new_line(print_number); columns += strlen(yytext); printf("POINTER"); print_number++; }
"printf"                { check_new_line(print_number); columns += strlen(yytext); printf("PRINTF"); print_number++; }
"scanf"                 { check_new_line(print_number); columns += strlen(yytext); printf("SCANF"); print_number++; }
"define"                { check_new_line(print_number); columns += strlen(yytext); printf("DEFINE"); print_number++; }
"exit"                  { check_new_line(print_number); columns += strlen(yytext); printf("EXIT"); print_number++; }
"/*"                    { last_line = total_lines; BEGIN(COMMENT);  column_start_comment = columns; columns += strlen(yytext); }
"//".*\n                { total_lines++; }
[_a-zA-Z][_a-zA-Z0-9]*  { check_new_line(print_number); check_errors(total_lines, columns, yytext) ? : printf("IDENTIFIER(%s)", yytext); columns += strlen(yytext); print_number++; }
"0"[1-7][0-7]*          { check_new_line(print_number); check_errors(total_lines, columns, yytext) ? : printf("NUM_OCTAL(%s)", yytext); columns += strlen(yytext); print_number++; }
[0-9][0-9]*             { check_new_line(print_number); check_errors(total_lines, columns, yytext) ? : printf("NUM_INTEGER(%s)", yytext); columns += strlen(yytext); print_number++; }
"0"[x|X][a-fA-F0-9]*    { check_new_line(print_number); check_errors(total_lines, columns, yytext) ? : printf("NUM_HEXA(%s)", yytext); columns += strlen(yytext); print_number++; }
\"(\\.|[^"\\])*\"       { check_new_line(print_number); check_errors(total_lines, columns, yytext) ? : printf("STRING(%s)", fixed_string(yytext)); columns += strlen(yytext); print_number++; }
'([^'\\\n]|\\.)'        { check_new_line(print_number); check_errors(total_lines, columns, yytext) ? : printf("CHARACTER(%s)", fix_char(yytext)); columns += strlen(yytext); print_number++; }
\a
\b
\f
\r
\t
\v
\\
\'
\"		
\n                      { total_lines++; columns = 1; column_start_comment = 1; }
"}"                     { check_new_line(print_number); columns += strlen(yytext); printf("R_CURLY_BRACKET"); print_number++; }
.                       { check_new_line(print_number); error_message(total_lines, columns, yytext); print_number++; }
}

<COMMENT>{
"/*/".*                 { last_line = total_lines; BEGIN(INITIAL); columns += strlen(yytext); column_start_comment = columns; }
" "                     { columns++; }
"//"
"/*"                    { last_line = total_lines; check_new_line(print_number); warning_message(last_line, columns, "'/*' within block comment"); print_number++; columns += 2; unput('*'); }
"*/"                    { BEGIN(INITIAL); print_number++; columns += 2; }
"*"
[^\n]                   { columns += strlen(yytext); }
\n                      { columns = 1; total_lines++; }
<<EOF>>                 { check_new_line(print_number); error_message(last_line, column_start_comment, "unterminated comment"); print_number++; return -1; }
}

%%

void check_new_line(int print_number) {
    
    if(print_number) printf("\n");

}

char* fix_char(char *string) {
    // remove the single quotes if they exist
    
    char* new_string = malloc(strlen(string) - 1);

    int index = 0;

    // If the string is \' just return the second and third characters

    if(!strcmp(string, "'\\'\'")) {
        new_string[0] = string[1];
        new_string[1] = string[2];
        new_string[2] = '\0';
        return new_string;
    }

    for(int i = 0; i < strlen(string) - 1; i++) {
        if(string[i] != '\'') {
            new_string[index] = string[i];
            index++;
        }
    }

    return new_string;

}

int check_errors(int total_lines, int columns, char* word) {
    if(strlen(word) > 255) {
        error_message(total_lines, columns, "identifier too long");
        return 1;
    }
    return 0;

}

void error_message(int last_line, int first_error_character, char* message) {
    printf("error:lexical:%d:%d: %s", last_line, first_error_character, message);
}

void warning_message(int last_line, int first_error_character, char* message) {
    printf("warning:%d:%d: %s", last_line, first_error_character, message);
}

char* fixed_string(char* string) {

    char* fixed_string = malloc(strlen(string) - 1);
    
    // All characters except the first and last
    strncpy(fixed_string, string + 1, strlen(string) - 2);
    fixed_string[strlen(string) - 2] = '\0';

    return fixed_string;

}

int main () {
    yylex();
    return 0;
}