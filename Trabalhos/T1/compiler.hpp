#include "definitions.hpp"

namespace Compiler {

class Lexic_Analyzer {
   public:
    int lexic_analyze(std::string line) {
        int current_state = 1;
        int last_final_state = 0;
        int last_final_state_position = 0;
        std::string current_token = "";
        std::string last_final_token = "";

        for (int i = 0; i < line.length(); i++) {
            int next_state = transistions_table[current_state][line[i]];
            current_token += line[i];

            if (next_state != 0 && next_state != 171) {
                current_state = next_state;

                if (line[i] == '\n') {
                    line_number++;
                    column_number = 0;
                } else if(line[i] == '\t') {
                    column_number += 4;
                } else {
                    column_number++;
                }
                
                if (final_states[current_state] == 1) {
                    last_final_state = current_state;
                    last_final_state_position = i;
                    last_final_token = current_token;
                }

                if (i == line.length() - 1) {
                    if (final_states[current_state] == 1) {
                        if (last_final_token == " ") {
                            continue;
                        }
                        input.erase(0, last_final_state_position + 1);
                        token_read = last_final_token;
                        return tokens[last_final_state];
                    }
                }

            } else {
                if (last_final_state != 0) {
                    if (last_final_token != " ") {
                        input.erase(0, last_final_state_position + 1);
                        token_read = last_final_token;
                        return tokens[last_final_state];
                    }
                } else {
                    if (line[i] == ' ') {
                        current_state = 1;
                        last_final_state = 0;
                        last_final_state_position = 0;
                        last_final_token = "";
                        current_token = "";
                        continue;
                    } else if (line[i] == '\n') {
                        line_number++;
                        column_number = 0;
                        input.erase(0, i + 1);
                        token_read = last_final_token;
                        return OUTRO;
                    }
                    column_number++;
                    std::cout << "ERRO LEXICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << current_token << "\'";
                    return ERRO;
                }
            }
        }
        return ERRO;
    }
};

class Syntactic_analyzer {
   public:

    void syntax_analyze(int token_value) {

        switch (token_value) {
            case ALGORITMO:
                algorithm_function();
                break;
            case PONTO:
                point_function();
                break;
            case ID:
                id_function();
                break;
            case PONTO_VIRGULA:
                semicolon_function();
                break;
            case PROCEDIMENTO:
                procedure_function();
                break;
            case FUNCAO:
                function_function();
                break;
            case DOIS_PONTOS:
                colon_function();
                break;
            case ABRE_PAR:
                open_parenthesis_function();
                break;
            case FECHA_PAR:
                close_parenthesis_function();
                break;
            case VARIAVEIS:
                variables_function();
                break;
            case TIPO:
                type_function();
                break;
            case IGUAL:
                equal_function();
                break;
            case ABRE_COL:
                open_bracket_function();
                break;
            case FECHA_COL:
                close_bracket_function();
                break;
            case VETOR:
                vector_function();
                break;
            case MATRIZ:
                matrix_function();
                break;
            case NUMERO_INTEIRO:
                integer_number_function();
                break;
            case INTEIRO:
                integer_function();
                break;
            case REAL:
                real_function();
                break;
            case CARACTERE:
                character_function();
                break;
            case LOGICO:
                logical_function();
                break;
            case INICIO:
                begin_function();
                break;
            case FIM:
                end_function();
                break;
            case SE:
                if_function();
                break;
            case ENTAO:
                then_function();
                break;
            case PARA:
                for_function();
                break;
            case DE:
                from_function();
                break;
            case ATE:
                until_function();
                break;
            case ENQUANTO:
                while_function();
                break;
            case FACA:
                do_function();
                break;
            case REPITA:
                repeat_function();
                break;
            case LEIA:
                read_function();
                break;
            case IMPRIMA:
                print_function();
                break;
            case ATRIBUICAO:
                attribution_function();
                break;
            case MAIS:
                plus_function();
                break;
            case MENOS:
                minus_function();
                break;
            case NAO:
                not_function();
                break;
            case NUMERO_REAL:
                real_number_function();
                break;
            case VERDADEIRO:
                true_function();
                break;
            case FALSO:
                false_function();
                break;
            case TEXTO:
                text_function();
                break;
            case VIRGULA:
                comma_function();
                break;
            case PASSO:
                step_function();
                break;
            case SENAO:
                else_function();
                break;
            case DIFERENTE:
                different_function();
                break;
            case MENOR:
                less_function();
                break;
            case MENOR_IGUAL:
                less_equal_function();
                break;
            case MAIOR:
                greater_function();
                break;
            case MAIOR_IGUAL:
                greater_equal_function();
                break;
            case OU:
                or_function();
                break;
            case VEZES:
                times_function();
                break;
            case DIVISAO:
                division_function();
                break;
            case DIV:
                div_function();
                break;
            case E:
                and_function();
                break;
            default:
                break;
            break;
        }
    }

