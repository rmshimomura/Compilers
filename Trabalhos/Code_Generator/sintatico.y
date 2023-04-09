%{

    #include "ast_node.hh"
    extern int yylex(void);
    extern char* yytext;
    extern int yychar;
    extern int yydebug;
    int yydebug = 1;
    extern void yyerror(char *s);
    std::vector<ast::AST_Constant*> constantes;
    std::vector<ast::AST_Variable*> variaveis_globais;
    std::vector<ast::AST_Function*> funcoes;

%}


%union {
    ast::AST_Node_BOP* Type_AST_Node_BOP;
    ast::AST_Node_UOP* Type_AST_Node_UOP;
    ast::AST_Node_TOP* Type_AST_Node_TOP;
    ast::AST_Node_Expressao* Type_AST_Node_Expression;
    ast::AST_Node_Chamada_Funcao* Type_AST_Node_Chamada_Funcao;
    ast::AST_Node_Opcoes_Expressao* Type_AST_Node_Opcoes_Expressao;
    ast::AST_Node_Loop_Expressoes* Type_AST_Node_Loop_Expressoes;
    ast::AST_Node_Loop_Expressoes_Temporario* Type_AST_Node_Loop_Expressoes_Temporario;
    ast::AST_Node_Loop_Matriz* Type_AST_Node_Loop_Matriz;
    ast::AST_Node_Condicao_Parada* Type_AST_Node_Condicao_Parada;
    ast::AST_Node_Ajuste_Valores* Type_AST_Node_Ajuste_Valores;
    ast::AST_Node_Inicializacao_For* Type_AST_Node_Inicializacao_For;
    ast::AST_Node_Expressoes_Printf_Temporario* Type_AST_Node_Expressoes_Printf_Temporario;
    ast::AST_Node_Expressoes_Printf* Type_AST_Node_Expressoes_Printf;
    ast::AST_Node_Endereco_Var* Type_AST_Node_Endereco_Var;
    ast::AST_Node_Comando_Return* Type_AST_Node_Comando_Return;
    ast::AST_Node_Comando_Exit* Type_AST_Node_Comando_Exit;
    ast::AST_Node_Comando_Scanf* Type_AST_Node_Comando_Scanf;
    ast::AST_Node_Comando_Printf* Type_AST_Node_Comando_Printf;
    ast::AST_Node_Comando_For* Type_AST_Node_Comando_For;
    ast::AST_Node_Comando_While* Type_AST_Node_Comando_While;
    ast::AST_Node_Comando_If* Type_AST_Node_Comando_If;
    ast::AST_Node_Comando_Do_While* Type_AST_Node_Comando_Do_While;
    ast::AST_Node_Comando* Type_AST_Node_Comando;
    ast::AST_Node_Lista_Comandos_Temporario* Type_AST_Node_Lista_Comandos_Temporario;
    ast::AST_Node_Lista_Comandos* Type_AST_Node_Lista_Comandos;
    ast::AST_Node_Corpo_Funcao* Type_AST_Node_Corpo_Funcao;
    ast::AST_Variable* Type_AST_Variable;
    ast::AST_Constant* Type_AST_Constant;
    ast::AST_Parameter* Type_AST_Parameter;
    ast::AST_Function* Type_AST_Function;

    std::string* string_token;
    int integer_token;
    char character_token;
}

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
%token L_SQUARE_BRACKET
%token R_SQUARE_BRACKET
%token TERNARY_CONDITIONAL
%token START_ARROW
%token<string_token> IDENTIFIER
%token<integer_token> NUM_INTEGER
%token<string_token> STRING
%token<character_token> CHARACTER
%token NEWLINE

