#include <iostream>
#include <vector>
#define all_letters -2
#define all_numbers -3

namespace Compiler {

class State {
    typedef struct transition {
        char input;
        State *state;
    } transition;

   private:
    std::vector<transition> transitions;

   public:
    std::string name, type, token;
    State(std::string name, std::string type, std::string token) : name(name), type(type), token(token) {}

    void addTransition(char input, State &state) {
        transitions.push_back({input, &state});
    }

    State *getNextState(char input) {
        for (auto &transition : transitions) {
            if (transition.input == input) {
                return transition.state;
            } else if (input >= 'a' && input <= 'z' && transition.input == all_letters) {
                return transition.state;
            } else if (input >= '0' && input <= '9' && transition.input == all_numbers) {
                return transition.state;
            }
        }
        return NULL;
    }
};

class Automata {
   private:
    std::vector<State> states;
    State *initialState;

   public:
    Automata(State &initialState) {
        this->initialState = &initialState;
        this->states.push_back(initialState);
    }
    void addState(State &state) {
        this->states.push_back(state);
    }

    void inputString(std::string input) {
        State *currentState = this->initialState;
        State *lastFinalState = NULL;
        std::string token = "";
        int lastFinalStateIndex = -1;
        int tokenStartIndex = 0;
        std::string currentFinalToken = "";
        int tokensCount = 0;

        for (int i = 0; i < input.size(); i++) {
            State *nextState = currentState->getNextState(input[i]);

            if (nextState) {
                if (!token.length()) {
                    tokenStartIndex = i;
                }

                currentState = nextState;
                token += input[i];

                if (currentState->type == "final") {
                    lastFinalState = currentState;
                    lastFinalStateIndex = i;
                    currentFinalToken = token;
                }

                if (i == input.length() - 1) {
                    if (lastFinalState) {
                        if (lastFinalState->token == "INTEIRO" || lastFinalState->token == "REAL") {
                            if (tokensCount > 0) {
                                std::cout << std::endl;
                            }

                            std::cout << lastFinalState->token << " " << currentFinalToken;

                        } else {
                            if (currentState->token == "ERRO") {
                            } else {
                                if (tokensCount > 0) {
                                    std::cout << std::endl;
                                }
                                std::cout << currentState->token;
                            }
                        }

                        tokensCount++;

                    } else {
                        if (currentState->token == "ERRO") {
                        } else {
                            if (tokensCount > 0) {
                                std::cout << std::endl;
                            }
                            std::cout << "ERRO";
                        }

                        tokensCount++;
                    }
                }

            } else {
                if (currentState->type == "normal") {  // Se eu estiver em um estado normal

                    if (lastFinalState) {  // Se eu tiver um estado final anterior

                        if (tokensCount > 0) {
                            std::cout << std::endl;
                        }

                        if (lastFinalState->token == "INTEIRO" || lastFinalState->token == "REAL") {
                            std::cout << lastFinalState->token << " " << currentFinalToken;

                        } else {
                            std::cout << lastFinalState->token;
                        }

                        // if(lastFinalStateIndex != input.length() - 1) {
                        //     std::cout << std::endl;
                        // }

                        tokensCount++;

                        currentState = this->initialState;
                        lastFinalState = NULL;
                        input = input.substr(lastFinalStateIndex + 1);
                        lastFinalStateIndex = -1;
                        token.clear();
                        i = -1;

                    } else {  // Se eu não tiver um estado final anterior

                        if (tokensCount > 0) {
                            std::cout << std::endl;
                        }

                        std::cout << "ERRO";

                        // if(tokenStartIndex != input.length() - 1) {
                        //     std::cout << std::endl;
                        // }
                        tokensCount++;

                        currentState = this->initialState;
                        lastFinalState = NULL;
                        lastFinalStateIndex = -1;
                        token.clear();
                        input = input.substr(tokenStartIndex + 1);  // A próxima string a ser analisada é a string atual sem o primeiro caractere
                        i = -1;
                    }

                } else if (currentState->type == "final") {  // Se eu estiver em um estado final

                    if (currentState->token == "ERRO") {
                        currentState = this->initialState;
                        lastFinalState = NULL;
                        lastFinalStateIndex = -1;
                        token.clear();
                        input = input.substr(i);
                        i = -1;
                        continue;
                    }

                    if (tokensCount > 0) {
                        std::cout << std::endl;
                    }

                    if (currentState->token == "INTEIRO" || currentState->token == "REAL") {
                        std::cout << currentState->token << " " << currentFinalToken;

                    } else {
                        std::cout << currentState->token;
                    }

                    tokensCount++;

                    // if(lastFinalStateIndex != input.length() - 1) {
                    //     std::cout << std::endl;
                    // }

                    currentState = this->initialState;
                    lastFinalState = NULL;
                    lastFinalStateIndex = -1;
                    token.clear();
                    input = input.substr(i);
                    i = -1;
                }
            }
        }
    }
};

}  // namespace Compiler