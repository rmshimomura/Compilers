%option noyywrap

%{
    #include "sintatico.tab.hh"
    extern YYSTYPE yylval;
%}

%%
      
<INITIAL>{

" "                     {  }
"Grafo"                 { return GRAFO; }
"K"                     { return K_TOKEN; }
"-->"                  { return ARROW; }
":"                     { return COLON; }
"="                     { return EQUAL; }
[0-9][0-9]*             { 
                            yylval.integer_token = atoi(yytext);
                            return NUM_INTEGER;
                        }
\n                      { return NEWLINE; }
\r
.                       { printf("Caracter Misterioso: %d\n", *yytext); exit(0); }
}

%%

void yyerror(char *s) {
    printf("Erro: %s\n", s);
}