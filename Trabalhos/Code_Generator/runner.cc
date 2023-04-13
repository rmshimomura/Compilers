#include "ast_node.hh"

void ast::traversal::general_AST_available_functions(ast::AST_Function* function) {
    std::cout << "Function name: " << *function->function_name << std::endl;
    std::cout << "Return type: " << *function->return_type << std::endl;
    std::cout << "Parameters: " << std::endl;
    for (auto parameter : function->parameters) {
        std::cout << "Name: " << *(parameter->name) << " Type: " << *(parameter->type) << std::endl;
    }
    std::cout << "Variables: " << std::endl;
    for (auto variable : function->variables) {
        std::cout << "Name: " << *(variable->name) << " Type: " << *(variable->type) << " Value: " << (variable->value != nullptr ? *(variable->value) : "Not defined.") << std::endl;
    }
    std::cout << std::endl;
}

void ast::traversal::traversal_AST(ast::AST_Function* function) {
    

    // Open a file name test.dot
    // std::ofstream dotfile("test.dot");
    

    if (function->function_body == nullptr) {
        std::cout << "Function body is empty." << std::endl;
        return;
    }

    ast::traversal::traversal_CorpoFuncao(function->function_body);

}

void ast::traversal::traversal_BOP(ast::AST_Node_BOP* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->left);
    ast::traversal::traversal_Expressao(runner->right);

    std::cout << "BOP" << std::endl;
    

}

void ast::traversal::traversal_UOP(ast::AST_Node_UOP* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->child);

    std::cout << "UOP" << std::endl;

}

void ast::traversal::traversal_TOP(ast::AST_Node_TOP* runner) {
    
    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->test);
    ast::traversal::traversal_Expressao(runner->left);
    ast::traversal::traversal_Expressao(runner->right);

    std::cout << "TOP" << std::endl;

}

void ast::traversal::traversal_Expressao(ast::AST_Node_Expressao* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_BOP(runner->bop);
    ast::traversal::traversal_UOP(runner->uop);
    ast::traversal::traversal_TOP(runner->top);
    ast::traversal::traversal_ChamadaFuncao(runner->chamada_funcao);

    std::cout << "Expressao" << std::endl;

}

void ast::traversal::traversal_ChamadaFuncao(ast::AST_Node_Chamada_Funcao* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_OpcoesExpressao(runner->opcoes_expressao);

    std::cout << "funcao " << *(runner->function_name) << std::endl;

    return;

}

void ast::traversal::traversal_OpcoesExpressao(ast::AST_Node_Opcoes_Expressao* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_LoopExpressoes(runner->loop_expressoes);
    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_LoopMatriz(runner->loop_matriz);

    std::cout << "Opcoes Expressao" << std::endl;

}

void ast::traversal::traversal_LoopExpressoes(ast::AST_Node_Loop_Expressoes* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_LoopExpressoesTemporario(runner->loop_expressoes_temporario);

    std::cout << "Loop Expressoes" << std::endl;

}

void ast::traversal::traversal_LoopExpressoesTemporario(ast::AST_Node_Loop_Expressoes_Temporario* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_LoopExpressoesTemporario(runner->loop_expressoes_temporario);

    std::cout << "Loop Expressoes Temporario" << std::endl;

}

void ast::traversal::traversal_LoopMatriz(ast::AST_Node_Loop_Matriz* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_LoopMatriz(runner->loop_matriz);

    std::cout << "Loop Matriz" << std::endl;

}

void ast::traversal::traversal_CondicaoParada(ast::AST_Node_Condicao_Parada* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);

    std::cout << "Condicao Parada" << std::endl;

}

void ast::traversal::traversal_AjusteValores(ast::AST_Node_Ajuste_Valores* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);

    std::cout << "Ajuste Valores" << std::endl;

}

void ast::traversal::traversal_InicializacaoFor(ast::AST_Node_Inicializacao_For* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);

    std::cout << "Inicializacao For" << std::endl;

}

void ast::traversal::traversal_ExpressoesPrintfTemporario(ast::AST_Node_Expressoes_Printf_Temporario* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_ExpressoesPrintfTemporario(runner->expressoes_printf_temporario);

    std::cout << "Expressoes Printf Temporario" << std::endl;

}

