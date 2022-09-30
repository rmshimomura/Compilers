#include "compiler.hpp"

int main () {

    Compiler::Lexic_Analyzer analyzer;

    while (1) {

        std::string line;
        std::getline(std::cin, line);
        analyzer.sentence = line;

        if (line.empty()) break;

        if(analyzer.analyzeString()) {
            analyzer.newLine();
            std::cout << "CADEIA ACEITA";
        }

        analyzer.numberOfPrints++;

    }


}