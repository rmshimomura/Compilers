#include "allocator.hpp"

int allocator::Graph::return_vertex_with_less_interferences() {

    int less_interferences = 999999;
    allocator::Vertex* less_interferences_vertex = nullptr;

    for (auto const& [key, vertex] : this->vertexes) {
        if (vertex->active && vertex->id >= this->available_registers) {
            
            int interferences = 0;

            for (auto const& [key, interference] : vertex->interferences) {
                if (interference->active) {
                    interferences++;
                }
            }

            if (interferences < less_interferences) {
                less_interferences = interferences;
                less_interferences_vertex = vertex;
            } else if (interferences == less_interferences) {
                if (vertex->id < less_interferences_vertex->id) {
                    less_interferences_vertex = vertex;
                }
            }

        }
    }

    return less_interferences_vertex->id;

}

int allocator::Graph::return_vertex_with_most_interferences() {
    
    int most_interferences = -1;
    allocator::Vertex* most_interferences_vertex = nullptr;

    for (auto const& [key, vertex] : this->vertexes) {

        if (vertex->active && vertex->id >= this->available_registers) {
            
            int interferences = 0;

            for (auto const& [key, interference] : vertex->interferences) {
                if (interference->active) {
                    interferences++;
                }
            }

            if (interferences > most_interferences) {
                most_interferences = interferences;
                most_interferences_vertex = vertex;
            } else if (interferences == most_interferences) {
                if (vertex->id < most_interferences_vertex->id) {
                    most_interferences_vertex = vertex;
                }
            }

        }
    }

    return most_interferences_vertex->id;

}

bool allocator::Graph::exist_potential_spill(int current_available_registers) {
    
    int interferences = 0;

    for (auto const& [key, vertex] : this->vertexes) {
        if (vertex->active && vertex->id >= this->available_registers) {
            for (auto const& [key, interference] : vertex->interferences) {
                if (interference->active) {
                    interferences++;
                }
            }

            if (interferences < current_available_registers) {
                return false;
            } else {
                interferences = 0;
            }
        }
    }

    return true;

}

bool allocator::register_allocation(allocator::Graph* graph, int available_registers) {
    
    std::stack<Vertex*> stack;

    bool status = true;

    for (int i = 0; i < graph->virtual_registers_number; i++) {

        int vertex_id = -1;

        int potential_spill = graph->exist_potential_spill(available_registers);

        if (potential_spill) {
            vertex_id = graph->return_vertex_with_most_interferences();
        } else {
            vertex_id = graph->return_vertex_with_less_interferences();
        }

        Vertex* vertex = graph->vertexes[vertex_id];

        vertex->active = false;

        stack.push(vertex);

        if (vertex->print) {
            std::cout << "Push: " << vertex->id << (potential_spill ? " *" : "") << std::endl;
        }

    }

    for (int i = 0; i < graph->virtual_registers_number; i++) {

        Vertex* vertex = stack.top();
        stack.pop();

        vertex->active = true;

        bool used_registers[available_registers] = {0};

        for (auto const& [key, interference] : vertex->interferences) {
            if (interference->active && interference->register_assigned != -1 && interference->register_assigned < available_registers) {
                used_registers[interference->register_assigned] = true;
            }
        }

        int error = true;

        for (int j = 0; j < available_registers; j++) {
            if (!used_registers[j]) {
                vertex->register_assigned = j;
                error = false;
                break;
            }
        }
        
        if (error) {

            if (vertex->print) {
                std::cout << "Pop: " << vertex->id << " -> NO COLOR AVAILABLE" << std::endl;
                status = false;
            }

            break;

        } else {

            if (vertex->print) {
                std::cout << "Pop: " << vertex->id << " -> " << vertex->register_assigned << std::endl;
            }

        }

        for (auto const& [key, interference] : vertex->interferences) {
            interference->active = true;
        }
        
    }

    for (auto const& [key, vertex] : graph->vertexes) {

        vertex->active = true;

        if (vertex->virtual_register) {
            vertex->register_assigned = -1;
        }

    }

    return status;

}