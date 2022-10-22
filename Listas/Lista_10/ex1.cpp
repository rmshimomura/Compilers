#include "compiler.hpp"

std::vector<std::string> transform_input() {
    std::vector<std::string> strings;
    std::string line;
    while (std::getline(std::cin, line)) {
        strings.push_back(line);
    }
    return strings;
}

int main () {

    Compiler::Lexic_Analyzer lexic;

    lexic.initialize_matrix();

    std::vector<std::string> strings = transform_input();
    
    for(int i = 0; i < strings.size(); i++) {
        lexic.lexic_analyze(strings[i]);
    }

    Compiler::Syntactic_analyzer syntactic;

    syntactic.syntax_analyze();

    syntactic.results();


}