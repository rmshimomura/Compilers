#include "compiler.hpp"

std::vector<std::string> transform_input(std::string input) {
    std::vector<std::string> strings;
    std::string current_string = "";
    for(int iter = 0; iter < input.size(); iter++) {
        if(input[iter] != '\n') {
            current_string += input[iter];
        } else {
            strings.push_back(current_string);
            current_string = "";
        }
    }
    strings.push_back(current_string);
    return strings;
}

int main () {

    Compiler::Lexic_Analyzer lexic;

    lexic.initialize_matrix();

    std::string input = "";
    char c;

    while (std::cin.get(c)) {
        input += c;
    }

    std::vector<std::string> strings = transform_input(input);
    
    for(int i = 0; i < strings.size(); i++) {
        lexic.lexic_analyze(strings[i]);
    }

    Compiler::Syntactic_analyzer syntactic;

    syntactic.syntax_analyze();

    return 0;


}