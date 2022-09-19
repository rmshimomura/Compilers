#include <bits/stdc++.h>

#include "definitions.hpp"

namespace Compiler {

class Analyzer {
   public:
    std::string sentence;
    std::string currentToken;
    int token;
    int numberOfPrints = 0;

    void newLine() {
        if (numberOfPrints > 0) {
            std::cout << std::endl;
        }
    }

    int analyzeString() {
        token = getToken();

        return S();
    }

    void sanitizeToken() {
        std::string::iterator start_pos = sentence.begin();
        std::string::reverse_iterator end_pos = sentence.rbegin();

        while (std::isspace(*start_pos)) {
            start_pos++;
        }

        while (std::isspace(*end_pos)) {
            end_pos++;
        }

        sentence = std::string(start_pos, end_pos.base());
    }

    int getToken() {

        sanitizeToken();

        std::stringstream ss(sentence);

        if(!sentence.empty())
            ss >> currentToken;
        else
            currentToken = std::string("");

        sentence.erase(0, currentToken.length());

        if(sentence.empty() && currentToken.empty()) {
            return -2;
        }

        if (currentToken == "if") {
            return IF;
        } else if (currentToken == "then") {
            return THEN;
        } else if (currentToken == "else") {
            return ELSE;
        } else if (currentToken == "begin") {
            return BEGIN;
        } else if (currentToken == "end") {
            return END;
        } else if (currentToken == "print") {
            return PRINT;
        } else if (currentToken == ";") {
            return SEMI;
        } else if (currentToken == "=") {
            return EQ;
        } else {
            if (validNum(currentToken)) {
                return NUM;
            } else {
                return -1;
            }
        }
    }

    bool validNum(std::string received_token) {
        if (received_token.length() == 1 && (received_token[0] == '-' || received_token[0] == '+')) {
            return false;
        }

        for (int i = 0; i < received_token.length(); i++) {
            if (received_token[0] == '+' || received_token[0] == '-') {
                continue;
            }

            if (!isdigit(received_token[i])) {
                return false;
            }
        }

        return true;
    }

    int eat(int i) {

        if (i == token) {

            advance();

            return 1;

        } else if(i != token) {
            
            if(token == -2) {
                newLine();
                std::cout << "ERRO SINTATICO: CADEIA INCOMPLETA";
                numberOfPrints++;
                return 0;
            } else if (token == -1) {
                newLine();
                std::cout << "ERRO SINTATICO EM: " << currentToken  << " TOKEN NAO IDENTIFICADO";
                return 0;
            }

            newLine();
            std::cout << "ERRO SINTATICO EM: " << tokenNames[token] << " ESPERADO: " << tokenNames[i];
            numberOfPrints++;
            return 0;
        }

        return 1;
    }

    void advance() {
        token = getToken();
    }

    int S() {
        switch (token) {
            case IF: {
                if (!eat(IF)) return 0;

                if (!E()) return 0;

                if (!eat(THEN)) return 0;

                if (!S()) return 0;

                if (!eat(ELSE)) return 0;

                if (!S()) return 0;

                return 1;
            }
            case BEGIN: {
                if (!eat(BEGIN)) return 0;

                if (!S()) return 0;

                if (!L()) return 0;

                return 1;
            }
            case PRINT: {
                if (!eat(PRINT)) return 0;

                if (!E()) return 0;

                return 1;
            }
            default: {
                newLine();

                if(token == -1) {
                    std::cout << "ERRO SINTATICO EM: " << currentToken  << " ESPERADO: " << tokenNames[IF] << ", " << tokenNames[BEGIN] << ", " << tokenNames[PRINT];
                } else {
                    std::cout << "ERRO SINTATICO EM: " << tokenNames[token] << " ESPERADO: " << tokenNames[IF] << ", " << tokenNames[BEGIN] << ", " << tokenNames[PRINT];
                }

                numberOfPrints++;
                return 0;
            }
        }
    }

    int L() {
        switch (token) {
            case END: {
                if (!eat(END)) return 0;
                return 1;
            }
            case SEMI: {
                if (!eat(SEMI)) return 0;

                if (!S()) return 0;

                if (!L()) return 0;

                return 1;
            }
            default: {
                newLine();
                if(token == -1) {
                    std::cout << "ERRO SINTATICO EM: " << currentToken  << " ESPERADO: " << tokenNames[END] << ", " << tokenNames[SEMI];
                } else {
                    std::cout << "ERRO SINTATICO EM: " << tokenNames[token] << " ESPERADO: " << tokenNames[END] << ", " << tokenNames[SEMI];
                }
                numberOfPrints++;
                return 0;
            }
        }

        return 1;
    }

    int E() {
        if (!eat(NUM)) return 0;

        if (!eat(EQ)) return 0;

        if (!eat(NUM)) return 0;

        return 1;
    }
};
}  // namespace Compiler