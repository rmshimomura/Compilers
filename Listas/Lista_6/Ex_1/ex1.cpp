#include "compiler.hpp"

int main () {

    Compiler::State s1("s1", "normal", "");
    Compiler::State s2("s2", "normal", "");
    Compiler::State s3("s3", "final", "ELE");
    Compiler::State s4("s4", "normal", "");
    Compiler::State s5("s5", "normal", "");
    Compiler::State s6("s6", "final", "ELA");
    Compiler::State s7("s7", "normal", "");
    Compiler::State s8("s8", "final", "DELE");
    Compiler::State s9("s9", "normal", "");
    Compiler::State s10("s10", "final", "DELA");
    Compiler::State s11("s11", "normal", "");
    Compiler::State s12("s12", "normal", "");
    Compiler::State s13("s13", "final", "GATO");
    Compiler::State s14("s14", "final", "CARRO");
    Compiler::State s15("s15", "final", "GATOS");
    Compiler::State s16("s16", "final", "CARROS");
    Compiler::State s17("s17", "final", "MAIS");
    Compiler::State s18("s18", "final", "MENOS");
    Compiler::State s19("s19", "final", "INTEIRO");
    Compiler::State s20("s20", "normal", "");
    Compiler::State s21("s21", "normal", "");
    Compiler::State s22("s22", "final", "REAL");

    s1.addTransition('+', s17);
    s1.addTransition('-', s18);
    s1.addTransition(all_numbers, s19);
    s1.addTransition('h', s2);
    s1.addTransition('s', s4);
    s1.addTransition('c', s11);

    s2.addTransition('e', s3);
    s2.addTransition('i', s7);

    s3.addTransition('r', s9);

    s4.addTransition('h', s5);

    s5.addTransition('e', s6);

    s7.addTransition('s', s8);

    s9.addTransition('s', s10);

    s11.addTransition('a', s12);

    s12.addTransition('t', s13);
    s12.addTransition('r', s14);

    s13.addTransition('s', s15);

    s14.addTransition('s', s16);

    s19.addTransition(all_numbers, s19);
    s19.addTransition('e', s20);

    s20.addTransition('+', s21);
    s20.addTransition('-', s21);
    s20.addTransition(all_numbers, s22);

    s21.addTransition(all_numbers, s22);

    s22.addTransition(all_numbers, s22);

    Compiler::Automata automata(s1);

    automata.addState(s2);
    automata.addState(s3);
    automata.addState(s4);
    automata.addState(s5);
    automata.addState(s6);
    automata.addState(s7);
    automata.addState(s8);
    automata.addState(s9);
    automata.addState(s10);
    automata.addState(s11);
    automata.addState(s12);
    automata.addState(s13);
    automata.addState(s14);
    automata.addState(s15);
    automata.addState(s16);
    automata.addState(s17);
    automata.addState(s18);
    automata.addState(s19);
    automata.addState(s20);
    automata.addState(s21);
    automata.addState(s22);

    std::string input = "";
    char c;
    while ((c = getchar()) != EOF) {
        input += c;
    }

    automata.inputString(input);

}