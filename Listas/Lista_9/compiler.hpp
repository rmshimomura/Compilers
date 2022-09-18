#include <bits/stdc++.h>
#include "definitions.hpp"


namespace Compiler {
    
    class Analyzer {

    public:

        std::string sentence;
        std::string currentToken;
        int token;
        int currentLine;
        bool accepted = true;
        int numberOfPrints = 0;


        void newLine() {
            if(numberOfPrints > 0) {
                std::cout << std::endl;
            }
        } 

        void analyzeString() {

            token = getToken();

            S();

        }

        int getToken(){

            sanitizeToken();

            std::stringstream ss(sentence);
            ss >> currentToken;
            
            sentence.erase(0, sentence.find(" ") + 1);

            if(currentToken == "if"){
                return IF;
            } else if(currentToken == "then"){
                return THEN;
            } else if(currentToken == "else"){
                return ELSE;
            } else if(currentToken == "begin"){
                return BEGIN;
            } else if(currentToken == "end"){
                return END;
            } else if(currentToken == "print"){
                return PRINT;
            } else if(currentToken == ";"){
                return SEMI;
            } else if(currentToken == "="){
                return EQ;
            } else {

                if(validNum(currentToken)) {
                    return NUM;
                } else {
                    return -1;
                }

            }

        }

        bool validNum(std::string received_token){

            if(received_token.length() == 1 && (received_token[0] == '-' || received_token[0] == '+')){
                return false;
            }

            for(int i = 0; i < received_token.length(); i++){
                
                if(received_token[0] == '+' || received_token[0] == '-'){
                    continue;
                }
                
                if(!isdigit(received_token[i])){
                    return false;
                }

            }

            return true;

        }

        void eat(int i) {

            if(i == token) {
                advance();
            } else {
                newLine();
                std::cout << "ERRO SINTATICO EM: " << tokenNames[token] << " ESPERADO: " << tokenNames[i];
                accepted = false;
                numberOfPrints++;
                return;
            }

        }

        void advance() {

            token = getToken();

        }

        void sanitizeToken() {
            
            std::string::iterator start_pos = sentence.begin();
            std::string::reverse_iterator end_pos = sentence.rbegin();

            while(std::isspace(*start_pos)) {
                start_pos++;
            }

            while(std::isspace(*end_pos)) {
                end_pos++;
            }

            sentence = std::string(start_pos, end_pos.base());

            sentence.push_back(' ');


        }

        void S() {

            switch(token) {

                case IF: {

                    eat(IF);
                    if(accepted) {
                        E();
                        if(accepted) {
                            eat(THEN);
                            if(accepted) {
                                S();
                                if(accepted) {
                                    eat(ELSE);
                                    if(accepted) {
                                        S();
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                case BEGIN: {
                    eat(BEGIN); 
                    if(accepted) {
                        S();
                        if(accepted) {
                            L();
                        }
                    }
                    break;
                } 
                case PRINT: {
                    eat(PRINT); 
                    if(accepted) {
                        E();
                    }
                    break;
                }
                default: {
                    newLine();
                    std::cout << "ERRO SINTATICO EM: " << tokenNames[token] << " ESPERADO: " << tokenNames[IF] << ", " << tokenNames[BEGIN] << ", " << tokenNames[PRINT]; accepted = false; 
                    numberOfPrints++; 
                    break;
                }
                
            }

        }

        void L() {

            switch(token) {
                case END: {
                    eat(END); 
                    break;
                } 
                case SEMI: {
                    eat(SEMI); 
                    if(accepted) {
                        S();
                        if(accepted) {
                            L();
                        }
                    }
                    break;
                }
                default: {

                    newLine();
                    std::cout << "ERRO SINTATICO EM: " << tokenNames[token] << " ESPERADO: " << tokenNames[END] << ", " << tokenNames[SEMI]; 
                    accepted = false; 
                    numberOfPrints++; 
                    break;

                }
            }

        }

        void E() {

            eat(NUM); 
            if(accepted) {
                eat(EQ); 
                if(accepted) {
                    eat(NUM); 
                }
            }

        }

    };
}