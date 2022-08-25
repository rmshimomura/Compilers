#include <iostream>
#include <vector>
#define all_letters -2
#define all_numbers -3
#define a_h -4
#define i -5
#define j_z -6
#define a_e -7
#define g_z -8
#define other -9

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
            } else if (input >= 'a' && input <= 'h' && transition.input == a_h) {
                return transition.state;
            } else if (input == 'i' && transition.input == i) {
                return transition.state;
            } else if (input >= 'j' && input <= 'z' && transition.input == j_z) {
                return transition.state;
            } else if (input >= 'a' && input <= 'e' && transition.input == a_e) {
                return transition.state;
            } else if (input >= 'g' && input <= 'z' && transition.input == g_z) {
                return transition.state;
            } else if (transition.input == other) {
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

    void inputString(std::string &input) {
        
        State *currentState = this->initialState;
        std::string currentToken = "";

        std::cout << std::endl;

        for (int index = 0; index < input.length(); index++) {

            if (input[index] == '\n' && currentToken.length() == 0) {
                currentToken = "";
                continue;
            }

            State *nextState = currentState->getNextState(input[index]);

            currentToken += input[index];

            if (nextState != NULL) {

                currentState = nextState;

                if (index == input.length() - 1 && input[index] == '\n') {
                    currentToken.pop_back();
                    std::cout << currentToken << " " << currentState->token << std::endl;
                }

            } else if (nextState == NULL) {
                
                if(currentToken.length() > 0 && currentState->type == "final" && currentToken[0] != ' ') {

                    currentToken.pop_back();
                    index--;

                    if(currentToken[currentToken.length() - 1] == '\n') {
                        currentToken.pop_back();
                        index--;
                    }

                    std::cout << currentToken << " " << currentState->token << std::endl;
                    currentToken = "";
                    currentState = this->initialState;

                } else if(currentState->type == "final" && currentToken[0] == ' ') {

                    std::cout << currentState->token << std::endl;
                    currentToken = "";
                    currentState = this->initialState;
                    index--;

                } else {

                    std::cout << currentToken << " error" << std::endl;
                    currentToken = "";
                    currentState = this->initialState;
                }

            }
        }
    }
};

}  // namespace Compiler