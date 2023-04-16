#include "ast_node.hh"

namespace mips {

    void print_consts_and_global_vars(std::vector<ast::AST_Constant*> consts, std::vector<ast::AST_Variable*> global_vars) {
        
        std::cout << ".data" << std::endl;

        for (auto c : consts) {
            std::cout << "\t" << *(c->name) << ": .word " << c->value << std::endl;
        }
        for (auto v : global_vars) {

            std::string type = *(v->type);

            if (type.find("*") != std::string::npos) { // pointer

                std::cout << "\t" << *(v->name) << ": .word 0" << std::endl;

            } else {

                int bytes = 0;
                int multiplier = calculate_bytes_multipler(type);

                if (type.find("int") != std::string::npos) {
                    bytes = 4 * multiplier;
                } else if (type.find("char") != std::string::npos) {
                    bytes = 1 * multiplier;
                } else if (type.find("void") != std::string::npos) {
                    std::cout << "Error: Incomplete void type not allowed" << std::endl;
                } else {
                    std::cout << "Error: Unknown type " << type << std::endl;
                }

                if (multiplier != 1) { // array
                    std::cout << "\t" << *(v->name) << ": .space " << bytes << std::endl;
                } else { // not array
                    std::cout << "\t" << *(v->name) << ": .word 0" << std::endl;
                }

            }

        }
    }

    int calculate_bytes_multipler(std::string type) {

        int multiplier = 1;

        for(int i = 0; i < type.length(); i++) {
            if (type[i] == '[') {
                int j = i + 1;
                std::string number = "";
                while (type[j] != ']') {
                    number += type[j];
                    j++;
                }
                multiplier *= std::stoi(number);
            }
        }

        return multiplier;
    }

    namespace ops {

        void exit() {
            std::cout << "\tli $v0, 10" << std::endl;
            std::cout << "\tsyscall" << std::endl;
        }

        void print_int() {
            std::cout << "\tli $v0, 1" << std::endl;
            std::cout << "\tsyscall" << std::endl;
        }

        void print_char() {
            std::cout << "\tli $v0, 11" << std::endl;
            std::cout << "\tsyscall" << std::endl;
        }

        void print_string() {
            std::cout << "\tli $v0, 4" << std::endl;
            std::cout << "\tsyscall" << std::endl;
        }

        void read_int() {
            std::cout << "\tli $v0, 5" << std::endl;
            std::cout << "\tsyscall" << std::endl;
        }

        void read_char() {
            std::cout << "\tli $v0, 12" << std::endl;
            std::cout << "\tsyscall" << std::endl;
        }

        void read_string() {
            std::cout << "\tli $v0, 8" << std::endl;
            std::cout << "\tsyscall" << std::endl;
        }
        
        void save_register_on_stack(std::string reg) {
            std::cout << "\tsw " << reg << ", 0($sp)" << std::endl;
            std::cout << "\taddiu $sp, $sp, -4" << std::endl;
        }

        void load_register_from_stack(std::string reg) {
            std::cout << "\taddiu $sp, $sp, 4" << std::endl;
            std::cout << "\tlw " << reg << ", 0($sp)" << std::endl;
        }

        void jump_and_link_function(std::string function_name) {
            std::cout << "\tjal " << function_name << std::endl;
        }

        void print_label(std::string label) {
            std::cout << label << ":" << std::endl;
        }

    };

}