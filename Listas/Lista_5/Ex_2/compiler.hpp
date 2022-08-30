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
        std::string currentFinalToken = "";

        int indexLastFinal = -1;
        State *ptrLastFinal = NULL;

        for (int index = 0; index < input.length(); index++) {

            State *nextState = currentState->getNextState(input[index]);

            if (input[index] != ' ' && input[index] != '\n') {
                currentToken += input[index];
            }

            if (nextState) {

                currentState = nextState;

                if (currentState->type == "final") {
                    indexLastFinal = index;
                    ptrLastFinal = currentState;
                    currentFinalToken = currentToken;
                    
                }

                if (index == input.length() - 1) {
                    if (ptrLastFinal) {
                        std::cout <<  currentFinalToken << " " << ptrLastFinal->token << std::endl;
                    } else {
                        std::cout <<  currentToken << " " << currentState->token << std::endl;
                    }
                }


            } else {

                if (ptrLastFinal) {

                    if (currentFinalToken.length() > 0) {
                        std::cout << currentFinalToken << " " << ptrLastFinal->token << std::endl;
                    } else {
                        std::cout << ptrLastFinal->token << std::endl;
                    }

                    index = indexLastFinal;
                    currentToken = "";
                    currentState = this->initialState;
                    ptrLastFinal = NULL;
                    indexLastFinal = -1;
                    currentFinalToken = "";


                } else {

                    if(currentToken.length() > 0) {
                        std::cout << currentToken << " error" << std::endl;
                    } else {
                        std::cout << currentState->token << std::endl;
                    }
                    currentToken = "";
                    currentState = this->initialState;

                }
            }

        }
    }
};

}  // namespace Compiler