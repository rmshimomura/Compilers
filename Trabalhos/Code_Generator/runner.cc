#include "ast_node.hh"

std::ofstream dotfile("test.dot");
int node_counter = 0;

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

void ast::traversal::free_ASTs(std::vector<ast::AST_Function*> funcoes, std::vector<ast::AST_Constant*> constantes, std::vector<ast::AST_Variable*> variaveis_globais) {

    for (auto function : funcoes) {
        ast::traversal::traversal_AST(function, 0, 1);
        delete function->function_name;
        delete function->return_type;

        for (auto parameter : function->parameters) {
            delete parameter->name;
            delete parameter->type;
            delete parameter;
        }

        for (auto variable : function->variables) {
            delete variable->name;
            delete variable->type;
            delete variable->value;
            delete variable;
        }

        delete function;

    }

    for (auto constant : constantes) {
        delete constant->name;
        delete constant;
    }

    for (auto variable : variaveis_globais) {
        delete variable->name;
        delete variable->type;
        delete variable->value;
        delete variable;
    }


}

void ast::traversal::print_ASTs(std::vector<ast::AST_Function*> funcoes) {
    dotfile << "digraph ARV {" << std::endl;
    dotfile << "graph [pad=\"0.5\", nodesep=\"0.5\", ranksep=\"2\"];" << std::endl;

    for (auto function : funcoes) {
        ast::traversal::traversal_AST(function, 1, 0);
    }

    dotfile << "}" << std::endl;
    dotfile.close();
}

void ast::traversal::traversal_AST(ast::AST_Function* function, int print_graphviz, int free_AST) {
    if (function->function_body == nullptr) {
        std::cout << "Function body is empty." << std::endl;
        return;
    }

    function->function_body->function_name = function->function_name;

    ast::traversal::traversal_Corpo_Funcao(function->function_body, print_graphviz, free_AST);

}

void ast::traversal::traversal_BOP(ast::AST_Node_BOP* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->left) {
        runner->left->parent = runner;
    }

    if (runner->right) {
        runner->right->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->left, print_graphviz, free_AST);
    ast::traversal::traversal_Expressao(runner->right, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->left != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->left->node_number << ";" << std::endl;
        }

        if (runner->right != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->right->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \"" << runner->operation << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_UOP(ast::AST_Node_UOP* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->child) {
        runner->child->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->child, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->child != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->child->node_number << ";" << std::endl;
        }

        dotfile << 
        "\t" << 
        runner->node_number << 
        " [shape = box, label = \"" 
        << runner->operation 
        << (runner->is_postfix ? "postfix" : "prefix")
        << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }

}

void ast::traversal::traversal_TOP(ast::AST_Node_TOP* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->test) {
        runner->test->parent = runner;
    }

    if (runner->left) {
        runner->left->parent = runner;
    }

    if (runner->right) {
        runner->right->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->test, print_graphviz, free_AST);
    ast::traversal::traversal_Expressao(runner->left, print_graphviz, free_AST);
    ast::traversal::traversal_Expressao(runner->right, print_graphviz, free_AST);

    if (print_graphviz) {
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
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Expressao(ast::AST_Node_Expressao* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->bop) {
        runner->bop->parent = runner;
    }

    if (runner->uop) {
        runner->uop->parent = runner;
    }

    if (runner->top) {
        runner->top->parent = runner;
    }

    if (runner->chamada_funcao) {
        runner->chamada_funcao->parent = runner;
    }

    if (runner->acesso_variavel) {
        runner->acesso_variavel->parent = runner;
    }

    ast::traversal::traversal_BOP(runner->bop, print_graphviz, free_AST);
    ast::traversal::traversal_UOP(runner->uop, print_graphviz, free_AST);
    ast::traversal::traversal_TOP(runner->top, print_graphviz, free_AST);
    ast::traversal::traversal_Chamada_Funcao(runner->chamada_funcao, print_graphviz, free_AST);
    ast::traversal::traversal_Acesso_Variavel(runner->acesso_variavel, print_graphviz, free_AST);

    if (print_graphviz) {
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
    }

    if (free_AST) {
        delete runner;
    }

}

