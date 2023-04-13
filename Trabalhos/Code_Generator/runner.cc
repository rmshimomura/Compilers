#include "ast_node.hh"

std::ofstream dotfile("test.dot");
int node_counter = 0;

void ast::traversal::print_ASTs(std::vector<ast::AST_Function*> funcoes) {

    dotfile << "digraph ARV {" << std::endl;
    dotfile << "graph [pad=\"0.5\", nodesep=\"0.5\", ranksep=\"2\"];" << std::endl;

    for (auto function : funcoes) {
        ast::traversal::traversal_AST(function);
    }

    dotfile << "}" << std::endl;
    dotfile.close();
}

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
    if (function->function_body == nullptr) {
        std::cout << "Function body is empty." << std::endl;
        return;
    }

    function->function_body->function_name = function->function_name;

    ast::traversal::traversal_CorpoFuncao(function->function_body);

    
}

void ast::traversal::traversal_BOP(ast::AST_Node_BOP* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->left);
    ast::traversal::traversal_Expressao(runner->right);

    if (runner->left != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->left->node_number << ";" << std::endl;
    }

    if (runner->right != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->right->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \"" << runner->operation << "\"];" << std::endl;

    // std::cout << "BOP: " << runner->operation << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_UOP(ast::AST_Node_UOP* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->child);

    if (runner->child != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->child->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \"" << runner->operation << "\"];" << std::endl;

    // std::cout << "UOP: " << runner->operation << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_TOP(ast::AST_Node_TOP* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->test);
    ast::traversal::traversal_Expressao(runner->left);
    ast::traversal::traversal_Expressao(runner->right);

    if (runner->test != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->test->node_number << ";" << std::endl;
    }

    if (runner->left != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->left->node_number << ";" << std::endl;
    }

    if (runner->right != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->right->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "?"
            << "\"];" << std::endl;

    // std::cout << "TOP" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_Expressao(ast::AST_Node_Expressao* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_BOP(runner->bop);
    ast::traversal::traversal_UOP(runner->uop);
    ast::traversal::traversal_TOP(runner->top);
    ast::traversal::traversal_ChamadaFuncao(runner->chamada_funcao);
    ast::traversal::traversal_AcessoVariavel(runner->acesso_variavel);

    if (runner->bop != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->bop->node_number << ";" << std::endl;
    }

    if (runner->uop != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->uop->node_number << ";" << std::endl;
    }

    if (runner->top != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->top->node_number << ";" << std::endl;
    }

    if (runner->chamada_funcao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->chamada_funcao->node_number << ";" << std::endl;
    }

    if (runner->acesso_variavel != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->acesso_variavel->node_number << ";" << std::endl;
    }

    std::string variable;

    if (runner->string != nullptr) {
        variable = std::string(*(runner->string));
    } else if (runner->character != 0) {
        variable = std::string(1, runner->character);
    } else if (runner->using_int) {
        variable = std::to_string(runner->num_int);
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Expressão\n"
            << variable
            << "\"];" << std::endl;

    // std::cout << "Expressao" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ChamadaFuncao(ast::AST_Node_Chamada_Funcao* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_LoopExpressoes(runner->loop_expressoes);

    if (runner->loop_expressoes != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->loop_expressoes->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \"Chamada Funcao " << *(runner->function_name) << "\"];" << std::endl;

    // std::cout << "funcao " << *(runner->function_name) << " Node number = " << runner->node_number << std::endl;

    return;
}

void ast::traversal::traversal_AcessoVariavel(ast::AST_Node_Acesso_Variavel* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_LoopMatriz(runner->loop_matriz);

    if (runner->loop_matriz != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->loop_matriz->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \"Acesso Variavel " << *(runner->variable_name) << "\"];" << std::endl;

    // std::cout << "Acesso Variavel: " << *(runner->variable_name) << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_LoopExpressoes(ast::AST_Node_Loop_Expressoes* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_LoopExpressoesTemporario(runner->loop_expressoes_temporario);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    if (runner->loop_expressoes_temporario != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->loop_expressoes_temporario->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Loop Expressoes"
            << "\"];" << std::endl;

    // std::cout << "Loop Expressoes" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_LoopExpressoesTemporario(ast::AST_Node_Loop_Expressoes_Temporario* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_LoopExpressoesTemporario(runner->loop_expressoes_temporario);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    if (runner->loop_expressoes_temporario != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->loop_expressoes_temporario->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Loop Expressoes Temporario"
            << "\"];" << std::endl;

    // std::cout << "Loop Expressoes Temporario" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_LoopMatriz(ast::AST_Node_Loop_Matriz* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_LoopMatriz(runner->loop_matriz);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    if (runner->loop_matriz != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->loop_matriz->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Loop Matriz"
            << "\"];" << std::endl;

    // std::cout << "Loop Matriz" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_CondicaoParada(ast::AST_Node_Condicao_Parada* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Condicao Parada"
            << "\"];" << std::endl;

    // std::cout << "Condicao Parada" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_AjusteValores(ast::AST_Node_Ajuste_Valores* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Ajuste Valores"
            << "\"];" << std::endl;

    // std::cout << "Ajuste Valores" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_InicializacaoFor(ast::AST_Node_Inicializacao_For* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Inicializacao For"
            << "\"];" << std::endl;

    // std::cout << "Inicializacao For" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ExpressoesPrintfTemporario(ast::AST_Node_Expressoes_Printf_Temporario* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_ExpressoesPrintfTemporario(runner->expressoes_printf_temporario);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    if (runner->expressoes_printf_temporario != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressoes_printf_temporario->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Expressoes Printf Temporario"
            << "\"];" << std::endl;

    // std::cout << "Expressoes Printf Temporario" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ExpressoesPrintf(ast::AST_Node_Expressoes_Printf* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_ExpressoesPrintfTemporario(runner->expressoes_printf_temporario);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    if (runner->expressoes_printf_temporario != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressoes_printf_temporario->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Expressoes Printf"
            << "\"];" << std::endl;

    // std::cout << "Expressoes Printf" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_EnderecoVar(ast::AST_Node_Endereco_Var* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \"" << *(runner->identifier) << "\"];" << std::endl;

    // std::cout << "Endereco Var " << *(runner->identifier) << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ComandoReturn(ast::AST_Node_Comando_Return* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_CondicaoParada(runner->CondicaoParada);

    if (runner->CondicaoParada != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->CondicaoParada->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando Return"
            << "\"];" << std::endl;

    // std::cout << "Comando Return" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ComandoExit(ast::AST_Node_Comando_Exit* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando Exit"
            << "\"];" << std::endl;

    // std::cout << "Comando Exit" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ComandoScanf(ast::AST_Node_Comando_Scanf* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_EnderecoVar(runner->endereco_var);

    if (runner->endereco_var != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->endereco_var->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando Scanf"
            << "\"];" << std::endl;

    // std::cout << "Comando Scanf" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ComandoPrintf(ast::AST_Node_Comando_Printf* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_ExpressoesPrintf(runner->expressoes_printf);

    if (runner->expressoes_printf != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressoes_printf->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando Printf \n"
            << runner->string->substr(1, runner->string->size() - 2)
            << "\"];" << std::endl;

    // std::cout << "Comando Printf" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ComandoFor(ast::AST_Node_Comando_For* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_InicializacaoFor(runner->inicializacao_for);
    ast::traversal::traversal_CondicaoParada(runner->condicao_parada);
    ast::traversal::traversal_AjusteValores(runner->ajuste_valores);
    ast::traversal::traversal_ListaComandos(runner->lista_comandos);

    if (runner->inicializacao_for != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->inicializacao_for->node_number << ";" << std::endl;
    }

    if (runner->condicao_parada != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->condicao_parada->node_number << ";" << std::endl;
    }

    if (runner->ajuste_valores != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->ajuste_valores->node_number << ";" << std::endl;
    }

    if (runner->lista_comandos != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando For"
            << "\"];" << std::endl;

    // std::cout << "Comando For" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ComandoWhile(ast::AST_Node_Comando_While* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_CondicaoParada(runner->condicao_parada);
    ast::traversal::traversal_ListaComandos(runner->lista_comandos);

    if (runner->condicao_parada != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->condicao_parada->node_number << ";" << std::endl;
    }

    if (runner->lista_comandos != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando While"
            << "\"];" << std::endl;

    // std::cout << "Comando While" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ComandoIf(ast::AST_Node_Comando_If* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_CondicaoParada(runner->condicao_parada);
    ast::traversal::traversal_ListaComandos(runner->lista_comandos_then);
    ast::traversal::traversal_ListaComandos(runner->lista_comandos_else);

    if (runner->condicao_parada != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->condicao_parada->node_number << ";" << std::endl;
    }

    if (runner->lista_comandos_then != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos_then->node_number << ";" << std::endl;
    }

    if (runner->lista_comandos_else != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos_else->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando If"
            << "\"];" << std::endl;

    // std::cout << "Comando If" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ComandoDoWhile(ast::AST_Node_Comando_Do_While* runner) {
    if (!runner) return;

    ast::traversal::traversal_ListaComandos(runner->lista_comandos);
    ast::traversal::traversal_CondicaoParada(runner->condicao_parada);

    if (runner->condicao_parada != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->condicao_parada->node_number << ";" << std::endl;
    }

    if (runner->lista_comandos != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando Do While"
            << "\"];" << std::endl;

    // std::cout << "Comando Do While" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_Comando(ast::AST_Node_Comando* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Expressao(runner->expressao);
    ast::traversal::traversal_ComandoDoWhile(runner->comando_do_while);
    ast::traversal::traversal_ComandoIf(runner->comando_if);
    ast::traversal::traversal_ComandoWhile(runner->comando_while);
    ast::traversal::traversal_ComandoFor(runner->comando_for);
    ast::traversal::traversal_ComandoPrintf(runner->comando_printf);
    ast::traversal::traversal_ComandoScanf(runner->comando_scanf);
    ast::traversal::traversal_ComandoExit(runner->comando_exit);
    ast::traversal::traversal_ComandoReturn(runner->comando_return);

    if (runner->expressao != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
    }

    if (runner->comando_do_while != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando_do_while->node_number << ";" << std::endl;
    }

    if (runner->comando_if != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando_if->node_number << ";" << std::endl;
    }

    if (runner->comando_while != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando_while->node_number << ";" << std::endl;
    }

    if (runner->comando_for != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando_for->node_number << ";" << std::endl;
    }

    if (runner->comando_printf != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando_printf->node_number << ";" << std::endl;
    }

    if (runner->comando_scanf != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando_scanf->node_number << ";" << std::endl;
    }

    if (runner->comando_exit != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando_exit->node_number << ";" << std::endl;
    }

    if (runner->comando_return != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando_return->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Comando"
            << "\"];" << std::endl;

    // std::cout << "Comando" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ListaComandosTemporario(ast::AST_Node_Lista_Comandos_Temporario* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Comando(runner->comando);
    ast::traversal::traversal_ListaComandosTemporario(runner->lista_comandos_temporario);

    dotfile << "\t" << runner->node_number << " -> " << runner->comando->node_number << ";" << std::endl;

    if (runner->lista_comandos_temporario != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos_temporario->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Lista Comandos Temporario"
            << "\"];" << std::endl;

    // std::cout << "Lista Comandos Temporario" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_ListaComandos(ast::AST_Node_Lista_Comandos* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    ast::traversal::traversal_Comando(runner->comando);
    ast::traversal::traversal_ListaComandosTemporario(runner->lista_comandos_temporario);

    dotfile << "\t" << runner->node_number << " -> " << runner->comando->node_number << ";" << std::endl;

    if (runner->lista_comandos_temporario != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos_temporario->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Lista Comandos"
            << "\"];" << std::endl;

    // std::cout << "Lista Comandos" << " Node number = " << runner->node_number << std::endl;
}

void ast::traversal::traversal_CorpoFuncao(ast::AST_Node_Corpo_Funcao* runner) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    runner->node_number = node_counter++;

    ast::traversal::traversal_ListaComandos(runner->lista_comandos);

    if (runner->lista_comandos != nullptr) {
        dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos->node_number << ";" << std::endl;
    }

    dotfile << "\t" << runner->node_number << " [shape = box, label = \""
            << "Corpo Funcao\n"
            << *(runner->function_name)
            << "\"];" << std::endl;

    // std::cout << "Corpo Funcao" << " Node number = " << runner->node_number << std::endl;
}