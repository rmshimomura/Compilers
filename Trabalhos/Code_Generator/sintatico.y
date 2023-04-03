%{

    #include <stdio.h>
    extern int yylex();
    extern char* yytext;
    extern int yychar;
    extern int yydebug;
    int yydebug = 1;
    extern void yyerror(char *s);

%}

%token AST
%token VOID
%token INT
%token CHAR
%token RETURN
%token GLOBAL
%token VARIABLE
%token TYPE
%token FUNCTION
%token END_FUNCTION
%token PARAMETER
%token RETURN_TYPE
%token CONSTANT
%token IF
%token ELSE
%token VALUE
%token WHILE
%token FOR
%token DO_WHILE
%token PRINTF
%token SCANF
%token EXIT
%token PLUS
%token MINUS
%token MULTIPLY
%token DIV
%token REMAINDER
%token INC
%token DEC
%token BITWISE_AND
%token BITWISE_OR
%token BITWISE_NOT
%token BITWISE_XOR
%token NOT
%token LOGICAL_AND
%token LOGICAL_OR
%token EQUAL
%token NOT_EQUAL
%token LESS_THAN
%token GREATER_THAN
%token LESS_EQUAL
%token GREATER_EQUAL
%token R_SHIFT
%token L_SHIFT
%token ASSIGN
%token ADD_ASSIGN
%token MINUS_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token L_PAREN
%token R_PAREN
%token L_CURLY_BRACKET
%token R_CURLY_BRACKET
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token NUMBER_SIGN
%token START_ARROW
%token IDENTIFIER
%token NUM_INTEGER
%token STRING
%token CHARACTER
%token NEWLINE

%start Programa

%%

Programa : AST START_ARROW Declaracoes { };

Declaracoes : DeclaraConstante Declaracoes {};
            | DeclaraVariavelGlobal Declaracoes {};
            | DeclaraFuncao Declaracoes {};
            | {};

DeclaraConstante : CONSTANT COLON IDENTIFIER VALUE COLON NUM_INTEGER {};

DeclaraVariavelGlobal : GLOBAL VARIABLE COLON IDENTIFIER TYPE COLON TipoDeVariavel {};

TipoDeVariavel: INT Size {};
    | CHAR Size {};
    | VOID Size {};

// Size serve se quiser declarar algo do tipo: int[10]

Size: L_SQUARE_BRACKET NUM_INTEGER R_SQUARE_BRACKET {};
    | {};

DeclaraFuncao : FUNCTION COLON IDENTIFIER RETURN_TYPE COLON TipoDeVariavel ParametrosDeFuncao DeclararVariaveisLocais CorpoFuncao END_FUNCTION {};

ParametrosDeFuncao: PARAMETER COLON IDENTIFIER TYPE COLON TipoDeVariavel ParametrosDeFuncao {};
          | {};

DeclararVariaveisLocais: VARIABLE COLON IDENTIFIER TYPE COLON TipoDeVariavel DeclararVariaveisLocais {};
            | {};

/* COMANDOS */

CorpoFuncao: ListaComandos {};

ListaComandos: Comando ListaComandosTemporario {};

ListaComandosTemporario: SEMICOLON Comando ListaComandosTemporario {};
            | {};

Comando: OperadorAtribuicao {};
        | OperadorIncremento {};
        | OperadorDecremento {};
        | ComandoDoWhile {};
        | ComandoIf {};
        | ComandoWhile {};
        | ComandoFor {};
        | ComandoPrintf {};
        | ComandoScanf {};
        | ComandoExit {};
        | ComandoReturn {};
        | IDENTIFIER L_PAREN LoopExpressoes R_PAREN {};

LoopExpressoes: Expressao LoopExpressoesTemporario {};
            | {};

LoopExpressoesTemporario: COMMA Expressao LoopExpressoesTemporario {};
                    | {};

ComandoDoWhile: DO_WHILE L_PAREN ListaComandos COMMA CondicaoParada R_PAREN {};

ComandoIf: IF L_PAREN CondicaoParada COMMA ListaComandos COMMA ListaComandos R_PAREN {};
        | IF L_PAREN CondicaoParada COMMA ListaComandos R_PAREN {};

ComandoWhile: WHILE L_PAREN CondicaoParada COMMA ListaComandos R_PAREN {};

ComandoFor: FOR L_PAREN InicializacaoFor COMMA CondicaoParada COMMA AjusteValores COMMA ListaComandos R_PAREN {};

ComandoPrintf: PRINTF L_PAREN STRING COMMA ExpressoesPrintf R_PAREN {};
            | PRINTF L_PAREN STRING R_PAREN {};

ComandoScanf: SCANF L_PAREN STRING COMMA EnderecoVar R_PAREN {};

