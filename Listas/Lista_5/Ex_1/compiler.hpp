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
    std::string name, type;
    State(std::string name, std::string type) : name(name), type(type) {}

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

    void inputString(std::string &input) {
        State *currentState = this->initialState;
        std::string currentToken = "";
        std::string currentFinalToken = "";

        int indexLastFinal = -1;
        State *ptrLastFinal = NULL;

        for (int index = 0; index < input.length(); index++) {
            if (input[index] == '\n') {
                if (ptrLastFinal != NULL) {
                    std::cout << currentFinalToken << std::endl;
                    currentFinalToken = "";
                    ptrLastFinal = NULL;
                }

                currentFinalToken = "";
                currentToken = "";
                currentState = this->initialState;
                ptrLastFinal = NULL;
                indexLastFinal = -1;
                continue;
            }

            State *nextState = currentState->getNextState(input[index]);
            
            if (nextState != NULL) {
                currentState = nextState;
                currentToken += input[index];
                if (currentState->type == "final") {
                    indexLastFinal = index;
                    ptrLastFinal = currentState;
                    currentFinalToken = currentToken;
                }

                if (index == input.length() - 1) {
                    if (currentState->type == "final") {
                        std::cout << currentFinalToken << std::endl;
                        currentFinalToken = "";
                        ptrLastFinal = NULL;
                    }

                    break;
                }

            } else {

                if (indexLastFinal != -1) {
                    std::cout << currentFinalToken << std::endl;
                    index = indexLastFinal;
                    currentState = this->initialState;
                    currentToken = "";
                    indexLastFinal = -1;
                    ptrLastFinal = NULL;
                    currentFinalToken = "";
                } else {
                    std::cout << "ERRO" << std::endl;
                    currentState = this->initialState;
                    currentToken = "";
                }
            }
        }
    }
};
}  // namespace Compiler