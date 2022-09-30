#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

namespace Compiler {

class Analyzer {
   public:
    std::string sentence;
    // std::string currentToken;

    int transistions_table[14][127]{0};
    int final_states[14]{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1};
    std::string final_states_names[14] = {"error", "", "ID", "IF", "ID", "error", "REAL", "NUM", "REAL", "error", "", "comment", "white space", "error"};

    void initialize_matrix() {
        u("1 i 2");
        u("1 ah 4");
        u("1 jz 4");
        u("2 f 3");
        u("2 ae 4");
        u("2 gz 4");
        u("2 09 4");
        u("3 09 4");
        u("3 az 4");
        u("4 09 4");
        u("4 az 4");
        u("1 . 5");
        u("5 09 6");
        u("6 09 6");
        u("1 09 7");
        u("7 09 7");
        u("7 . 8");
        u("8 09 8");
        u("1 - 9");
        u("9 - 10");
        u("10 az 10");
        u("10 newline 11");
        u("1 blank 12");
        u("12 blank 12");
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

                    if(final_states_names[last_final_state] != "white space") {

                        if(last_final_token[last_final_token.length() - 1] == '\n') {
                            last_final_token.pop_back();
                        }
                        std::cout << last_final_token << " " << final_states_names[last_final_state] << std::endl;
                    } else {
                        
                        std::cout << final_states_names[last_final_state] << std::endl;
                    }
                }

            } else {

                if (last_final_state != 0) {

                    if(final_states_names[last_final_state] != "white space") {
                        if(last_final_token[last_final_token.length() - 1] == '\n') {
                            last_final_token.pop_back();
                        }
                        std::cout << last_final_token << " " << final_states_names[last_final_state] << std::endl;
                    } else {
                        
                        std::cout << final_states_names[last_final_state] << std::endl;
                    }

                    i = last_final_state_position;
                    current_state = 1;
                    last_final_state = 0;
                    last_final_state_position = 0;
                    last_final_token = "";
                    current_token = "";
                } else {
                    std::cout << current_token << " error" << std::endl;
                    current_state = 1;
                    last_final_state = 0;
                    last_final_state_position = 0;
                    last_final_token = "";
                    current_token = "";
                }
            }
        }
    }

    // void sanitizeToken() {
    //     std::string::iterator start_pos = sentence.begin();
    //     std::string::reverse_iterator end_pos = sentence.rbegin();

    //     while (std::isspace(*start_pos)) {
    //         start_pos++;
    //     }

    //     while (std::isspace(*end_pos)) {
    //         end_pos++;
    //     }

    //     sentence = std::string(start_pos, end_pos.base());
    // }

    // std::string getToken() {

    //     sanitizeToken();

    //     std::stringstream ss(sentence);

    //     if(!sentence.empty())
    //         ss >> currentToken;
    //     else
    //         currentToken = std::string("");

    //     sentence.erase(0, currentToken.length());

    //     if(sentence.empty() && currentToken.empty()) {
    //         return "EOS";
    //     }

    //     return currentToken;
    // }
};
}  // namespace Compiler