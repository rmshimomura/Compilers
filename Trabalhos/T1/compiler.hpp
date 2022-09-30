#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

std::vector<std::vector<std::string>> valid_strings;

namespace Compiler {

class Lexic_Analyzer {
   public:
    std::string sentence;
    // std::string currentToken;

    int transistions_table[3][127]{0};
    int final_states[3]{0,0,1};
    std::string final_states_names[3] = {"error","error","ID"};

    void initialize_matrix() {
        u("1 az 2");
        u("2 az 2");
        u("2 09 2");
        u("1 + 2");
        u("1 * 2");
        u("1 ( 2");
        u("1 ) 2");
        u("1 $ 2");
    }

    void u(std::string line) {

        std::vector<std::string> tokens;
        std::istringstream iss(line);
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));

        char origin = std::stoi(tokens[0]);
        char destination = std::stoi(tokens[2]);

        if (tokens[1] == "blank") {
            transistions_table[origin][32] = destination;

        } else if (tokens[1] == "newline") {
            transistions_table[origin]['\n'] = destination;

        } else if (tokens[1].length() == 2) {
            char range_1 = tokens[1][0];
            char range_2 = tokens[1][1];

            for (int char_read = range_1; char_read <= range_2; char_read++) {
                transistions_table[origin][char_read] = destination;
            }

        } else {
            char char_read = tokens[1][0];
            transistions_table[origin][char_read] = destination;
        }
    }

    void lexic_analyze(std::string line) {

        int current_state = 1;
        int last_final_state = 0;
        int last_final_state_position = 0;
        std::string current_token = "";
        std::string last_final_token = "";
        std::vector<std::string> recognized_tokens;

        for (int i = 0; i < line.length(); i++) {

            int next_state = transistions_table[current_state][line[i]];
            current_token += line[i];

            if (next_state != 0) {

                current_state = next_state;

                if(final_states[current_state] == 1){

                    last_final_state = current_state;
                    last_final_state_position = i;
                    last_final_token = current_token;
                }

                if(i == line.length() - 1) {

                    if(final_states[current_state] == 1){
                        recognized_tokens.push_back(last_final_token);
                    }

                }

            } else {

                if (last_final_state != 0) {

                    recognized_tokens.push_back(last_final_token);
                    i = last_final_state_position;
                    current_state = 1;
                    last_final_state = 0;
                    last_final_state_position = 0;
                    last_final_token = "";
                    current_token = "";

                } else {
                    
                    if(line[i] == ' ') {
                        current_state = 1;
                        last_final_state = 0;
                        last_final_state_position = 0;
                        last_final_token = "";
                        current_token = "";
                        continue;
                    }

                    recognized_tokens.clear();
                    recognized_tokens.push_back("ERRO LEXICO: " + current_token);
                    break;
                }
            }
        }

        valid_strings.push_back(recognized_tokens);
        
    }

};

class Syntactic_analyzer {

    public:

        void syntax_analyze() {

            for(int sentences_iterator = 0; sentences_iterator < valid_strings.size(); sentences_iterator++) {

                if(valid_strings[sentences_iterator].size() == 1 && valid_strings[sentences_iterator][0] == "ERRO LEXICO: ") {
                    std::cout << valid_strings[sentences_iterator][0] << std::endl;
                } else {
                    for(int tokens_iterator = 0; tokens_iterator < valid_strings[sentences_iterator].size(); tokens_iterator++) {
                        std::cout << valid_strings[sentences_iterator][tokens_iterator] << " ";
                    }
                    std::cout << std::endl;
                }

            }

        }

};

}  // namespace Compiler