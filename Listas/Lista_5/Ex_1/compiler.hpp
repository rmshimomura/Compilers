#include <iostream>
#include <vector>
#define all_letters -2
#define all_numbers -3

namespace Compiler {

    class State {

        typedef struct transition {
            char input;
            State* state;
        } transition;

    private:

        std::vector<transition> transitions;

    public:

        std::string name;
        State(std::string name) : name(name) {}

        void addTransition(char input, State &state) {
            transitions.push_back({input, &state});
        }

        State* getNextState(char input) {
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
            for (int index = 0; index < input.length(); index++) {

                if (input[index] == '\n') {
                    std::cout << currentToken << std::endl;
                    currentToken = "";
                    continue;
                }

                State* nextState = currentState->getNextState(input[index]);

                if (nextState != NULL) {
                    currentState = nextState;
                    currentToken += input[index];
                } else if (currentToken.length() > 0) {
                    std::cout << currentToken << std::endl;
                    currentToken = "";
                    currentState = this->initialState;
                    index--;
                } else {
                    std::cout << "ERROR" << std::endl;
                    currentState = this->initialState;
                }
                
            }
            std::cout << currentToken << std::endl;
        }
    };

}  // namespace Compiler