    void algorithm_function() {

        if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "algoritmo") {
            std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
            exit(0);
        }

        s.pop();
        ask_for_new_token = true;
    }

    void point_function() {
        ask_for_new_token = false;

        if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != ".") {
            std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
            exit(0);
        }
        s.pop();
        ask_for_new_token = true;
    }

    void id_function() {
        ask_for_new_token = false;
            
        if (s.top() == "DeclaraParametros") {
            s.pop();
            s.push("Declaracoes");
        } else if (s.top() == "Declaracoes") {
            s.pop();
            s.push("Declaracoes\'");
            s.push("DeclaraVariaveis");
        } else if (s.top() == "DeclaraVariaveis") {
            s.pop();
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("TipoBasico");
        } else if (s.top() == "DeclaraIdentificador") {
            s.pop();
            s.push("DeclaraIdentificador\'");
            s.push("id");
        } else if (s.top() == "TipoBasico") {
            s.pop();
            s.push("id");
        } else if (s.top() == "ListaComandos") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos");
        } else if (s.top() == "Comandos") {
            s.pop();
            s.push("ComandosExtra");
            s.push("id");
        } else if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
        } else if (s.top() == "Termo") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Fator");
        } else if (s.top() == "Fator") {
            s.pop();
            s.push("FatorExtra");
            s.push("id");
        } else if (s.top() == "Variavel") {
            s.pop();
            s.push("Variavel\'");
            s.push("id");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIterExtra");
            s.push("id");
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("id");
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("id");
        } else if (s.top() == "ListaComandos\'") {
            s.pop();
            s.push("ListaComandosExtra\'");
            s.push("id");
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper)) {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void semicolon_function() {
        ask_for_new_token = false;
        if (s.top() == "Parametros") {
            s.pop();
        } else if (s.top() == "ComandosExtra") {
            s.pop();
            s.push("Comandos\'\'\'");
        } else if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "DeclaraIdentificador\'") {
            s.pop();
        } else if (s.top() == "ListaComandosExtra\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos\'\'\'");
        } else if (s.top() == "Comandos\'\'\'") {
            s.pop();
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != ";") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void procedure_function() {
        ask_for_new_token = false;
        if (s.top() == "ProcedimentoFuncao") {
            s.pop();
            s.push("ProcedimentoFuncao");
            s.push("DeclaraProcedimento");
        } else if (s.top() == "DeclaraProcedimento") {
            s.pop();
            s.push(";");
            s.push("BlocoComandos");
            s.push("BlocoVariaveis");
            s.push("DeclaraParametros");
            s.push(";");
            s.push("Parametros");
            s.push("id");
            s.push("procedimento");
        } else if (s.top() == "BlocoVariaveis") {
            s.pop();
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "procedimento") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void function_function() {
        ask_for_new_token = false;

        if (s.top() == "ProcedimentoFuncao") {
            s.pop();
            s.push("ProcedimentoFuncao");
            s.push("DeclaraFuncao");
        } else if (s.top() == "DeclaraFuncao") {
            s.pop();
            s.push(";");
            s.push("BlocoComandos");
            s.push("BlocoVariaveis");
            s.push("DeclaraParametros");
            s.push(";");
            s.push("TipoBasico");
            s.push(":");
            s.push("Parametros");
            s.push("id");
            s.push("funcao");
        } else if (s.top() == "BlocoVariaveis") {
            s.pop();
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "funcao") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void colon_function() {
        ask_for_new_token = false;
        if (s.top() == "Parametros") {
            s.pop();
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != ":") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void open_parenthesis_function() {
        ask_for_new_token = false;
        if (s.top() == "Parametros") {
            s.pop();
            s.push(")");
            s.push("DeclaraIdentificador");
            s.push("(");
        } else if (s.top() == "ComandosExtra") {
            s.pop();
            s.push("Comandos\'\'\'");
        } else if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
        } else if (s.top() == "Termo") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Fator");
        } else if (s.top() == "Fator") {
            s.pop();
            s.push(")");
            s.push("Expressao");
            s.push("(");
        } else if (s.top() == "FatorExtra") {
            s.pop();
            s.push(")");
            s.push("ExprIter");
            s.push("(");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push(")");
            s.push("Expressao");
            s.push("(");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push(")");
            s.push("ExprIter");
            s.push("(");
        } else if (s.top() == "ListaComandosExtra\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos\'\'\'");
        } else if (s.top() == "Comandos\'\'\'") {
            s.pop();
            s.push(")");
            s.push("ExprIter");
            s.push("(");
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "(") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void close_parenthesis_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "DeclaraIdentificador\'") {
            s.pop();
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "ExprIter\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != ")") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void variables_function() {
        ask_for_new_token = false;
        if (s.top() == "DeclaraParametros") {
            s.pop();
        } else if (s.top() == "BlocoVariaveis") {
            s.pop();
            s.push("Declaracoes");
            s.push("variaveis");
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "variaveis") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void type_function() {
        ask_for_new_token = false;
        if (s.top() == "DeclaraParametros") {
            s.pop();
            s.push("Declaracoes");
        } else if (s.top() == "Declaracoes") {
            s.pop();
            s.push("Declaracoes\'\'");
            s.push("DeclaraTipo");
        } else if (s.top() == "DeclaraTipo") {
            s.pop();
            s.push(";");
            s.push("TipoBasico");
            s.push("]");
            s.push("Dimensao");
            s.push("[");
            s.push("VetorMatriz");
            s.push("=");
            s.push("id");
            s.push("tipo");
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
            s.push("Declaracoes\'\'");
            s.push(";");
            s.push("TipoBasico");
            s.push("]");
            s.push("Dimensao");
            s.push("[");
            s.push("VetorMatriz");
            s.push("=");
            s.push("id");
            s.push("tipo");
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
            s.push("Declaracoes\'\'");
            s.push(";");
            s.push("TipoBasico");
            s.push("]");
            s.push("Dimensao");
            s.push("[");
            s.push("VetorMatriz");
            s.push("=");
            s.push("id");
            s.push("tipo");
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "tipo") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void equal_function() {

        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Expressao\'") {
            s.pop();
            s.push("ExpressaoSimples");
            s.push("=");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("Expressao\'");
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "=") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void open_bracket_function() {
        ask_for_new_token = false;
        if (s.top() == "ComandosExtra") {
            s.pop();
            s.push("Expressao");
            s.push("<-");
            s.push("Variavel\'");
        } else if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "ListaComandosExtra\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Expressao");
            s.push("<-");
            s.push("Variavel\'");
        } else if (s.top() == "Variavel\'") {
            s.pop();
            s.push("]");
            s.push("ExprIter");
            s.push("[");
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "[") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;
            
        }
    }

    void close_bracket_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Dimensao\'") {
            s.pop();
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "ExprIter\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {

            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "]") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }

            s.pop();
            ask_for_new_token = true;

        }

    }

    void vector_function() {
        ask_for_new_token = false;
        if (s.top() == "VetorMatriz") {
            s.pop();
            s.push("vetor");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "vetor") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void matrix_function() {
        ask_for_new_token = false;
        if (s.top() == "VetorMatriz") {
            s.pop();
            s.push("matriz");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "matriz") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void integer_number_function() {
        ask_for_new_token = false;
        if (s.top() == "Dimensao") {
            s.pop();
            s.push("Dimensao\'");
            s.push("numero_inteiro");
            s.push(":");
            s.push("numero_inteiro");
        } else if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
        } else if (s.top() == "Termo") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Fator");
        } else if (s.top() == "Fator") {
            s.pop();
            s.push("numero_inteiro");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("numero_inteiro");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "numero_inteiro") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void integer_function() {
        ask_for_new_token = false;
        if (s.top() == "DeclaraParametros") {
            s.pop();
            s.push("Declaracoes");
        } else if (s.top() == "Declaracoes") {
            s.pop();
            s.push("Declaracoes\'");
            s.push("DeclaraVariaveis");
        } else if (s.top() == "DeclaraVariaveis") {
            s.pop();
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("TipoBasico");
        } else if (s.top() == "TipoBasico") {
            s.pop();
            s.push("inteiro");
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("inteiro");
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("inteiro");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "inteiro") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void real_function() {
        ask_for_new_token = false;
        if (s.top() == "DeclaraParametros") {
            s.pop();
            s.push("Declaracoes");
        } else if (s.top() == "Declaracoes") {
            s.pop();
            s.push("Declaracoes\'");
            s.push("DeclaraVariaveis");
        } else if (s.top() == "DeclaraVariaveis") {
            s.pop();
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("TipoBasico");
        } else if (s.top() == "TipoBasico") {
            s.pop();
            s.push("real");
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("real");
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("real");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "real") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void character_function () {
        ask_for_new_token = false;
        if (s.top() == "DeclaraParametros") {
            s.pop();
            s.push("Declaracoes");
        } else if (s.top() == "Declaracoes") {
            s.pop();
            s.push("Declaracoes\'");
            s.push("DeclaraVariaveis");
        } else if (s.top() == "DeclaraVariaveis") {
            s.pop();
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("TipoBasico");
        } else if (s.top() == "TipoBasico") {
            s.pop();
            s.push("caractere");
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("caractere");
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("caractere");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "caractere") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void logical_function() {
        ask_for_new_token = false;
        if (s.top() == "DeclaraParametros") {
            s.pop();
            s.push("Declaracoes");
        } else if (s.top() == "Declaracoes") {
            s.pop();
            s.push("Declaracoes\'");
            s.push("DeclaraVariaveis");
        } else if (s.top() == "DeclaraVariaveis") {
            s.pop();
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("TipoBasico");
        } else if (s.top() == "TipoBasico") {
            s.pop();
            s.push("logico");
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("logico");
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
            s.push("Declaracoes\'");
            s.push(";");
            s.push("DeclaraIdentificador");
            s.push(":");
            s.push("logico");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "logico") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void begin_function() {
        ask_for_new_token = false;
        if (s.top() == "ProcedimentoFuncao") {
            s.pop();
        } else if (s.top() == "DeclaraParametros") {
            s.pop();
        } else if (s.top() == "BlocoVariaveis") {
            s.pop();
        } else if (s.top() == "BlocoComandos") {
            s.pop();
            s.push("fim");
            s.push("ListaComandos");
            s.push("inicio");
        } else if (s.top() == "Declaracoes\'") {
            s.pop();
        } else if (s.top() == "Declaracoes\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "inicio") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void end_function() {
        ask_for_new_token = false;
        if (s.top() == "ListaComandos\'") {
            s.pop();
        } else if (s.top() == "Comandos\'\'") {
            s.pop();
            s.push("se");
            s.push("fim");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "fim") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void if_function() {
        ask_for_new_token = false;
        if (s.top() == "ListaComandos") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos");
        } else if (s.top() == "Comandos") {
            s.pop();
            s.push("Comandos\'\'");
            s.push("ListaComandos");
            s.push("entao");
            s.push("Expressao");
            s.push("se");
        } else if (s.top() == "ListaComandos\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos\'\'");
            s.push("ListaComandos");
            s.push("entao");
            s.push("Expressao");
            s.push("se");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "se") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void then_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "entao") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void for_function() {
        ask_for_new_token = false;
        if (s.top() == "ListaComandos") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos");
        } else if (s.top() == "Comandos") {
            s.pop();
            s.push("Comandos\'");
            s.push("Expressao");
            s.push("ate");
            s.push("Expressao");
            s.push("de");
            s.push("id");
            s.push("para");
        } else if (s.top() == "ListaComandos\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos\'");
            s.push("Expressao");
            s.push("ate");
            s.push("Expressao");
            s.push("de");
            s.push("id");
            s.push("para");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "para") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void from_function() {
        ask_for_new_token = false;

        if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "de") {
            std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
            exit(0);
        }
        s.pop();
        ask_for_new_token = true;
    }

    void until_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ListaComandos\'") {
            s.pop();
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "ate") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void while_function() {
        ask_for_new_token = false;
        if (s.top() == "ListaComandos") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos");
        } else if (s.top() == "Comandos") {
            s.pop();
            s.push("enquanto");
            s.push("fim");
            s.push("ListaComandos");
            s.push("faca");
            s.push("Expressao");
            s.push("enquanto");
        } else if (s.top() == "ListaComandos\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("enquanto");
            s.push("fim");
            s.push("ListaComandos");
            s.push("faca");
            s.push("Expressao");
            s.push("enquanto");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "enquanto") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void do_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "Comandos\'") {
            s.pop();
            s.push("para");
            s.push("fim");
            s.push("ListaComandos");
            s.push("faca");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "faca") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void repeat_function() {
        ask_for_new_token = false;
        if (s.top() == "ListaComandos") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos");
        } else if (s.top() == "Comandos") {
            s.pop();
            s.push("Expressao");
            s.push("ate");
            s.push("ListaComandos");
            s.push("repita");
        } else if (s.top() == "ListaComandos\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Expressao");
            s.push("ate");
            s.push("ListaComandos");
            s.push("repita");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "repita") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void read_function() {
        ask_for_new_token = false;
        if (s.top() == "ListaComandos") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos");
        } else if (s.top() == "Comandos") {
            s.pop();
            s.push(")");
            s.push("Variavel");
            s.push("(");
            s.push("leia");
        } else if (s.top() == "ListaComandos\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push(")");
            s.push("Variavel");
            s.push("(");
            s.push("leia");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "leia") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void print_function() {
        ask_for_new_token = false;
        if (s.top() == "ListaComandos") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Comandos");
        } else if (s.top() == "Comandos") {
            s.pop();
            s.push(")");
            s.push("ExprIter");
            s.push("(");
            s.push("imprima");
        } else if (s.top() == "ListaComandos\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push(")");
            s.push("ExprIter");
            s.push("(");
            s.push("imprima");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "imprima") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void attribution_function() {
        ask_for_new_token = false;
        if (s.top() == "ComandosExtra") {
            s.pop();
            s.push("Expressao");
            s.push("<-");
            s.push("Variavel\'");
        } else if (s.top() == "ListaComandosExtra\'") {
            s.pop();
            s.push("ListaComandos\'");
            s.push(";");
            s.push("Expressao");
            s.push("<-");
            s.push("Variavel\'");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "<-") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void plus_function() {
        ask_for_new_token = false;
        if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
            s.push("+");
        } else if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("+");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "ExpressaoSimples\'") {
            s.pop();
            s.push("Termo");
            s.push("+");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("ExpressaoSimples\'");
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "+") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void minus_function() {
        ask_for_new_token = false;
        if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
            s.push("-");
        } else if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("-");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "ExpressaoSimples\'") {
            s.pop();
            s.push("Termo");
            s.push("-");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("ExpressaoSimples\'");
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "-") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void not_function() {
        ask_for_new_token = false;
        if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
        } else if (s.top() == "Termo") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Fator");
        } else if (s.top() == "Fator") {
            s.pop();
            s.push("Fator");
            s.push("nao");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Fator");
            s.push("nao");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "nao") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void real_number_function() {
        ask_for_new_token = false;
        if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
        } else if (s.top() == "Termo") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Fator");
        } else if (s.top() == "Fator") {
            s.pop();
            s.push("numero_real");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("numero_real");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "numero_real") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void true_function() {
        ask_for_new_token = false;
        if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
        } else if (s.top() == "Termo") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Fator");
        } else if (s.top() == "Fator") {
            s.pop();
            s.push("verdadeiro");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("verdadeiro");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "verdadeiro") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void false_function() {
        ask_for_new_token = false;
        if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
        } else if (s.top() == "Termo") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Fator");
        } else if (s.top() == "Fator") {
            s.pop();
            s.push("falso");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("falso");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "falso") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void text_function() {
        ask_for_new_token = false;
        if (s.top() == "Expressao") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples");
        } else if (s.top() == "ExpressaoSimples") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Termo");
        } else if (s.top() == "Termo") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Fator");
        } else if (s.top() == "Fator") {
            s.pop();
            s.push("texto");
        } else if (s.top() == "ExprIter") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("texto");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "texto") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void comma_function() {
        ask_for_new_token = false;

        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "DeclaraIdentificador\'") {
            s.pop();
            s.push("DeclaraIdentificador");
            s.push(",");
        } else if (s.top() == "Dimensao\'") {
            s.pop();
            s.push("Dimensao");
            s.push(",");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "ExprIter\'") {
            s.pop();
            s.push("ExprIter");
            s.push(",");
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != ",") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void step_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "Comandos\'") {
            s.pop();
            s.push("para");
            s.push("fim");
            s.push("ListaComandos");
            s.push("faca");
            s.push("Expressao");
            s.push("passo");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "passo") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void else_function() {
        ask_for_new_token = false;
        if (s.top() == "ListaComandos\'") {
            s.pop();
        } else if (s.top() == "Comandos\'\'") {
            s.pop();
            s.push("se");
            s.push("fim");
            s.push("ListaComandos");
            s.push("senao");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "senao") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void different_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Expressao\'") {
            s.pop();
            s.push("ExpressaoSimples");
            s.push("<>");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("Expressao\'");
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "<>") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void less_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Expressao\'") {
            s.pop();
            s.push("ExpressaoSimples");
            s.push("<");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("Expressao\'");
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "<") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void less_equal_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Expressao\'") {
            s.pop();
            s.push("ExpressaoSimples");
            s.push("<=");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("Expressao\'");
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "<=") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void greater_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Expressao\'") {
            s.pop();
            s.push("ExpressaoSimples");
            s.push(">");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("Expressao\'");
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != ">") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void greater_equal_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Expressao\'") {
            s.pop();
            s.push("ExpressaoSimples");
            s.push(">=");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Expressao\'\'") {
            s.pop();
            s.push("Expressao\'\'");
            s.push("Expressao\'");
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != ">=") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void or_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra\'") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "ExpressaoSimples\'") {
            s.pop();
            s.push("Termo");
            s.push("ou");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "ExpressaoSimples\'\'") {
            s.pop();
            s.push("ExpressaoSimples\'\'");
            s.push("ExpressaoSimples\'");
        } else if (s.top() == "Termo\'\'") {
            s.pop();
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "ou") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void times_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Termo\'") {
            s.pop();
            s.push("Fator");
            s.push("*");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Termo\'");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "*") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void division_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Termo\'") {
            s.pop();
            s.push("Fator");
            s.push("/");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Termo\'");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "/") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void div_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Termo\'") {
            s.pop();
            s.push("Fator");
            s.push("div");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Termo\'");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "div") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

    void and_function() {
        ask_for_new_token = false;
        if (s.top() == "FatorExtra") {
            s.pop();
            s.push("Variavel\'");
        } else if (s.top() == "ExprIterExtra") {
            s.pop();
            s.push("ExprIter\'");
            s.push("Expressao\'\'");
            s.push("ExpressaoSimples\'\'");
            s.push("Termo\'\'");
            s.push("Variavel\'");
        } else if (s.top() == "Termo\'") {
            s.pop();
            s.push("Fator");
            s.push("e");
        } else if (s.top() == "Variavel\'") {
            s.pop();
        } else if (s.top() == "Termo\'\'") {
            s.pop();
            s.push("Termo\'\'");
            s.push("Termo\'");
        } else {
            if (std::any_of(s.top().begin(), s.top().end(), ::isupper) || s.top() != "e") {
                std::cout << "ERRO DE SINTAXE. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token_read << "\'";
                exit(0);
            }
            s.pop();
            ask_for_new_token = true;
        }
    }

};

}  // namespace Compiler