#ifndef AST_NODE_HH
#define AST_NODE_HH

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace ast {

/*
enum AST_Terminals {
    AST,
    VOID,
    INT,
    CHAR,
    RETURN,
    GLOBAL,
    VARIABLE,
    TYPE,
    FUNCTION,
    END_FUNCTION,
    PARAMETER,
    RETURN_TYPE,
    CONSTANT,
    IF,
    VALUE,
    WHILE,
    FOR,
    DO_WHILE,
    PRINTF,
    SCANF,
    EXIT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIV,
    REMAINDER,
    INC,
    DEC,
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_NOT,
    BITWISE_XOR,
    NOT,
    LOGICAL_AND,
    LOGICAL_OR,
    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_EQUAL,
    GREATER_EQUAL,
    R_SHIFT,
    L_SHIFT,
    ASSIGN,
    ADD_ASSIGN,
    MINUS_ASSIGN,
    SEMICOLON,
    COMMA,
    COLON,
    L_PAREN,
    R_PAREN,
    L_SQUARE_BRACKET,
    R_SQUARE_BRACKET,
    TERNARY_CONDITIONAL,
    START_ARROW,
    IDENTIFIER,
    NUM_INTEGER,
    STRING,
    CHARACTER,
    NEWLINE
};
*/
enum AST_Nonterminals {
    Programa,
    ConsumirNovasLinhas,
    Declaracoes,
    DeclaraConstante,
    DeclaraVariavelGlobal,
    TipoDeVariavel,
    TamanhoVariavel,
    LoopColchetes,
    LoopPonteirosTemporario,
    DeclaraFuncao,
    ParametrosDeFuncao,
    DeclararVariaveisLocais,
    CorpoFuncao,
    ListaComandos,
    ListaComandosTemporario,
    Comando,
    LoopExpressoes,
    LoopExpressoesTemporario,
    ComandoDoWhile,
    ComandoIf,
    ComandoWhile,
    ComandoFor,
    ComandoPrintf,
    ComandoScanf,
    ComandoExit,
    ComandoReturn,
    EnderecoVar,
    ExpressoesPrintf,
    ExpressoesPrintfTemporario,
    InicializacaoFor,
    CondicaoParada,
    AjusteValores,
    Expressao,
    ChamadaFuncao,
    AcessoVariavel,
    LoopMatriz,
    BOP,
    UOP,
    TOP
};

enum Node_Type {
    Terminal,
    Non_Terminal
};

class AST_Node;
class AST_Node_BOP;
class AST_Node_UOP;
class AST_Node_TOP;
class AST_Node_Expressao;
class AST_Node_Chamada_Funcao;
class AST_Node_Acesso_Variavel;
class AST_Node_Loop_Expressoes;
class AST_Node_Loop_Expressoes_Temporario;
class AST_Node_Loop_Matriz;
class AST_Node_Condicao_Parada;
class AST_Node_Ajuste_Valores;
class AST_Node_Inicializacao_For;
class AST_Node_Expressoes_Printf_Temporario;
class AST_Node_Expressoes_Printf;
class AST_Node_Endereco_Var;
class AST_Node_Comando_Return;
class AST_Node_Comando_Exit;
class AST_Node_Comando_Scanf;
class AST_Node_Comando_Printf;
class AST_Node_Comando_For;
class AST_Node_Comando_While;
class AST_Node_Comando_If;
class AST_Node_Comando_Do_While;
class AST_Node_Comando;
class AST_Node_Lista_Comandos_Temporario;
class AST_Node_Lista_Comandos;
class AST_Node_Corpo_Funcao;
class AST_Variable;
class AST_Constant;
class AST_Parameter;
class AST_Function;

class AST_Node {
   public:
    void* node_content;
    Node_Type node_type;
    int node_name;
    AST_Node* parent;
    int node_number;

    AST_Node() {
    }
};

class AST_Node_BOP : public AST_Node {
   public:
    std::string operation;
    AST_Node_Expressao* left;
    AST_Node_Expressao* right;

    AST_Node_BOP(std::string operation, AST_Node_Expressao* left, AST_Node_Expressao* right) {
        init();
        this->operation = operation;
        this->left = left;
        this->right = right;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::BOP;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class AST_Node_UOP : public AST_Node {
   public:
    std::string operation;
    AST_Node_Expressao* child;
    int is_postfix;

    AST_Node_UOP(std::string operation, AST_Node_Expressao* child, int is_postfix) {
        init();
        this->operation = operation;
        this->child = child;
        this->is_postfix = is_postfix;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::UOP;
        this->child = nullptr;
    }
};

class AST_Node_TOP : public AST_Node {
   public:
    AST_Node_Expressao* test;
    AST_Node_Expressao* left;
    AST_Node_Expressao* right;

    AST_Node_TOP(AST_Node_Expressao* test, AST_Node_Expressao* left, AST_Node_Expressao* right) {
        init();
        this->test = test;
        this->left = left;
        this->right = right;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::TOP;
        this->test = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class AST_Node_Expressao : public AST_Node {
   public:
    // First rule
    AST_Node_BOP* bop;

    // Second rule
    AST_Node_UOP* uop;

    // Third rule
    AST_Node_TOP* top;

    // Fourth rule
    AST_Node_Chamada_Funcao* chamada_funcao;

    // Fifth rule
    int num_int;

    // Sixth rule
    char character;

    // Seventh rule
    std::string* string;

    int using_int;

    AST_Node_Acesso_Variavel* acesso_variavel;

    AST_Node_Expressao(AST_Node_BOP* bop) {
        init();
        this->bop = bop;
    }

    AST_Node_Expressao(AST_Node_UOP* uop) {
        init();
        this->uop = uop;
    }

    AST_Node_Expressao(AST_Node_TOP* top) {
        init();
        this->top = top;
    }

    AST_Node_Expressao(AST_Node_Chamada_Funcao* chamada_funcao) {
        init();
        this->chamada_funcao = chamada_funcao;
    }

    AST_Node_Expressao(int num_int) {
        init();
        this->num_int = num_int;
        this->using_int = 1;
    }

    AST_Node_Expressao(char character) {
        init();
        this->character = character;
    }

    AST_Node_Expressao(std::string* string) {
        init();
        this->string = string;
    }

    AST_Node_Expressao(AST_Node_Acesso_Variavel* acesso_variavel) {
        init();
        this->acesso_variavel = acesso_variavel;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::Expressao;
        this->bop = nullptr;
        this->uop = nullptr;
        this->top = nullptr;
        this->chamada_funcao = nullptr;
        this->num_int = -1;
        this->character = 0;
        this->string = nullptr;
        this->acesso_variavel = nullptr;
        this->using_int = 0;
    }
};

class AST_Node_Chamada_Funcao : public AST_Node {
   public:
    // First rule
    std::string* function_name;
    AST_Node_Loop_Expressoes* loop_expressoes;

    AST_Node_Chamada_Funcao(std::string* function_name, AST_Node_Loop_Expressoes* loop_expressoes) {
        init();
        this->function_name = function_name;
        this->loop_expressoes = loop_expressoes;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ChamadaFuncao;
        this->function_name = nullptr;
        this->loop_expressoes = nullptr;
    }
};

class AST_Node_Acesso_Variavel : public AST_Node {
   public:
    // First rule
    std::string* variable_name;

    // Second rule
    AST_Node_Loop_Matriz* loop_matriz;

    AST_Node_Acesso_Variavel(std::string* variable_name, AST_Node_Loop_Matriz* loop_matriz) {
        init();
        this->variable_name = variable_name;
        this->loop_matriz = loop_matriz;
    }

    AST_Node_Acesso_Variavel(std::string* variable_name) {
        init();
        this->variable_name = variable_name;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::AcessoVariavel;
        this->variable_name = nullptr;
        this->loop_matriz = nullptr;
    }
};

class AST_Node_Loop_Expressoes : public AST_Node {
   public:
    // First rule
    AST_Node_Expressao* expressao;
    AST_Node_Loop_Expressoes_Temporario* loop_expressoes_temporario;

    AST_Node_Loop_Expressoes(AST_Node_Expressao* expressao, AST_Node_Loop_Expressoes_Temporario* loop_expressoes_temporario) {
        init();
        this->expressao = expressao;
        this->loop_expressoes_temporario = loop_expressoes_temporario;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::LoopExpressoes;
        this->expressao = nullptr;
        this->loop_expressoes_temporario = nullptr;
    }
};

class AST_Node_Loop_Expressoes_Temporario : public AST_Node {
   public:
    AST_Node_Expressao* expressao;
    AST_Node_Loop_Expressoes_Temporario* loop_expressoes_temporario;

    AST_Node_Loop_Expressoes_Temporario(AST_Node_Expressao* expressao, AST_Node_Loop_Expressoes_Temporario* loop_expressoes_temporario) {
        init();
        this->expressao = expressao;
        this->loop_expressoes_temporario = loop_expressoes_temporario;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::LoopExpressoesTemporario;
        this->expressao = nullptr;
        this->loop_expressoes_temporario = nullptr;
    }
};

class AST_Node_Loop_Matriz : public AST_Node {
   public:
    AST_Node_Expressao* expressao;
    AST_Node_Loop_Matriz* loop_matriz;

    AST_Node_Loop_Matriz(AST_Node_Expressao* expressao, AST_Node_Loop_Matriz* loop_matriz) {
        init();
        this->expressao = expressao;
        this->loop_matriz = loop_matriz;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::LoopMatriz;
        this->expressao = nullptr;
        this->loop_matriz = nullptr;
    }
};

class AST_Node_Condicao_Parada : public AST_Node {
   public:
    // First rule
    AST_Node_Expressao* expressao;

    AST_Node_Condicao_Parada(AST_Node_Expressao* expressao) {
        init();
        this->expressao = expressao;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::CondicaoParada;
        this->expressao = nullptr;
    }
};

class AST_Node_Ajuste_Valores : public AST_Node {
   public:
    // First rule
    AST_Node_Expressao* expressao;

    AST_Node_Ajuste_Valores(AST_Node_Expressao* expressao) {
        init();
        this->expressao = expressao;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::AjusteValores;
        this->expressao = nullptr;
    }
};

class AST_Node_Inicializacao_For : public AST_Node {
   public:
    // First rule
    AST_Node_Expressao* expressao;
    std::string* identifier;

    AST_Node_Inicializacao_For(std::string* identifier, AST_Node_Expressao* expressao) {
        init();
        this->expressao = expressao;
        this->identifier = identifier;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::InicializacaoFor;
        this->expressao = nullptr;
        this->identifier = nullptr;
    }
};

class AST_Node_Expressoes_Printf_Temporario : public AST_Node {
   public:
    // First rule
    AST_Node_Expressao* expressao;
    AST_Node_Expressoes_Printf_Temporario* expressoes_printf_temporario;

    AST_Node_Expressoes_Printf_Temporario(AST_Node_Expressao* expressao, AST_Node_Expressoes_Printf_Temporario* expressoes_printf_temporario) {
        init();
        this->expressao = expressao;
        this->expressoes_printf_temporario = expressoes_printf_temporario;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ExpressoesPrintfTemporario;
        this->expressao = nullptr;
        this->expressoes_printf_temporario = nullptr;
    }
};

class AST_Node_Expressoes_Printf : public AST_Node {
   public:
    // First rule
    AST_Node_Expressao* expressao;
    AST_Node_Expressoes_Printf_Temporario* expressoes_printf_temporario;

    AST_Node_Expressoes_Printf(AST_Node_Expressao* expressao, AST_Node_Expressoes_Printf_Temporario* expressoes_printf_temporario) {
        init();
        this->expressao = expressao;
        this->expressoes_printf_temporario = expressoes_printf_temporario;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ExpressoesPrintf;
        this->expressao = nullptr;
        this->expressoes_printf_temporario = nullptr;
    }
};

class AST_Node_Endereco_Var : public AST_Node {
   public:
    // First rule
    std::string* identifier;

    AST_Node_Endereco_Var(std::string* identifier) {
        init();
        this->identifier = identifier;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::EnderecoVar;
        this->identifier = nullptr;
    }
};

class AST_Node_Comando_Return : public AST_Node {
   public:
    // First rule
    AST_Node_Condicao_Parada* CondicaoParada;

    AST_Node_Comando_Return(AST_Node_Condicao_Parada* CondicaoParada) {
        init();
        this->CondicaoParada = CondicaoParada;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoReturn;
        this->CondicaoParada = nullptr;
    }
};

class AST_Node_Comando_Exit : public AST_Node {
   public:
    // First rule
    AST_Node_Expressao* expressao;

    AST_Node_Comando_Exit(AST_Node_Expressao* expressao) {
        init();
        this->expressao = expressao;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoExit;
        this->expressao = nullptr;
    }
};

class AST_Node_Comando_Scanf : public AST_Node {
   public:
    // First rule
    std::string* string;
    AST_Node_Endereco_Var* endereco_var;

    AST_Node_Comando_Scanf(std::string* string, AST_Node_Endereco_Var* endereco_var) {
        init();
        this->string = string;
        this->endereco_var = endereco_var;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoScanf;
        this->string = nullptr;
        this->endereco_var = nullptr;
    }
};

class AST_Node_Comando_Printf : public AST_Node {
   public:
    // First rule
    AST_Node_Expressoes_Printf* expressoes_printf;

    // First and second rule
    std::string* string;

    AST_Node_Comando_Printf(std::string* string, AST_Node_Expressoes_Printf* expressoes_printf) {
        init();
        this->string = string;
        this->expressoes_printf = expressoes_printf;
    }

    AST_Node_Comando_Printf(std::string* string) {
        init();
        this->string = string;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoPrintf;
        this->string = nullptr;
        this->expressoes_printf = nullptr;
    }
};

class AST_Node_Comando_For : public AST_Node {
   public:
    // First rule
    AST_Node_Inicializacao_For* inicializacao_for;
    AST_Node_Condicao_Parada* condicao_parada;
    AST_Node_Ajuste_Valores* ajuste_valores;
    AST_Node_Lista_Comandos* lista_comandos;

    AST_Node_Comando_For(AST_Node_Inicializacao_For* inicializacao_for, AST_Node_Condicao_Parada* condicao_parada, AST_Node_Ajuste_Valores* ajuste_valores, AST_Node_Lista_Comandos* lista_comandos) {
        init();
        this->inicializacao_for = inicializacao_for;
        this->condicao_parada = condicao_parada;
        this->ajuste_valores = ajuste_valores;
        this->lista_comandos = lista_comandos;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoFor;
        this->inicializacao_for = nullptr;
        this->condicao_parada = nullptr;
        this->ajuste_valores = nullptr;
        this->lista_comandos = nullptr;
    }
};

class AST_Node_Comando_While : public AST_Node {
   public:
    // First rule
    AST_Node_Condicao_Parada* condicao_parada;
    AST_Node_Lista_Comandos* lista_comandos;

    AST_Node_Comando_While(AST_Node_Condicao_Parada* condicao_parada, AST_Node_Lista_Comandos* lista_comandos) {
        init();
        this->condicao_parada = condicao_parada;
        this->lista_comandos = lista_comandos;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoWhile;
        this->condicao_parada = nullptr;
        this->lista_comandos = nullptr;
    }
};

class AST_Node_Comando_If : public AST_Node {
   public:
    // First and second rule
    AST_Node_Condicao_Parada* condicao_parada;
    AST_Node_Lista_Comandos* lista_comandos_then;
    AST_Node_Lista_Comandos* lista_comandos_else;

    AST_Node_Comando_If(AST_Node_Condicao_Parada* condicao_parada, AST_Node_Lista_Comandos* lista_comandos_then, AST_Node_Lista_Comandos* lista_comandos_else) {
        init();
        this->condicao_parada = condicao_parada;
        this->lista_comandos_then = lista_comandos_then;
        this->lista_comandos_else = lista_comandos_else;
    }

    AST_Node_Comando_If(AST_Node_Condicao_Parada* condicao_parada, AST_Node_Lista_Comandos* lista_comandos_then) {
        init();
        this->condicao_parada = condicao_parada;
        this->lista_comandos_then = lista_comandos_then;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoIf;
        this->condicao_parada = nullptr;
        this->lista_comandos_then = nullptr;
        this->lista_comandos_else = nullptr;
    }
};

class AST_Node_Comando_Do_While : public AST_Node {
   public:
    // First rule
    AST_Node_Lista_Comandos* lista_comandos;
    AST_Node_Condicao_Parada* condicao_parada;

    AST_Node_Comando_Do_While(AST_Node_Lista_Comandos* lista_comandos, AST_Node_Condicao_Parada* condicao_parada) {
        init();
        this->lista_comandos = lista_comandos;
        this->condicao_parada = condicao_parada;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoDoWhile;
        this->lista_comandos = nullptr;
        this->condicao_parada = nullptr;
    }
};

class AST_Node_Comando : public AST_Node {
   public:
    // First rule
    AST_Node_Comando_Do_While* comando_do_while;

    // Second rule
    AST_Node_Comando_If* comando_if;

    // Third rule
    AST_Node_Comando_While* comando_while;

    // Fourth rule
    AST_Node_Comando_For* comando_for;

    // Fifth rule
    AST_Node_Comando_Printf* comando_printf;

    // Sixth rule
    AST_Node_Comando_Scanf* comando_scanf;

    // Seventh rule
    AST_Node_Comando_Exit* comando_exit;

    // Eighth rule
    AST_Node_Comando_Return* comando_return;

    // Ninth rule
    AST_Node_Expressao* expressao;

    AST_Node_Comando(AST_Node_Comando_Do_While* comando_do_while) {
        init();
        this->comando_do_while = comando_do_while;
    }

    AST_Node_Comando(AST_Node_Comando_If* comando_if) {
        init();
        this->comando_if = comando_if;
    }

    AST_Node_Comando(AST_Node_Comando_While* comando_while) {
        init();
        this->comando_while = comando_while;
    }

    AST_Node_Comando(AST_Node_Comando_For* comando_for) {
        init();
        this->comando_for = comando_for;
    }

    AST_Node_Comando(AST_Node_Comando_Printf* comando_printf) {
        init();
        this->comando_printf = comando_printf;
    }

    AST_Node_Comando(AST_Node_Comando_Scanf* comando_scanf) {
        init();
        this->comando_scanf = comando_scanf;
    }

    AST_Node_Comando(AST_Node_Comando_Exit* comando_exit) {
        init();
        this->comando_exit = comando_exit;
    }

    AST_Node_Comando(AST_Node_Comando_Return* comando_return) {
        init();
        this->comando_return = comando_return;
    }

    AST_Node_Comando(AST_Node_Expressao* expressao) {
        init();
        this->expressao = expressao;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::Comando;
        this->comando_do_while = nullptr;
        this->comando_if = nullptr;
        this->comando_while = nullptr;
        this->comando_for = nullptr;
        this->comando_printf = nullptr;
        this->comando_scanf = nullptr;
        this->comando_exit = nullptr;
        this->comando_return = nullptr;
        this->expressao = nullptr;
    }
};

class AST_Node_Lista_Comandos_Temporario : public AST_Node {
   public:
    // First rule
    AST_Node_Comando* comando;
    AST_Node_Lista_Comandos_Temporario* lista_comandos_temporario;

    AST_Node_Lista_Comandos_Temporario(AST_Node_Comando* comando, AST_Node_Lista_Comandos_Temporario* lista_comandos_temporario) {
        init();
        this->comando = comando;
        this->lista_comandos_temporario = lista_comandos_temporario;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ListaComandosTemporario;
        this->comando = nullptr;
        this->lista_comandos_temporario = nullptr;
    }
};

class AST_Node_Lista_Comandos : public AST_Node {
   public:
    // First rule
    AST_Node_Comando* comando;
    AST_Node_Lista_Comandos_Temporario* lista_comandos_temporario;

    AST_Node_Lista_Comandos(AST_Node_Comando* comando, AST_Node_Lista_Comandos_Temporario* lista_comandos_temporario) {
        init();
        this->comando = comando;
        this->lista_comandos_temporario = lista_comandos_temporario;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ListaComandos;
        this->comando = nullptr;
        this->lista_comandos_temporario = nullptr;
    }
};

class AST_Node_Corpo_Funcao : public AST_Node {
   public:
    // First rule
    AST_Node_Lista_Comandos* lista_comandos;
    std::string* function_name;

    AST_Node_Corpo_Funcao(AST_Node_Lista_Comandos* lista_comandos) {
        init();
        this->lista_comandos = lista_comandos;
    }

   private:
    void init() {
        this->node_number = -1;
        this->parent = nullptr;
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::CorpoFuncao;
        this->lista_comandos = nullptr;
        this->function_name = nullptr;
    }
};

class AST_Variable {
   public:
    std::string* name;
    std::string* type;
    std::string* value;

    AST_Variable(std::string* name, std::string* type, std::string* value) {
        this->name = name;
        this->type = type;
        this->value = value;
    }

    AST_Variable(std::string* name, std::string* type) {
        this->name = name;
        this->type = type;
        this->value = nullptr;
    }
};

class AST_Constant {
   public:
    std::string* name;
    int value;

    AST_Constant(std::string* name, int value) {
        this->name = name;
        this->value = value;
    }
};

class AST_Parameter {
   public:
    std::string* name;
    std::string* type;

    AST_Parameter(std::string* name, std::string* type) {
        this->name = name;
        this->type = type;
    }
};

class AST_Function {
   public:
    std::string* function_name;
    std::string* return_type;
    std::vector<AST_Parameter*> parameters;
    std::vector<AST_Variable*> variables;
    AST_Node_Corpo_Funcao* function_body;

    AST_Function(std::string* function_name, std::string* return_type) {
        this->function_name = function_name;
        this->return_type = return_type;
    }

    void add_parameter(AST_Parameter* parameter) {
        this->parameters.push_back(parameter);
    }

    void add_variable(AST_Variable* variable) {
        this->variables.push_back(variable);
    }

    void set_function_body(AST_Node_Corpo_Funcao* function_body) {
        this->function_body = function_body;
    }
};

namespace traversal {
    
    void general_AST_available_functions(ast::AST_Function* function);
    void traversal_AST(ast::AST_Function* function);
    void print_ASTs(std::vector<ast::AST_Function*> funcoes);

    void traversal_BOP(ast::AST_Node_BOP* runner);
    void traversal_UOP(ast::AST_Node_UOP* runner);
    void traversal_TOP(ast::AST_Node_TOP* runner);
    void traversal_Expressao(ast::AST_Node_Expressao* runner);
    void traversal_ChamadaFuncao(ast::AST_Node_Chamada_Funcao* runner);
    void traversal_AcessoVariavel(ast::AST_Node_Acesso_Variavel* runner);
    void traversal_LoopExpressoes(ast::AST_Node_Loop_Expressoes* runner);
    void traversal_LoopExpressoesTemporario(ast::AST_Node_Loop_Expressoes_Temporario* runner);
    void traversal_LoopMatriz(ast::AST_Node_Loop_Matriz* runner);
    void traversal_CondicaoParada(ast::AST_Node_Condicao_Parada* runner);
    void traversal_AjusteValores(ast::AST_Node_Ajuste_Valores* runner);
    void traversal_InicializacaoFor(ast::AST_Node_Inicializacao_For* runner);
    void traversal_ExpressoesPrintfTemporario(ast::AST_Node_Expressoes_Printf_Temporario* runner);
    void traversal_ExpressoesPrintf(ast::AST_Node_Expressoes_Printf* runner);
    void traversal_EnderecoVar(ast::AST_Node_Endereco_Var* runner);
    void traversal_ComandoReturn(ast::AST_Node_Comando_Return* runner);
    void traversal_ComandoExit(ast::AST_Node_Comando_Exit* runner);
    void traversal_ComandoScanf(ast::AST_Node_Comando_Scanf* runner);
    void traversal_ComandoPrintf(ast::AST_Node_Comando_Printf* runner);
    void traversal_ComandoFor(ast::AST_Node_Comando_For* runner);
    void traversal_ComandoWhile(ast::AST_Node_Comando_While* runner);
    void traversal_ComandoIf(ast::AST_Node_Comando_If* runner);
    void traversal_ComandoDoWhile(ast::AST_Node_Comando_Do_While* runner);
    void traversal_Comando(ast::AST_Node_Comando* runner);
    void traversal_ListaComandosTemporario(ast::AST_Node_Lista_Comandos_Temporario* runner);
    void traversal_ListaComandos(ast::AST_Node_Lista_Comandos* runner);
    void traversal_CorpoFuncao(ast::AST_Node_Corpo_Funcao* runner);

};  

};

#endif  // AST_H