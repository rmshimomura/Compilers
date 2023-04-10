#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


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
    OpcoesExpressao,
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
class AST_Node_Opcoes_Expressao;
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

    AST_Node() {
    }
};

class AST_Node_BOP : public AST_Node {
   public:
    std::string opearation;
    AST_Node_Expressao* left;
    AST_Node_Expressao* right;

    AST_Node_BOP(std::string operation, AST_Node_Expressao* left, AST_Node_Expressao* right) {
        init();
        this->opearation = operation;
        this->left = left;
        this->right = right;
    }

   private:
    void init() {
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::BOP;
    }
};

class AST_Node_UOP : public AST_Node {
   public:
    std::string opearation;
    AST_Node_Expressao* child;
    int is_postfix;

    AST_Node_UOP(std::string operation, AST_Node_Expressao* child, int is_postfix) {
        init();
        this->opearation = operation;
        this->child = child;
        this->is_postfix = is_postfix;
    }

   private:
    void init() {
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::UOP;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::TOP;
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
    }

    AST_Node_Expressao(char character) {
        init();
        this->character = character;
    }

    AST_Node_Expressao(std::string* string) {
        init();
        this->string = string;
    }

   private:
    void init() {
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::Expressao;
    }
};

class AST_Node_Chamada_Funcao : public AST_Node {
   public:
    // First rule
    std::string* function_name;
    AST_Node_Opcoes_Expressao* opcoes_expressao;

    AST_Node_Chamada_Funcao(std::string* function_name, AST_Node_Opcoes_Expressao* opcoes_expressao) {
        init();
        this->function_name = function_name;
        this->opcoes_expressao = opcoes_expressao;
    }

    private:

    void init() {
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ChamadaFuncao;
    }
};

class AST_Node_Opcoes_Expressao : public AST_Node {
   public:
    // First rule
    AST_Node_Loop_Expressoes* loop_expressoes;

    // Second rule
    AST_Node_Expressao* expressao;
    AST_Node_Loop_Matriz* loop_matriz;

    AST_Node_Opcoes_Expressao(AST_Node_Loop_Expressoes* loop_expressoes) {
        init();
        this->loop_expressoes = loop_expressoes;
    }

    AST_Node_Opcoes_Expressao(AST_Node_Expressao* expressao, AST_Node_Loop_Matriz* loop_matriz) {
        init();
        this->expressao = expressao;
        this->loop_matriz = loop_matriz;
    }

    private:

        void init() {
            this->node_type = Node_Type::Non_Terminal;
            this->node_content = this;
            this->node_name = AST_Nonterminals::OpcoesExpressao;
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
    void init(){
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::LoopExpressoes;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::LoopExpressoesTemporario;
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
    void init(){
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::LoopMatriz;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::CondicaoParada;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::AjusteValores;
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
    void init(){
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::InicializacaoFor;
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
    void init(){
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ExpressoesPrintfTemporario;
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
    void init(){
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ExpressoesPrintf;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::EnderecoVar;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoReturn;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoExit;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoScanf;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoPrintf;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoFor;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoWhile;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoIf;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ComandoDoWhile;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::Comando;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ListaComandosTemporario;
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
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::ListaComandos;
    }
};

class AST_Node_Corpo_Funcao : public AST_Node {
   public:
    // First rule
    AST_Node_Lista_Comandos* lista_comandos;

    AST_Node_Corpo_Funcao(AST_Node_Lista_Comandos* lista_comandos) {
        init();
        this->lista_comandos = lista_comandos;
    }

    private:
    void init() {
        this->node_type = Node_Type::Non_Terminal;
        this->node_content = this;
        this->node_name = AST_Nonterminals::CorpoFuncao;
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
}