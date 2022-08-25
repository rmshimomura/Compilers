#include "compiler.hpp"

int main () {

    Compiler::State q1("q1", "normal", "");
    Compiler::State q2("q2", "final", "ID");
    Compiler::State q3("q3", "final", "IF");
    Compiler::State q4("q4", "final", "ID");
    Compiler::State q5("q5", "final", "error");
    Compiler::State q6("q6", "final", "REAL");
    Compiler::State q7("q7", "final", "NUM");
    Compiler::State q8("q8", "final", "REAL");
    Compiler::State q9("q9", "final", "error");
    Compiler::State q10("q10", "normal", "");
    Compiler::State q11("q11", "final", "comment");
    Compiler::State q12("q12", "final", "white space");
    Compiler::State q13("q13", "final", "error");

    q1.addTransition('i', q2);
    q1.addTransition(a_h, q4);
    q1.addTransition(j_z, q4);
    q1.addTransition('.', q5);
    q1.addTransition(all_numbers, q7);
    q1.addTransition('-', q9);
    q1.addTransition(' ', q12);

    q2.addTransition('f', q3);
    q2.addTransition(a_e, q4);
    q2.addTransition(g_z, q4);
    q2.addTransition(all_numbers, q4);

    q3.addTransition(all_numbers, q4);
    q3.addTransition(all_letters, q4);

    q4.addTransition(all_letters, q4);
    q4.addTransition(all_numbers, q4);

    q5.addTransition(all_numbers, q6);

    q6.addTransition(all_numbers, q6);

    q7.addTransition(all_numbers, q7);
    q7.addTransition('.', q8);

    q8.addTransition(all_numbers, q8);

    q9.addTransition('-', q10);

    q10.addTransition(all_letters, q10);
    q10.addTransition('\n', q11);

    q12.addTransition(' ', q12);

    q13.addTransition(other, q13);

    Compiler::Automata automata(q1);

    automata.addState(q2);
    automata.addState(q3);
    automata.addState(q4);
    automata.addState(q5);
    automata.addState(q6);
    automata.addState(q7);
    automata.addState(q8);
    automata.addState(q9);
    automata.addState(q10);
    automata.addState(q11);
    automata.addState(q12);
    automata.addState(q13);

    std::string input = "";
    char c;
    while ((c = getchar()) != EOF) {
        input += c;
    }

    automata.inputString(input);

}