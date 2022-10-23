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

                if(line[i] == '\n') {
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
                        if(last_final_token == " ") {
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
    std::stack<std::string> stack_analyzer;
    std::vector<std::string> sentence;

    void syntax_analyze(int token_value) {
        
        switch (token_value) {
            
        }

    }

};

}  // namespace Compiler