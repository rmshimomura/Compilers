%{

    #include <stdio.h>
    extern int yylex();
    extern char* yytext;
	extern int last_line;
	extern char buffer[1024];
	extern int total_lines;
	extern int columns;
    void yyerror(void *s);

%}

%token VOID
%token INT
%token CHAR
%token RETURN
%token BREAK
%token SWITCH
%token CASE
%token DEFAULT
%token DO
%token WHILE
%token FOR
%token IF
%token ELSE
%token TYPEDEF
%token STRUCT
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
%token POINTER
%token PRINTF
%token SCANF
%token DEFINE
%token EXIT
%token IDENTIFIER
%token NUM_OCTAL
%token NUM_INTEGER
%token NUM_HEXA
%token STRING
%token CHARACTER

%start Programa

%%

Programa : DeclaracoesOuFuncao LoopDeclaracoesOuFuncao {};

DeclaracoesOuFuncao : Declaracoes {}
                    | Funcao {};

LoopDeclaracoesOuFuncao : DeclaracoesOuFuncao LoopDeclaracoesOuFuncao {}
                        | {};

Declaracoes : NUMBER_SIGN DEFINE IDENTIFIER Expressao {}
            | DeclaracaoVariaveis {}
            | DeclaracaoPrototipos {};

Funcao : Tipo LoopVezes IDENTIFIER Parametros L_CURLY_BRACKET LoopFuncaoDeclaracaoVariaveis Comandos R_CURLY_BRACKET {};

LoopVezes : MULTIPLY LoopVezes {}
            | {};

LoopFuncaoDeclaracaoVariaveis : DeclaracaoVariaveis LoopFuncaoDeclaracaoVariaveis {}
                        | {};

DeclaracaoVariaveis : Tipo LoopDeclaracaoVariaveis SEMICOLON {};

LoopDeclaracaoVariaveis : LoopVezes IDENTIFIER LoopExpressao Switch1 Switch2 {};

Switch1: ASSIGN ExpressaoAtribuicao {}
		| {};

Switch2: COMMA LoopDeclaracaoVariaveis {}
		| {};

LoopExpressao : L_SQUARE_BRACKET Expressao R_SQUARE_BRACKET LoopExpressao {}
                | {};

DeclaracaoPrototipos : Tipo LoopVezes IDENTIFIER Parametros SEMICOLON {};

Parametros : L_PAREN LoopParametros R_PAREN {};

LoopParametros : Tipo LoopVezes IDENTIFIER LoopExpressao Switch3 {}
                | {};

Switch3 : COMMA LoopParametros {}
        | {};

Tipo : INT {}
    | CHAR {}
    | VOID {};

Bloco : L_CURLY_BRACKET Comandos R_CURLY_BRACKET {};

Comandos : ListaComandos LoopListaComandos {};

LoopListaComandos : ListaComandos LoopListaComandos {}
                    | {};


ListaComandos : DO Bloco WHILE L_PAREN Expressao R_PAREN SEMICOLON {}
                | IF L_PAREN Expressao R_PAREN Bloco Switch5 {}
                | WHILE L_PAREN Expressao R_PAREN Bloco {}
                | FOR L_PAREN Switch6 SEMICOLON Switch6 SEMICOLON Switch6 R_PAREN Bloco {}
                | PRINTF L_PAREN STRING Switch7 R_PAREN SEMICOLON {}
                | SCANF L_PAREN STRING COMMA BITWISE_AND R_PAREN SEMICOLON {}
                | EXIT L_PAREN Expressao R_PAREN SEMICOLON {}
                | RETURN Switch6 SEMICOLON {}
                | Expressao SEMICOLON {}
                | SEMICOLON {}
                | Bloco {};

Switch5 : ELSE Bloco {}
        | {};

Switch6 : Expressao {}
        | {};

Switch7 : COMMA Expressao {}
        | {};

Expressao : ExpressaoAtribuicao {}
            | Expressao COMMA ExpressaoAtribuicao {};

ExpressaoAtribuicao : ExpressaoCondicional {}
                    | ExpressaoUnaria Switch8 ExpressaoAtribuicao {}