%type <Type_AST_Node_BOP> BOP
%type <Type_AST_Node_UOP> UOP
%type <Type_AST_Node_TOP> TOP
%type <Type_AST_Node_Expression> Expressao
%type <Type_AST_Node_Loop_Matriz> LoopMatriz
%type <Type_AST_Node_Loop_Expressoes_Temporario> LoopExpressoesTemporario
%type <Type_AST_Node_Loop_Expressoes> LoopExpressoes
%type <Type_AST_Node_Opcoes_Expressao> OpcoesExpressao
%type <Type_AST_Node_Chamada_Funcao> ChamadaDeFuncao
%type <Type_AST_Node_Ajuste_Valores> AjusteValores
%type <Type_AST_Node_Condicao_Parada> CondicaoParada
%type <Type_AST_Node_Inicializacao_For> InicializacaoFor
%type <Type_AST_Node_Expressoes_Printf_Temporario> ExpressoesPrintfTemporario
%type <Type_AST_Node_Expressoes_Printf> ExpressoesPrintf
%type <Type_AST_Node_Endereco_Var> EnderecoVar
%type <Type_AST_Node_Comando_Return> ComandoReturn
%type <Type_AST_Node_Comando_Exit> ComandoExit
%type <Type_AST_Node_Comando_Scanf> ComandoScanf
%type <Type_AST_Node_Comando_Printf> ComandoPrintf
%type <Type_AST_Node_Comando_For> ComandoFor
%type <Type_AST_Node_Comando_While> ComandoWhile
%type <Type_AST_Node_Comando_If> ComandoIf
%type <Type_AST_Node_Comando_Do_While> ComandoDoWhile
%type <Type_AST_Node_Comando> Comando
%type <Type_AST_Node_Lista_Comandos_Temporario> ListaComandosTemporario
%type <Type_AST_Node_Lista_Comandos> ListaComandos
%type <Type_AST_Node_Corpo_Funcao> CorpoFuncao


%start Programa

%%

Programa : AST START_ARROW ConsumirNovasLinhas Declaracoes { };

ConsumirNovasLinhas: ConsumirNovasLinhas NEWLINE {};
                    | {};

Declaracoes : DeclaraConstante ConsumirNovasLinhas Declaracoes  {};
            | DeclaraVariavelGlobal ConsumirNovasLinhas Declaracoes {};
            | DeclaraFuncao ConsumirNovasLinhas Declaracoes {};
            | {};

DeclaraConstante : CONSTANT COLON IDENTIFIER VALUE COLON NUM_INTEGER {};

DeclaraVariavelGlobal : GLOBAL VARIABLE COLON IDENTIFIER TYPE COLON TipoDeVariavel {};

TipoDeVariavel: INT TamanhoVariavel NEWLINE {};
    | CHAR TamanhoVariavel NEWLINE {};
    | VOID TamanhoVariavel NEWLINE {};

TamanhoVariavel: L_SQUARE_BRACKET NUM_INTEGER R_SQUARE_BRACKET LoopColchetes {};
                | MULTIPLY LoopPonteirosTemporario {};
                | {};

LoopColchetes : L_SQUARE_BRACKET NUM_INTEGER R_SQUARE_BRACKET LoopColchetes {};
            | {};

LoopPonteirosTemporario: MULTIPLY LoopPonteirosTemporario {};
                    | {};

DeclaraFuncao : FUNCTION COLON IDENTIFIER ConsumirNovasLinhas RETURN_TYPE COLON TipoDeVariavel ConsumirNovasLinhas ParametrosDeFuncao DeclararVariaveisLocais CorpoFuncao ConsumirNovasLinhas END_FUNCTION {};

ParametrosDeFuncao: PARAMETER COLON IDENTIFIER TYPE COLON TipoDeVariavel ConsumirNovasLinhas ParametrosDeFuncao {};
          | {};

DeclararVariaveisLocais: VARIABLE COLON IDENTIFIER TYPE COLON TipoDeVariavel ConsumirNovasLinhas DeclararVariaveisLocais {};
            | {};

/* COMANDOS */

CorpoFuncao: ListaComandos {$$ = new ast::AST_Node_Corpo_Funcao($1);};

ListaComandos: Comando ListaComandosTemporario {$$ = new ast::AST_Node_Lista_Comandos($1, $2);};

ListaComandosTemporario: SEMICOLON ConsumirNovasLinhas Comando ListaComandosTemporario {$$ = new ast::AST_Node_Lista_Comandos_Temporario($3, $4);};
            | {$$ = nullptr;};

