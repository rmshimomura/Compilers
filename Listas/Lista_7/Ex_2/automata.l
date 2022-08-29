%option noyywrap 

%%

\n {}
"if" { printf("IF\n"); }
"i"([a-e]|[g-z]|[0-9])([a-z]|[0-9])* { printf("%s ID\n", yytext); }
"if"([a-z]|[0-9])* { printf("%s ID\n", yytext); }
([a-h]|[j-z])([0-9]|[a-z])* { printf("%s ID\n", yytext);}
"." { printf("ERROR\n"); }
"."[0-9]+ { printf("%s REAL\n", yytext); }
[0-9]+ { printf("%s NUM\n", yytext); }
[0-9]+"."[0-9]* { printf("%s REAL\n", yytext); }
"-" { printf("ERROR\n"); }
"--"([a-z])* { printf("%s COMMENT\n", yytext); }
" "* { printf("white space\n"); }
. { printf("%s ERROR\n", yytext); }

%%

int main (int argc, char *argv[]) {
    yylex();
    return 0;
}