Switch8 : ASSIGN {}
        | ADD_ASSIGN {}
        | MINUS_ASSIGN {};

ExpressaoCondicional : ExpressaoOrLogico Switch9 {};

Switch9 : TERNARY_CONDITIONAL Expressao COLON ExpressaoCondicional {}
        | {};

ExpressaoOrLogico : ExpressaoAndLogico {}
                    | ExpressaoOrLogico LOGICAL_OR ExpressaoAndLogico {};

ExpressaoAndLogico : ExpressaoOr {}
                    | ExpressaoAndLogico LOGICAL_AND ExpressaoOr {};

ExpressaoOr : ExpressaoXor {}
            | ExpressaoOr BITWISE_OR ExpressaoXor {};

ExpressaoXor : ExpressaoAnd {}
            | ExpressaoXor BITWISE_XOR ExpressaoAnd {};

ExpressaoAnd : ExpressaoIgualdade {}
            | ExpressaoAnd BITWISE_AND ExpressaoIgualdade {};

ExpressaoIgualdade : ExpressaoRelacional {}
                    | ExpressaoIgualdade EQUAL ExpressaoRelacional {}
                    | ExpressaoIgualdade NOT_EQUAL ExpressaoRelacional {};

ExpressaoRelacional : ExpressaoShift {}
                    | ExpressaoRelacional LESS_THAN ExpressaoShift {}
                    | ExpressaoRelacional GREATER_THAN ExpressaoShift {}
                    | ExpressaoRelacional LESS_EQUAL ExpressaoShift {}
                    | ExpressaoRelacional GREATER_EQUAL ExpressaoShift {};

ExpressaoShift : ExpressaoAditiva {}
                | ExpressaoShift L_SHIFT ExpressaoAditiva {}
                | ExpressaoShift R_SHIFT ExpressaoAditiva {};

ExpressaoAditiva : ExpressaoMultiplicativa {}
                | ExpressaoAditiva PLUS ExpressaoMultiplicativa {}
                | ExpressaoAditiva MINUS ExpressaoMultiplicativa {};

ExpressaoMultiplicativa : ExpressaoCast {}
                        | ExpressaoMultiplicativa MULTIPLY ExpressaoCast {}
                        | ExpressaoMultiplicativa DIV ExpressaoCast {}
                        | ExpressaoMultiplicativa REMAINDER ExpressaoCast {};

ExpressaoCast : ExpressaoUnaria {}
                | L_PAREN Tipo LoopVezes R_PAREN ExpressaoCast {};

ExpressaoUnaria : ExpressaoPosfixa {}
                | INC ExpressaoUnaria {}
                | DEC ExpressaoUnaria {}
                | BITWISE_AND ExpressaoCast {}
                | MULTIPLY ExpressaoCast {}
                | PLUS ExpressaoCast {}
                | MINUS ExpressaoCast {}
                | NOT ExpressaoCast {}
                | BITWISE_NOT ExpressaoCast {};

ExpressaoPosfixa : ExpressaoPrimaria {}
                | ExpressaoPosfixa L_SQUARE_BRACKET Expressao R_SQUARE_BRACKET {}
                | ExpressaoPosfixa INC {}
                | ExpressaoPosfixa DEC {}
                | ExpressaoPosfixa L_PAREN Switch10 R_PAREN {};
Switch10 : ExpressaoAtribuicao Switch11 {}
        | {};
Switch11 : COMMA ExpressaoAtribuicao Switch11
        | {};

ExpressaoPrimaria : IDENTIFIER  {}
                    | Numero {}
                    | CHARACTER {}
                    | STRING {}
                    | L_PAREN Expressao R_PAREN {};

Numero : NUM_INTEGER {}
        | NUM_HEXA {}
        | NUM_OCTAL {};

%%

void yyerror(void *s) {

	columns -= strlen(yytext);

    printf("error:syntax:%d:%d: %s\n%s", total_lines, columns, yytext, buffer);
	for(int i = 0; i < columns -1; i++) {
		printf(" ");
	}
	printf("^");
	exit(0);
}

int main(int argc, char **argv) {
    yyparse();
	if(last_line > 0) printf("\n");
	printf("SUCCESSFUL COMPILATION.");
    return 0;
}
