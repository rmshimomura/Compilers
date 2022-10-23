#include "definitions.hpp"

std::vector<std::vector<int>> valid_strings;

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
                }

                column_number++;

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
                        return tokens[last_final_state];
                    }
                }

            } else {
                if (last_final_state != 0) {
                    if (last_final_token != " ") {
                        input.erase(0, last_final_state_position + 1);
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
    int pos_of_current_token = 0;
    std::string token;
    std::stack<std::string> s;
    std::vector<std::string> sentence;

    void syntax_analyze(int token_value) {
        switch (token_value) {
            case ALGORITMO:
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
            break;
        }
    }

    void id_function() {
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
        } else if (s.top() == "ListaComandosExtra\'") {
            s.pop();
            s.push("ListaComandosExtra\'");
            s.push("id");
        } else {

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void semicolon_function() {
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

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void procedure_function() {
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

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void function_function() {

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

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void colon_function() {
        if (s.top() == "Parametros") {
            s.pop();
        } else {

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void open_parenthesis_function() {
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

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void close_parenthesis_function() {
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
        } else if (s.top() == "DeclaraIdentificador") {
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

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void variables_function() {
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

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void type_function() {
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

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

    void equal_function() {
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

            if (std::any_of(token.begin(), token.end(), ::isupper)) {
                std::cout << "ERRO SINTATICO. Linha: " << line_number << " Coluna: " << column_number << " -> \'" << token << "\'";
                exit(0);
            }

            s.pop();
            
        }
    }

};

}  // namespace Compiler