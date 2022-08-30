#include "compiler.hpp"

int main () {


    Compiler::State q1("q1", "normal");
    Compiler::State q2("q2", "final");
    Compiler::State q3("q3", "final");
    Compiler::State q4("q4", "final");
    Compiler::State q5("q5", "final");
    Compiler::State q6("q6", "normal");
    Compiler::State q7("q7", "normal");
    Compiler::State q8("q8", "final");

    q1.addTransition(all_letters, q2);
    q1.addTransition(all_numbers, q5);
    q1.addTransition('+', q3);
    q1.addTransition('-', q4);

    q2.addTransition(all_letters, q2);
    q2.addTransition(all_numbers, q2);

    q5.addTransition(all_numbers, q5);
    q5.addTransition('e', q6);

    q6.addTransition(all_numbers, q8);
    q6.addTransition('+', q7);
    q6.addTransition('-', q7);

    q7.addTransition(all_numbers, q8);

    q8.addTransition(all_numbers, q8);

    Compiler::Automata automata(q1);

    automata.addState(q2);
    automata.addState(q3);
    automata.addState(q4);
    automata.addState(q5);
    automata.addState(q6);
    automata.addState(q7);
    automata.addState(q8);

    std::string input = "";
    char c;
    while ((c = getchar()) != EOF) {
        input += c;
    }

    automata.inputString(input);

}