ComandoExit: EXIT L_PAREN Expressao R_PAREN {};

ComandoReturn: RETURN L_PAREN CondicaoParada R_PAREN {};

/* Scanf */

EnderecoVar: BITWISE_AND L_PAREN IDENTIFIER R_PAREN {};

/* Printf */

ExpressoesPrintf: Expressao ExpressoesPrintfTemporario {};
                | {};

ExpressoesPrintfTemporario: COMMA Expressao ExpressoesPrintfTemporario {};
                        | {};

/* For */

InicializacaoFor: ASSIGN L_PAREN IDENTIFIER COMMA Expressao R_PAREN {};
                | {};

CondicaoParada: Expressao {};
                | {};

AjusteValores: OperadorAtribuicao {};
                | OperadorIncremento {};
                | OperadorDecremento {};

/* Operadores */

OperadorAtribuicao: ASSIGN L_PAREN Expressao COMMA Expressao R_PAREN {};

OperadorIncremento: INC L_PAREN IDENTIFIER R_PAREN {};
                | L_PAREN Expressao R_PAREN INC {};

OperadorDecremento: DEC L_PAREN IDENTIFIER R_PAREN {};
                | L_PAREN Expressao R_PAREN DEC {};

/* EXPRESSOES */

Expressao: BOP {};
        | UOP {};
        | TOP {};
        | IDENTIFIER {};
        | IDENTIFIER L_PAREN IDENTIFIER R_PAREN {}; // fatorial(n);
        | IDENTIFIER L_SQUARE_BRACKET Expressao R_SQUARE_BRACKET {};
        | NUM_INTEGER {};
        | CHARACTER {};
        | STRING {};

BOP: PLUS L_PAREN Expressao COMMA Expressao R_PAREN {};
    | MINUS L_PAREN Expressao COMMA Expressao R_PAREN {};
    | MULTIPLY L_PAREN Expressao COMMA Expressao R_PAREN {};
    | DIV L_PAREN Expressao COMMA Expressao R_PAREN {};
    | REMAINDER L_PAREN Expressao COMMA Expressao R_PAREN {};
    | BITWISE_AND L_PAREN Expressao COMMA Expressao R_PAREN {};
    | BITWISE_OR L_PAREN Expressao COMMA Expressao R_PAREN {};
    | BITWISE_XOR L_PAREN Expressao COMMA Expressao R_PAREN {};
    | LOGICAL_AND L_PAREN Expressao COMMA Expressao R_PAREN {};
    | LOGICAL_OR L_PAREN Expressao COMMA Expressao R_PAREN {};
    | EQUAL L_PAREN Expressao COMMA Expressao R_PAREN {};
    | NOT_EQUAL L_PAREN Expressao COMMA Expressao R_PAREN {};
    | LESS_THAN L_PAREN Expressao COMMA Expressao R_PAREN {};
    | GREATER_THAN L_PAREN Expressao COMMA Expressao R_PAREN {};
    | LESS_EQUAL L_PAREN Expressao COMMA Expressao R_PAREN {};
    | GREATER_EQUAL L_PAREN Expressao COMMA Expressao R_PAREN {};
    | R_SHIFT L_PAREN Expressao COMMA Expressao R_PAREN {};
    | L_SHIFT L_PAREN Expressao COMMA Expressao R_PAREN {};
    | ASSIGN L_PAREN Expressao COMMA Expressao R_PAREN {};
    | ADD_ASSIGN L_PAREN Expressao COMMA Expressao R_PAREN {};
    | MINUS_ASSIGN L_PAREN Expressao COMMA Expressao R_PAREN {};

UOP: PLUS  L_PAREN Expressao R_PAREN {};
    | MINUS L_PAREN Expressao R_PAREN {};
    | MULTIPLY L_PAREN Expressao R_PAREN {};
    | INC L_PAREN Expressao R_PAREN {};
    | DEC L_PAREN Expressao R_PAREN {};
    | BITWISE_NOT L_PAREN Expressao R_PAREN {};
    | NOT L_PAREN Expressao R_PAREN {};
    | L_PAREN Expressao R_PAREN PLUS {};
    | L_PAREN Expressao R_PAREN MINUS {};
    | L_PAREN Expressao R_PAREN MULTIPLY {};
    | L_PAREN Expressao R_PAREN INC {};
    | L_PAREN Expressao R_PAREN DEC {};
    | L_PAREN Expressao R_PAREN BITWISE_NOT {};
    | L_PAREN Expressao R_PAREN NOT {};

TOP: TERNARY_CONDITIONAL L_PAREN Expressao COMMA Expressao COMMA Expressao R_PAREN {}; 

%%

int main(int argc, char **argv) {
    
    #ifdef YYDEBUG
        yydebug = 1;
    #endif

    yyparse();
    
}
