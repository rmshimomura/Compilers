#include "compiler.hpp"


int main () {

    Compiler::Analyzer lexic;

    lexic.initialize_matrix();

    std::string input = "";
    char c;

    while (std::cin.get(c)) {
        input += c;
    }

    std::cout << input.length() << std::endl;

    // lexic.lexic_analyze(input);

    return 0;


}