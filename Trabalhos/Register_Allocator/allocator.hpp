#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

namespace allocator {

    class Vertex {
        public:
            int id;
            int register_assigned;
            bool print;
            bool active;
            bool virtual_register;
            std::map<int, Vertex*> interferences;

            Vertex(int id) {
                this->id = id;
                this->print = false;
                this->active = true;
                this->register_assigned = -1;
                this->virtual_register = false;
                this->interferences = std::map<int, Vertex*>();
            }
    };

    class Graph {
        public:
            int number;
            int virtual_registers_number;
            int available_registers;
            std::map<int, Vertex*> vertexes;
            int return_vertex_with_less_interferences();
            int return_vertex_with_most_interferences();
            bool exist_potential_spill(int current_available_registers);

            Graph(int number, int available_registers) {
                this->number = number;
                this->available_registers = available_registers;
                this->virtual_registers_number = 0;
                this->vertexes = std::map<int, Vertex*>();
            }
    };

    bool register_allocation(Graph* graph, int available_registers);

};