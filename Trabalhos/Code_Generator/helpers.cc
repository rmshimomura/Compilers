#include "ast_node.hh"

extern std::vector<ast::AST_Node_Strings*> node_strings;
extern bool used_registers[10];

namespace helpers {

    void split_format_string(std::string str, int node_number) {
        
        std::vector<std::string> tokens;

        std::string part = "";

        for(int i = 0; i < str.length(); i++) {
            if(str[i] == '%') {
                if(part == "") {
                    part += str[i];
                    part += str[i + 1];
                    tokens.push_back(part);
                    part = "";
                    i++;
                } else {
                    tokens.push_back(part);
                    part = "";
                    part += str[i];
                    part += str[i + 1];
                    tokens.push_back(part);
                    part = "";
                    i++;
                }
            } else {
                part += str[i];
            }
        }

        if(part != "") {
            tokens.push_back(part);
        }


        /*
        
            Not considering the case where the string is the type: %d%d%d%d%d
            Only considering the case where the string is the type: %d %d %d %d %d with mixed text also

        */
        
        ast::AST_Node_Strings* node = new ast::AST_Node_Strings(tokens, node_number);
        node_strings.push_back(node);
        

    }

    int return_first_unused_register() {
        for(int i = 0; i < 10; i++) {
            if(!used_registers[i]) {
                used_registers[i] = true;
                return i;
            }
        }
        return -1;
    }

};