Comando: Expressao {$$ = new ast::AST_Node_Comando($1);};
        | ComandoDoWhile {$$ = new ast::AST_Node_Comando($1);};
        | ComandoIf {$$ = new ast::AST_Node_Comando($1);};
        | ComandoWhile {$$ = new ast::AST_Node_Comando($1);};
        | ComandoFor {$$ = new ast::AST_Node_Comando($1);};
        | ComandoPrintf {$$ = new ast::AST_Node_Comando($1);};
        | ComandoScanf {$$ = new ast::AST_Node_Comando($1);};
        | ComandoExit {$$ = new ast::AST_Node_Comando($1);};
        | ComandoReturn {$$ = new ast::AST_Node_Comando($1);};

ComandoDoWhile: DO_WHILE L_PAREN ListaComandos COMMA CondicaoParada R_PAREN {$$ = new ast::AST_Node_Comando_Do_While($3, $5);};

ComandoIf: IF L_PAREN CondicaoParada COMMA ListaComandos COMMA ListaComandos R_PAREN {$$ = new ast::AST_Node_Comando_If($3, $5, $7);};
        | IF L_PAREN CondicaoParada COMMA ListaComandos R_PAREN {$$ = new ast::AST_Node_Comando_If($3, $5);};

ComandoWhile: WHILE L_PAREN CondicaoParada COMMA ListaComandos R_PAREN {$$ = new ast::AST_Node_Comando_While($3, $5);};

ComandoFor: FOR L_PAREN InicializacaoFor COMMA CondicaoParada COMMA AjusteValores COMMA ListaComandos R_PAREN {$$ = new ast::AST_Node_Comando_For($3, $5, $7, $9);};

ComandoPrintf: PRINTF L_PAREN STRING COMMA ExpressoesPrintf R_PAREN {$$ = new ast::AST_Node_Comando_Printf($3, $5);};
            | PRINTF L_PAREN STRING R_PAREN {$$ = new ast::AST_Node_Comando_Printf($3);};

ComandoScanf: SCANF L_PAREN STRING COMMA EnderecoVar R_PAREN {$$ = new ast::AST_Node_Comando_Scanf($3, $5);};

ComandoExit: EXIT L_PAREN Expressao R_PAREN {$$ = new ast::AST_Node_Comando_Exit($3);};

ComandoReturn: RETURN L_PAREN CondicaoParada R_PAREN {$$ = new ast::AST_Node_Comando_Return($3);};

/* Scanf */

EnderecoVar: BITWISE_AND L_PAREN IDENTIFIER R_PAREN {$$ = new ast::AST_Node_Endereco_Var($3);};

/* Printf */

ExpressoesPrintf: Expressao ExpressoesPrintfTemporario {$$ = new ast::AST_Node_Expressoes_Printf($1, $2);};
                | {$$ = nullptr;};

ExpressoesPrintfTemporario: COMMA Expressao ExpressoesPrintfTemporario {$$ = new ast::AST_Node_Expressoes_Printf_Temporario($2, $3);};
                        | {$$ = nullptr;};
/* For */

InicializacaoFor: ASSIGN L_PAREN IDENTIFIER COMMA Expressao R_PAREN {$$ = new ast::AST_Node_Inicializacao_For($3, $5);};
                | {$$ = nullptr;};

CondicaoParada: Expressao {$$ = new ast::AST_Node_Condicao_Parada($1);};
                | {$$ = nullptr;};

AjusteValores: Expressao {$$ = new ast::AST_Node_Ajuste_Valores($1);};
                | {$$ = nullptr;};

/* EXPRESSOES */

Expressao: BOP {$$ = new ast::AST_Node_Expressao($1);};
        | UOP {$$ = new ast::AST_Node_Expressao($1);};
        | TOP {$$ = new ast::AST_Node_Expressao($1);};
        | ChamadaDeFuncao {$$ = new ast::AST_Node_Expressao($1);};
        | NUM_INTEGER {$$ = new ast::AST_Node_Expressao($1);};
        | CHARACTER {$$ = new ast::AST_Node_Expressao($1);};
        | STRING {$$ = new ast::AST_Node_Expressao($1);};

ChamadaDeFuncao: IDENTIFIER OpcoesExpressao {$$ = new ast::AST_Node_Chamada_Funcao($1, $2);};