void ast::traversal::traversal_ExpressoesPrintf(ast::AST_Node_Expressoes_Printf* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_ExpressoesPrintfTemporario(runner->expressoes_printf_temporario);

    std::cout << "Expressoes Printf" << std::endl;

}

void ast::traversal::traversal_ComandoReturn(ast::AST_Node_Comando_Return* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_CondicaoParada(runner->CondicaoParada);

    std::cout << "Comando Return" << std::endl;

}

void ast::traversal::traversal_ComandoExit(ast::AST_Node_Comando_Exit* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Expressao(runner->expressao);

    std::cout << "Comando Exit" << std::endl;

}

void ast::traversal::traversal_ComandoScanf(ast::AST_Node_Comando_Scanf* runner) {

    if(runner == nullptr) return;


    std::cout << "Comando Scanf" << std::endl;

}

void ast::traversal::traversal_ComandoPrintf(ast::AST_Node_Comando_Printf* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_ExpressoesPrintf(runner->expressoes_printf);

    std::cout << "Comando Printf" << std::endl;

}

void ast::traversal::traversal_ComandoFor(ast::AST_Node_Comando_For* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_InicializacaoFor(runner->inicializacao_for);
    ast::traversal::traversal_CondicaoParada(runner->condicao_parada);
    ast::traversal::traversal_AjusteValores(runner->ajuste_valores);
    ast::traversal::traversal_ListaComandos(runner->lista_comandos);

    std::cout << "Comando For" << std::endl;

}

void ast::traversal::traversal_ComandoWhile(ast::AST_Node_Comando_While* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_CondicaoParada(runner->condicao_parada);
    ast::traversal::traversal_ListaComandos(runner->lista_comandos);

    std::cout << "Comando While" << std::endl;

}

void ast::traversal::traversal_ComandoIf(ast::AST_Node_Comando_If* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_CondicaoParada(runner->condicao_parada);
    ast::traversal::traversal_ListaComandos(runner->lista_comandos_then);
    ast::traversal::traversal_ListaComandos(runner->lista_comandos_else);

    std::cout << "Comando If" << std::endl;

}

void ast::traversal::traversal_ComandoDoWhile(ast::AST_Node_Comando_Do_While* runner) {

    if(!runner) return;

    ast::traversal::traversal_ListaComandos(runner->lista_comandos);
    ast::traversal::traversal_CondicaoParada(runner->condicao_parada);

    std::cout << "Comando Do While" << std::endl;

}

void ast::traversal::traversal_Comando(ast::AST_Node_Comando* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_ComandoDoWhile(runner->comando_do_while);
    ast::traversal::traversal_ComandoIf(runner->comando_if);
    ast::traversal::traversal_ComandoWhile(runner->comando_while);
    ast::traversal::traversal_ComandoFor(runner->comando_for);
    ast::traversal::traversal_ComandoPrintf(runner->comando_printf);
    ast::traversal::traversal_ComandoScanf(runner->comando_scanf);
    ast::traversal::traversal_ComandoExit(runner->comando_exit);
    ast::traversal::traversal_ComandoReturn(runner->comando_return);

    std::cout << "Comando" << std::endl;

}

void ast::traversal::traversal_ListaComandosTemporario(ast::AST_Node_Lista_Comandos_Temporario* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Comando(runner->comando);
    ast::traversal::traversal_ListaComandosTemporario(runner->lista_comandos_temporario);

    std::cout << "Lista Comandos Temporario" << std::endl;

}

void ast::traversal::traversal_ListaComandos(ast::AST_Node_Lista_Comandos* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_Comando(runner->comando);
    ast::traversal::traversal_ListaComandosTemporario(runner->lista_comandos_temporario);

    std::cout << "Lista Comandos" << std::endl;

}

void ast::traversal::traversal_CorpoFuncao(ast::AST_Node_Corpo_Funcao* runner) {

    if(runner == nullptr) return;

    ast::traversal::traversal_ListaComandos(runner->lista_comandos);

    std::cout << "Corpo Funcao" << std::endl;

}