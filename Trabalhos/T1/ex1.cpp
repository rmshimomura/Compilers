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
    
    stack_analyzer.push("programa");

    while(input.size() > 0) {

        int value = lexic.lexic_analyze(input);

        if(value == 0) {
            correct_program = 0;
            break;
        }

        // syntactic.syntactic_analyze(value);


    }

    if(correct_program) {
        std::cout << "PROGRAMA CORRETO.";
    }

    return 0;
}