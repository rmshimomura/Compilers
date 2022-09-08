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

            State *nextState = currentState->getNextState(input[i]); // Attempt to get next state

            if (nextState) { // If there is a next state

                if (!token.length()) tokenStartIndex = i; // If token is empty, set token start index

                currentState = nextState;
                token += input[i];

                if (currentState->type == "final") { // If current state is final
                    lastFinalState = currentState;
                    lastFinalStateIndex = i;
                    currentFinalToken = token;
                }

                if (i == input.length() - 1) { // If it is the last character

                    if (lastFinalState) { // If there is a final state

                        if (lastFinalState->token == "INTEIRO" || lastFinalState->token == "REAL") { // If it is a number

                            tokensCount > 0 ? std::cout << std::endl << lastFinalState->token << " " << currentFinalToken : std::cout << lastFinalState->token << " " << currentFinalToken;

                        } else { // If it is not a number

                            if (currentState->token != "ERRO") tokensCount > 0 ? std::cout << std::endl << currentState->token : std::cout << std::endl;

                        }

                        tokensCount++;

                    } else { // If there is no final state

                        if (currentState->token != "ERRO") tokensCount > 0 ? std::cout << std::endl << "ERRO" : std::cout << std::endl;

                        tokensCount++;

                    }

                }

            } else {

                if (currentState->type == "normal") {  // If current state is normal

                    if (lastFinalState) {  // If there is a final state

                        if (tokensCount > 0) {
                            std::cout << std::endl;
                        }

                        if (lastFinalState->token == "INTEIRO" || lastFinalState->token == "REAL") {
                            std::cout << lastFinalState->token << " " << currentFinalToken;

                        } else {
                            std::cout << lastFinalState->token;
                        }

                        tokensCount++;

                        currentState = this->initialState;
                        lastFinalState = NULL;
                        input = input.substr(lastFinalStateIndex + 1);
                        lastFinalStateIndex = -1;
                        token.clear();
                        i = -1;

                    } else { // If there is no final state

                        if (tokensCount > 0) {
                            std::cout << std::endl;
                        }

                        std::cout << "ERRO";

                        tokensCount++;

                        currentState = this->initialState;
                        lastFinalState = NULL;
                        lastFinalStateIndex = -1;
                        token.clear();
                        input = input.substr(tokenStartIndex + 1);  // Remove first character from input
                        i = -1;
                    }

                } else if (currentState->type == "final") {  // If current state is final

                    if (currentState->token == "ERRO") { // If current state is error
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

                    if (currentState->token == "INTEIRO" || currentState->token == "REAL") { // If it is a number
                    
                        std::cout << currentState->token << " " << currentFinalToken;

                    } else { // If it is not a number

                        std::cout << currentState->token;
                    }

                    tokensCount++;

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