#include "compiler.hpp"

int main () {


    Compiler::State q1("q1");
    Compiler::State q2("q2");
    Compiler::State q3("q3");
    Compiler::State q4("q4");
    Compiler::State q5("q5");
    Compiler::State q6("q6");
    Compiler::State q7("q7");
    Compiler::State q8("q8");

    q1.addTransition(_a_z, q2);
    q1.addTransition(_0_9, q5);
    q1.addTransition('+', q3);
    q1.addTransition('-', q4);

    q2.addTransition(_a_z, q2);
    q2.addTransition(_0_9, q2);

    q5.addTransition(_0_9, q5);
    q5.addTransition('e', q6);

    q6.addTransition(_0_9, q8);
    q6.addTransition('+', q7);
    q6.addTransition('-', q7);

    q7.addTransition(_0_9, q8);

    q8.addTransition(_0_9, q8);

    Compiler::Automata automata(q1);

    automata.addState(q2);
    automata.addState(q3);
    automata.addState(q4);
    automata.addState(q5);
    automata.addState(q6);
    automata.addState(q7);
    automata.addState(q8);

    // std::string input = "\n+-abcabc@ abc\nfgh\n";

    // Keep reading the input while the character is different to Ctrl-D and store it on a string.
    std::string input = "";
    char c;
    while ((c = getchar()) != EOF) {
        input += c;
    }

    system("clear");

    std::cout << "String inputted:\n" << input << std::endl;

    automata.inputString(input);

}