void ast::traversal::traversal_Chamada_Funcao(ast::AST_Node_Chamada_Funcao* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->loop_expressoes) {
        runner->loop_expressoes->parent = runner;
    }

    ast::traversal::traversal_Loop_Expressoes(runner->loop_expressoes, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->loop_expressoes != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->loop_expressoes->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \"Chamada Funcao " << *(runner->function_name) << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner->function_name;
        delete runner;
    }

}

void ast::traversal::traversal_Acesso_Variavel(ast::AST_Node_Acesso_Variavel* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->loop_matriz) {
        runner->loop_matriz->parent = runner;
    }

    ast::traversal::traversal_Loop_Matriz(runner->loop_matriz, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->loop_matriz != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->loop_matriz->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \"Acesso Variavel " << *(runner->variable_name) << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner->variable_name;
        delete runner;
    }
}

void ast::traversal::traversal_Loop_Expressoes(ast::AST_Node_Loop_Expressoes* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    if (runner->loop_expressoes_temporario) {
        runner->loop_expressoes_temporario->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);
    ast::traversal::traversal_Loop_Expressoes_Temporario(runner->loop_expressoes_temporario, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        if (runner->loop_expressoes_temporario != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->loop_expressoes_temporario->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Loop Expressoes"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Loop_Expressoes_Temporario(ast::AST_Node_Loop_Expressoes_Temporario* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    if (runner->loop_expressoes_temporario) {
        runner->loop_expressoes_temporario->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);
    ast::traversal::traversal_Loop_Expressoes_Temporario(runner->loop_expressoes_temporario, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        if (runner->loop_expressoes_temporario != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->loop_expressoes_temporario->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Loop Expressoes Temporario"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Loop_Matriz(ast::AST_Node_Loop_Matriz* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    if (runner->loop_matriz) {
        runner->loop_matriz->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);
    ast::traversal::traversal_Loop_Matriz(runner->loop_matriz, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        if (runner->loop_matriz != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->loop_matriz->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Loop Matriz"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }

}

void ast::traversal::traversal_Condicao_Parada(ast::AST_Node_Condicao_Parada* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Condicao Parada"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }

}

void ast::traversal::traversal_Ajuste_Valores(ast::AST_Node_Ajuste_Valores* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Ajuste Valores"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }

}

void ast::traversal::traversal_Inicializacao_For(ast::AST_Node_Inicializacao_For* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Inicializacao For"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner->identifier;
        delete runner;
    }
}

void ast::traversal::traversal_Expressoes_Printf_Temporario(ast::AST_Node_Expressoes_Printf_Temporario* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);
    ast::traversal::traversal_Expressoes_Printf_Temporario(runner->expressoes_printf_temporario, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        if (runner->expressoes_printf_temporario != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressoes_printf_temporario->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Expressoes Printf Temporario"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Expressoes_Printf(ast::AST_Node_Expressoes_Printf* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    if(runner->expressoes_printf_temporario) {
        runner->expressoes_printf_temporario->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);
    ast::traversal::traversal_Expressoes_Printf_Temporario(runner->expressoes_printf_temporario, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        if (runner->expressoes_printf_temporario != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressoes_printf_temporario->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Expressoes Printf"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Endereco_Var(ast::AST_Node_Endereco_Var* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (print_graphviz) {
        dotfile << "\t" << runner->node_number << " [shape = box, label = \"" << *(runner->identifier) << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner->identifier;
        delete runner;
    }
}

void ast::traversal::traversal_Comando_Return(ast::AST_Node_Comando_Return* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->CondicaoParada) {
        runner->CondicaoParada->parent = runner;
    }

    ast::traversal::traversal_Condicao_Parada(runner->CondicaoParada, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->CondicaoParada != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->CondicaoParada->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Comando Return"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }

}

void ast::traversal::traversal_Comando_Exit(ast::AST_Node_Comando_Exit* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressao != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressao->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Comando Exit"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Comando_Scanf(ast::AST_Node_Comando_Scanf* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->endereco_var) {
        runner->endereco_var->parent = runner;
    }

    ast::traversal::traversal_Endereco_Var(runner->endereco_var, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->endereco_var != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->endereco_var->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Comando Scanf"
                << runner->string->substr(1, runner->string->size() - 2)
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner->string;
        delete runner;
    }
}

void ast::traversal::traversal_Comando_Printf(ast::AST_Node_Comando_Printf* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressoes_printf) {
        runner->expressoes_printf->parent = runner;
    }

    ast::traversal::traversal_Expressoes_Printf(runner->expressoes_printf, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->expressoes_printf != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->expressoes_printf->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Comando Printf \n"
                << runner->string->substr(1, runner->string->size() - 2)
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner->string;
        delete runner;
    }
}

void ast::traversal::traversal_Comando_For(ast::AST_Node_Comando_For* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->inicializacao_for) {
        runner->inicializacao_for->parent = runner;
    }

    if (runner->condicao_parada) {
        runner->condicao_parada->parent = runner;
    }

    if (runner->ajuste_valores) {
        runner->ajuste_valores->parent = runner;
    }

    if (runner->lista_comandos) {
        runner->lista_comandos->parent = runner;
    }

    ast::traversal::traversal_Inicializacao_For(runner->inicializacao_for, print_graphviz, free_AST);
    ast::traversal::traversal_Condicao_Parada(runner->condicao_parada, print_graphviz, free_AST);
    ast::traversal::traversal_Ajuste_Valores(runner->ajuste_valores, print_graphviz, free_AST);
    ast::traversal::traversal_Lista_Comandos(runner->lista_comandos, print_graphviz, free_AST);

    if (print_graphviz) {
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
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Comando_While(ast::AST_Node_Comando_While* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->condicao_parada) {
        runner->condicao_parada->parent = runner;
    }

    if (runner->lista_comandos) {
        runner->lista_comandos->parent = runner;
    }

    ast::traversal::traversal_Condicao_Parada(runner->condicao_parada, print_graphviz, free_AST);
    ast::traversal::traversal_Lista_Comandos(runner->lista_comandos, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->condicao_parada != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->condicao_parada->node_number << ";" << std::endl;
        }

        if (runner->lista_comandos != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Comando While"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Comando_If(ast::AST_Node_Comando_If* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->condicao_parada) {
        runner->condicao_parada->parent = runner;
    }

    if (runner->lista_comandos_then) {
        runner->lista_comandos_then->parent = runner;
    }

    if (runner->lista_comandos_else) {
        runner->lista_comandos_else->parent = runner;
    }

    ast::traversal::traversal_Condicao_Parada(runner->condicao_parada, print_graphviz, free_AST);
    ast::traversal::traversal_Lista_Comandos(runner->lista_comandos_then, print_graphviz, free_AST);
    ast::traversal::traversal_Lista_Comandos(runner->lista_comandos_else, print_graphviz, free_AST);

    if (print_graphviz) {
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
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Comando_Do_While(ast::AST_Node_Comando_Do_While* runner, int print_graphviz, int free_AST) {
    if (!runner) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->condicao_parada) {
        runner->condicao_parada->parent = runner;
    }

    if (runner->lista_comandos) {
        runner->lista_comandos->parent = runner;
    }

    ast::traversal::traversal_Lista_Comandos(runner->lista_comandos, print_graphviz, free_AST);
    ast::traversal::traversal_Condicao_Parada(runner->condicao_parada, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->condicao_parada != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->condicao_parada->node_number << ";" << std::endl;
        }

        if (runner->lista_comandos != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Comando Do While"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Comando(ast::AST_Node_Comando* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->expressao) {
        runner->expressao->parent = runner;
    }

    if (runner->comando_do_while) {
        runner->comando_do_while->parent = runner;
    }

    if (runner->comando_for) {
        runner->comando_for->parent = runner;
    }

    if (runner->comando_if) {
        runner->comando_if->parent = runner;
    }

    if (runner->comando_while) {
        runner->comando_while->parent = runner;
    }

    if (runner->comando_printf) {
        runner->comando_printf->parent = runner;
    }

    if (runner->comando_scanf) {
        runner->comando_scanf->parent = runner;
    }

    if (runner->comando_exit) {
        runner->comando_exit->parent = runner;
    }

    if (runner->comando_return) {
        runner->comando_return->parent = runner;
    }

    ast::traversal::traversal_Expressao(runner->expressao, print_graphviz, free_AST);
    ast::traversal::traversal_Comando_Do_While(runner->comando_do_while, print_graphviz, free_AST);
    ast::traversal::traversal_Comando_If(runner->comando_if, print_graphviz, free_AST);
    ast::traversal::traversal_Comando_While(runner->comando_while, print_graphviz, free_AST);
    ast::traversal::traversal_Comando_For(runner->comando_for, print_graphviz, free_AST);
    ast::traversal::traversal_Comando_Printf(runner->comando_printf, print_graphviz, free_AST);
    ast::traversal::traversal_Comando_Scanf(runner->comando_scanf, print_graphviz, free_AST);
    ast::traversal::traversal_Comando_Exit(runner->comando_exit, print_graphviz, free_AST);
    ast::traversal::traversal_Comando_Return(runner->comando_return, print_graphviz, free_AST);

    if (print_graphviz) {
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
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Lista_Comandos_Temporario(ast::AST_Node_Lista_Comandos_Temporario* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->comando) {
        runner->comando->parent = runner;
    }

    if (runner->lista_comandos_temporario) {
        runner->lista_comandos_temporario->parent = runner;
    }

    ast::traversal::traversal_Comando(runner->comando, print_graphviz, free_AST);
    ast::traversal::traversal_Lista_Comandos_Temporario(runner->lista_comandos_temporario, print_graphviz, free_AST);

    if (print_graphviz) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando->node_number << ";" << std::endl;

        if (runner->lista_comandos_temporario != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos_temporario->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Lista Comandos Temporario"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Lista_Comandos(ast::AST_Node_Lista_Comandos* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->comando) {
        runner->comando->parent = runner;
    }

    if (runner->lista_comandos_temporario) {
        runner->lista_comandos_temporario->parent = runner;
    }

    ast::traversal::traversal_Comando(runner->comando, print_graphviz, free_AST);
    ast::traversal::traversal_Lista_Comandos_Temporario(runner->lista_comandos_temporario, print_graphviz, free_AST);

    if (print_graphviz) {
        dotfile << "\t" << runner->node_number << " -> " << runner->comando->node_number << ";" << std::endl;

        if (runner->lista_comandos_temporario != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos_temporario->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Lista Comandos"
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}

void ast::traversal::traversal_Corpo_Funcao(ast::AST_Node_Corpo_Funcao* runner, int print_graphviz, int free_AST) {
    if (runner == nullptr) return;

    if (runner->node_number == -1) {
        runner->node_number = node_counter++;
    }

    if (runner->lista_comandos) {
        runner->lista_comandos->parent = runner;
    }

    ast::traversal::traversal_Lista_Comandos(runner->lista_comandos, print_graphviz, free_AST);

    if (print_graphviz) {
        if (runner->lista_comandos != nullptr) {
            dotfile << "\t" << runner->node_number << " -> " << runner->lista_comandos->node_number << ";" << std::endl;
        }

        dotfile << "\t" << runner->node_number << " [shape = box, label = \""
                << "Corpo Funcao\n"
                << *(runner->function_name)
                << "\"];" << std::endl;
    }

    if (free_AST) {
        delete runner;
    }
}