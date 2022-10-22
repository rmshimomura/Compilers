#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
#include <stack>

std::vector<std::vector<std::string>> valid_strings;

namespace Compiler {

class Lexic_Analyzer {
   public:
    std::string sentence;
    

    int transistions_table[8][127]{0};
    int final_states[8]{0, 0, 1, 1, 1, 1, 1, 1};

    void initialize_matrix() {
        u("1 az 2");
        u("2 az 2");
        u("2 09 2");
        u("1 + 3");
        u("1 * 4");
        u("1 ( 5");
        u("1 ) 6");
        u("1 $ 7");
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

                if (final_states[current_state] == 1) {
                    last_final_state = current_state;
                    last_final_state_position = i;
                    last_final_token = current_token;
                }

                if (i == line.length() - 1) {
                    if (final_states[current_state] == 1) {
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
                    if (line[i] == ' ') {
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
    int pos_of_current_token = 0;
    std::string token;
    std::stack<std::string> stack_analyzer;
    std::vector<std::string> sentence;

    void syntax_analyze() {
        for (int sentences_iterator = 0; sentences_iterator < valid_strings.size(); sentences_iterator++) {

            if(valid_strings[sentences_iterator].size()) {
                
                if (valid_strings[sentences_iterator][0].find("ERRO LEXICO: ") != std::string::npos) {
                    continue;
                }

            }
            
            sentence = valid_strings[sentences_iterator];
            analyze_string(sentences_iterator);

        }
    }

    void analyze_string(int sentences_iterator) {

        if(!sentence.size()) {
            valid_strings[sentences_iterator].clear();
            valid_strings[sentences_iterator].push_back("ERRO SINTATICO:  ESPERADO: id, (");
            return;
        }

        stack_analyzer = std::stack<std::string>();
        stack_analyzer.push("S");

        std::vector<std::string> syntactic_accepted;

        int k = 0;

        token = sentence[k]; 

        while(k < sentence.size() - 1) {

            std::string stack_top = stack_analyzer.top();

            for (int w = 0; w < syntactic_accepted.size(); w++) {
                std:: cout << syntactic_accepted[w] << " ";
            }

            std::cout << std::endl;

            printf("\n%s-%s\n", stack_top.c_str(), token.c_str());

            if (token == "+") {
                if(stack_top == "E\'") {
                    stack_analyzer.pop();
                    stack_analyzer.push("E\'");
                    stack_analyzer.push("T");
                    syntactic_accepted.push_back("+");
                    k++;
                    if(k == sentence.size() - 1 && stack_analyzer.top() != "$" && sentence[k] != "$") {
                        std::string custom_error = "ERRO SINTATICO: " + sentence[k];
                        if(stack_analyzer.top() == "E") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "T") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "F") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "E\'") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: +, ), $");
                        } else if (stack_analyzer.top() == "T\'") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: +, *, ), $");
                        }
                        return;
                    }
                    token = sentence[k];
                } else if(stack_top == "T\'") {
                    stack_analyzer.pop();
                } else if(stack_top == "E" || stack_top == "T" || stack_top == "F" || stack_top == "S") {
                    valid_strings[sentences_iterator].clear();
                    valid_strings[sentences_iterator].push_back("ERRO SINTATICO: + ESPERADO: id, (");
                    return;
                } else {
                    syntactic_accepted.push_back(stack_analyzer.top());
                    stack_analyzer.pop();
                    if(stack_analyzer.top() != "$") {

                        k++;
                        token = sentence[k];
                    }
                }

            } else if (token == "*") {
                if(stack_top == "T\'") {
                    stack_analyzer.pop();
                    stack_analyzer.push("T\'");
                    stack_analyzer.push("F");
                    syntactic_accepted.push_back("*");
                    k++;
                    if(k == sentence.size() - 1 && stack_analyzer.top() != "$" && sentence[k] != "$") {
                        std::string custom_error = "ERRO SINTATICO: " + sentence[k];
                        if(stack_analyzer.top() == "E") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "T") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "F") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "E\'") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: +, ), $");
                        } else if (stack_analyzer.top() == "T\'") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: +, *, ), $");
                        }
                        return;
                    }
                    token = sentence[k];
                } else if(stack_top == "E" || stack_top == "T" || stack_top == "F" || stack_top == "S") {
                    valid_strings[sentences_iterator].clear();
                    valid_strings[sentences_iterator].push_back("ERRO SINTATICO: * ESPERADO: id, (");
                    return;
                } else {
                    syntactic_accepted.push_back(stack_analyzer.top());
                    stack_analyzer.pop();
                    if(stack_analyzer.top() != "$") {

                        k++;
                        token = sentence[k];
                    }
                }
            } else if (token == "(") {
                if(stack_top == "E") {
                    stack_analyzer.pop();
                    stack_analyzer.push("E\'");
                    stack_analyzer.push("T");
                } else if (stack_top == "T") {
                    stack_analyzer.pop();
                    stack_analyzer.push("T\'");
                    stack_analyzer.push("F");
                } else if(stack_top == "F") {
                    stack_analyzer.pop();
                    stack_analyzer.push(")");
                    stack_analyzer.push("E");
                    syntactic_accepted.push_back("(");
                    k++;
                    if(k == sentence.size() - 1 && stack_analyzer.top() != "$" && sentence[k] != "$") {
                        std::string custom_error = "ERRO SINTATICO: " + sentence[k];
                        if(stack_analyzer.top() == "E") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "T") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "F") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "E\'") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: +, ), $");
                        } else if (stack_analyzer.top() == "T\'") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: +, *, ), $");
                        }
                        return;
                    }
                    token = sentence[k];
                } else if (stack_top == "S") {
                    stack_analyzer.pop();
                    stack_analyzer.push("$");
                    stack_analyzer.push("E");
                } else if (stack_top == "E\'" || stack_top == "T\'") {
                    valid_strings[sentences_iterator].clear();
                    valid_strings[sentences_iterator].push_back("ERRO SINTATICO: ( ESPERADO: +, *, ), $");
                    return;
                } else {
                    syntactic_accepted.push_back(stack_analyzer.top());
                    stack_analyzer.pop();

                    if(stack_analyzer.top() != "$") {

                        k++;
                        token = sentence[k];
                    }
                }
            } else if (token == ")") {
                if(stack_top == "E\'") {
                    stack_analyzer.pop();
                } else if(stack_top == "T\'") {
                    stack_analyzer.pop();
                } else if(stack_top == "E" || stack_top == "T" || stack_top == "F" || stack_top == "S") {
                    valid_strings[sentences_iterator].clear();
                    valid_strings[sentences_iterator].push_back("ERRO SINTATICO: ) ESPERADO: id, (");
                    return;
                } else if (stack_top == "$") {

                    valid_strings[sentences_iterator].clear();
                    valid_strings[sentences_iterator].push_back("ERRO SINTATICO: ) ESPERADO: $");
                    return;

                } else {
                    syntactic_accepted.push_back(stack_analyzer.top());
                    stack_analyzer.pop();
                    if(stack_analyzer.top() != "$") {

                        k++;
                        token = sentence[k];
                    }
                }
            } else if (token == "$") {
                if(stack_top == "E\'") {
                    stack_analyzer.pop();
                } else if(stack_top == "T\'") {
                    stack_analyzer.pop();
                } else if(stack_top == "E" || stack_top == "T" || stack_top == "F" || stack_top == "S") {
                    valid_strings[sentences_iterator].clear();
                    valid_strings[sentences_iterator].push_back("ERRO SINTATICO: $ ESPERADO: id, (");
                    return;
                } else {
                    syntactic_accepted.push_back(stack_analyzer.top());
                    stack_analyzer.pop();
                    if(stack_analyzer.top() != "$") {

                        k++;
                        token = sentence[k];
                    }
                }

                if(stack_analyzer.empty() && k != sentence.size() - 1) {
                    valid_strings[sentences_iterator].clear();
                    valid_strings[sentences_iterator].push_back("ERRO SINTATICO:  ESPERADO: id, (");
                    return;
                }

            } else { 

                if(stack_top == "E") {
                    stack_analyzer.pop();
                    stack_analyzer.push("E\'");
                    stack_analyzer.push("T");
                } else if (stack_top == "T") {
                    stack_analyzer.pop();
                    stack_analyzer.push("T\'");
                    stack_analyzer.push("F");
                } else if(stack_top == "F") {
                    stack_analyzer.pop();
                    syntactic_accepted.push_back(token);
                    k++;
                    if(k == sentence.size() - 1 && stack_analyzer.top() != "$" && sentence[k] != "$") {
                        std::string custom_error = "ERRO SINTATICO: " + sentence[k];
                        if(stack_analyzer.top() == "E") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "T") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "F") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: id, (");
                        } else if (stack_analyzer.top() == "E\'") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: $");
                        } else if (stack_analyzer.top() == "T\'") {
                            valid_strings[sentences_iterator].clear();
                            valid_strings[sentences_iterator].push_back(custom_error + " ESPERADO: $");
                        }
                        return;
                    }
                    token = sentence[k];
                } else if (stack_top == "S") {
                    stack_analyzer.pop();
                    stack_analyzer.push("$");
                    stack_analyzer.push("E");
                } else if (stack_top == "E\'" || stack_top == "T\'") {

                    std::string result_string = token == "$" ? "$" : "id";
                    valid_strings[sentences_iterator].clear();
                    valid_strings[sentences_iterator].push_back("ERRO SINTATICO: " + result_string + " ESPERADO: +, *, ), $");
                    return;
                } else {
                    syntactic_accepted.push_back(stack_analyzer.top());
                    stack_analyzer.pop();
                    k++;
                    token = sentence[k];
                }
            }

        }

        valid_strings[sentences_iterator].clear();
        valid_strings[sentences_iterator].push_back("CADEIA ACEITA");

    }

    void results() {
        for (int sentences_iterator = 0; sentences_iterator < valid_strings.size(); sentences_iterator++) {
            if (valid_strings[sentences_iterator].size() == 1) {
                std::cout << valid_strings[sentences_iterator][0] << std::endl;
            } else {
                for (int tokens_iterator = 0; tokens_iterator < valid_strings[sentences_iterator].size(); tokens_iterator++) {
                    std::cout << valid_strings[sentences_iterator][tokens_iterator] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
};

}  // namespace Compiler