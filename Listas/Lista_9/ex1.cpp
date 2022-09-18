#include "compiler.hpp"

int main () {

    Compiler::Analyzer analyzer;

    while (1) {

        std::string line;
        std::getline(std::cin, line);
        analyzer.sentence = line;

        if (line.empty()) break;

        analyzer.analyzeString();

        if(analyzer.accepted) {

            analyzer.newLine();
            std::cout << "CADEIA ACEITA";
            
        }

        analyzer.accepted = true;

        analyzer.numberOfPrints++;

    }


}