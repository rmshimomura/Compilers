#include "compiler.hpp"
#include "definitions.hpp"

int main () {

    input = "";
    char c;

    while ((c = getchar()) != EOF) {
        input += c;
    }

    Compiler::Lexic_Analyzer lexic;

    Compiler::Syntactic_analyzer syntactic;

    int correct_program = 1;
    
    s.push(".");
    s.push("BlocoComandos");
    s.push("ProcedimentoFuncao");
    s.push("BlocoVariaveis");
    s.push(";");
    s.push("id");
    s.push("algoritmo");

    while(input.size() > 0) {

        if(ask_for_new_token) {

            token_read_value = lexic.lexic_analyze(input);

            if(token_read_value == 0) {
                correct_program = 0;
                break;
            } else if (token_read_value == 54 || token_read_value == 55 || token_read_value == 57) {
                continue;
            }

        }

        // std::cout << "Token lido: " << token_read << " " << s.top() << " " << token_read_value << std::endl;
        // std::cout << "Token lido: " << token_read << " " << column_number << " " << token_read_value << std::endl;

        syntactic.syntax_analyze(token_read_value);

    }

    if(correct_program) {
        std::cout << "PROGRAMA CORRETO.";
    }

    return 0;
}