OpcoesExpressao: L_PAREN LoopExpressoes R_PAREN { $$ = new ast::AST_Node_Opcoes_Expressao($2); }; // Funcao
            | L_SQUARE_BRACKET Expressao R_SQUARE_BRACKET LoopMatriz { $$ = new ast::AST_Node_Opcoes_Expressao($2, $4); }; // Vetor e/ou matriz
            | { $$ = nullptr; };

LoopExpressoes: Expressao LoopExpressoesTemporario { $$ = new ast::AST_Node_Loop_Expressoes($1, $2);};
            | { $$ = nullptr; };

LoopExpressoesTemporario: COMMA Expressao LoopExpressoesTemporario { $$ = new ast::AST_Node_Loop_Expressoes_Temporario($2, $3);};
            | { $$ = nullptr; };

LoopMatriz : L_SQUARE_BRACKET Expressao R_SQUARE_BRACKET LoopMatriz { $$ = new ast::AST_Node_Loop_Matriz($2, $4); };
            | { $$ = nullptr; };

BOP: PLUS L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("PLUS", $3, $5);
    };
    | MINUS L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("MINUS", $3, $5);
    };
    | MULTIPLY L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("MULTIPLY", $3, $5);
    };
    | DIV L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("DIV", $3, $5);
    };
    | REMAINDER L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("REMAINDER", $3, $5);
    };
    | BITWISE_AND L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("BITWISE_AND", $3, $5);
    };
    | BITWISE_OR L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("BITWISE_OR", $3, $5);
    };
    | BITWISE_XOR L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("BITWISE_XOR", $3, $5);
    };
    | LOGICAL_AND L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("LOGICAL_AND", $3, $5);
    };
    | LOGICAL_OR L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("LOGICAL_OR", $3, $5);
    };
    | EQUAL L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("EQUAL", $3, $5);
    };
    | NOT_EQUAL L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("NOT_EQUAL", $3, $5);
    };
    | LESS_THAN L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("LESS_THAN", $3, $5);
    };
    | GREATER_THAN L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("GREATER_THAN", $3, $5);
    };
    | LESS_EQUAL L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("LESS_EQUAL", $3, $5);
    };
    | GREATER_EQUAL L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("GREATER_EQUAL", $3, $5);
    };
    | R_SHIFT L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("R_SHIFT", $3, $5);
    };
    | L_SHIFT L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("L_SHIFT", $3, $5);
    };
    | ASSIGN L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("ASSIGN", $3, $5);
    };
    | ADD_ASSIGN L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("ADD_ASSIGN", $3, $5);
    };
    | MINUS_ASSIGN L_PAREN Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_BOP("MINUS_ASSIGN", $3, $5);
    };

UOP: PLUS  L_PAREN Expressao R_PAREN {
        $$ = new ast::AST_Node_UOP("PLUS", $3, false);
    };
    | MINUS L_PAREN Expressao R_PAREN {
        $$ = new ast::AST_Node_UOP("MINUS", $3, false);
    };
    | MULTIPLY L_PAREN Expressao R_PAREN {
        $$ = new ast::AST_Node_UOP("MULTIPLY", $3, false);
    };
    | INC L_PAREN Expressao R_PAREN {
        $$ = new ast::AST_Node_UOP("INC", $3, false);
    };
    | DEC L_PAREN Expressao R_PAREN {
        $$ = new ast::AST_Node_UOP("DEC", $3, false);
    };
    | BITWISE_NOT L_PAREN Expressao R_PAREN {
        $$ = new ast::AST_Node_UOP("BITWISE_NOT", $3, false);
    };
    | NOT L_PAREN Expressao R_PAREN {
        $$ = new ast::AST_Node_UOP("NOT", $3, false);
    };
    | L_PAREN Expressao R_PAREN INC {
        $$ = new ast::AST_Node_UOP("INC", $2, true);
    };
    | L_PAREN Expressao R_PAREN DEC {
        $$ = new ast::AST_Node_UOP("DEC", $2, true);
    };

TOP: TERNARY_CONDITIONAL L_PAREN Expressao COMMA Expressao COMMA Expressao R_PAREN {
        $$ = new ast::AST_Node_TOP($3, $5, $7);
    };

%%

int main(int argc, char **argv) {
    
    #ifdef YYDEBUG
        yydebug = 1;
    #endif

    yyparse();
    
}
