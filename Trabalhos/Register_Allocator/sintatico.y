%{
    #include "allocator.hpp"
    extern int yylex(void);
    extern char* yytext;
    extern int yychar;
    extern int yydebug;
    extern void yyerror(char *s);
    extern void yylex_destroy(void);
    allocator::Graph* graph = new allocator::Graph(0, 0);
    int current_vertex_index = -1;
    std::vector<int> interferences;
    std::vector<bool> results;
%}

%union {
    int integer_token;
}

%token GRAFO
%token K_TOKEN
%token ARROW
%token<integer_token> NUM_INTEGER
%token NEWLINE
%token COLON
%token EQUAL

%type <integer_token> Graph_Number
%type <integer_token> Available_Registers

%start Programa

%%

Programa: Defs LoopInterferences;

LoopInterferences: Interferences NEWLINE LoopInterferences { };
                | Interferences { };

Defs: Graph_Number NEWLINE Available_Registers NEWLINE {
    graph->number = $1;
    graph->available_registers = $3;
};

Graph_Number: GRAFO NUM_INTEGER COLON { $$ = $2; };

Available_Registers: K_TOKEN EQUAL NUM_INTEGER { $$ = $3; };

Interferences: NUM_INTEGER ARROW LoopInteger {

    // Check if the vertex already exists
    if (graph->vertexes[$1] == nullptr) {
            
        allocator::Vertex* vertex = new allocator::Vertex($1);
        graph->vertexes[$1] = vertex;
    
    }

    graph->vertexes[$1]->print = true;

    // For each interference add vice versa
    for (auto interference : interferences) {

        if (graph->vertexes[interference] == nullptr) {
            
            allocator::Vertex* vertex = new allocator::Vertex(interference);
            graph->vertexes[interference] = vertex;
        
        }

        // Check if interference is already on the graph->vertexes[$1]->interferences
        int add = 1;

        for (auto const& [key, vertex] : graph->vertexes[$1]->interferences) {
            if (key == interference) {
                add = 0;
                break;
            }
        }

        if (add) graph->vertexes[$1]->interferences[interference] = graph->vertexes[interference];

        add = 1;

        // Check if $1 is already on the graph->vertexes[interference]->interferences
        for (auto const& [key, vertex] : graph->vertexes[interference]->interferences) {
            if (key == $1) {
                add = 0;
                break;
            }
        }

        if (add) graph->vertexes[interference]->interferences[$1] = graph->vertexes[$1];

    }

    interferences.clear();
    
};

LoopInteger: NUM_INTEGER LoopInteger {
    interferences.push_back($1);
};
            | {};

%%

int main(int argc, char **argv) {

    yyparse();

    std::cout << "Graph " << graph->number << " -> Physical Registers: " << graph->available_registers << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for(int i = graph->available_registers; i > 1; i--) {

        int virtual_registers = 0;

        for (auto const& [key, vertex] : graph->vertexes) {
                
            if(vertex->id > graph->available_registers) {
                virtual_registers++;
                vertex->virtual_register = true;
            } else {
                vertex->register_assigned = vertex->id;
            }

        }

        graph->virtual_registers_number = virtual_registers;

        std::cout << "K = " << i << std::endl;
        std::cout << std::endl;

        bool allocation_result = allocator::register_allocation(graph, i);

        if (allocation_result) {
            results.push_back(true);
        } else {
            results.push_back(false);
        }

        std::cout << "----------------------------------------" << std::endl;

    }

    std::cout << "----------------------------------------" << std::endl;

    for (int i = 0; i < results.size(); i++) {

        int space = graph->available_registers - i < 10 ? true : false;

        if (results[i]) {

            if (space) {
                std::cout << "Graph " << graph->number << " -> K =  " << graph->available_registers - i << ": Successful Allocation";
            } else {
                std::cout << "Graph " << graph->number << " -> K = " << graph->available_registers - i << ": Successful Allocation";
            }
        } else {
            if (space) {
                std::cout << "Graph " << graph->number << " -> K =  " << graph->available_registers - i << ": SPILL";
            } else {
                std::cout << "Graph " << graph->number << " -> K = " << graph->available_registers - i << ": SPILL";
            }
        }

        if (i + 1 < results.size()) {
            std::cout << std::endl;
        }
    }


    for (int i = 0; i < graph->vertexes.size(); i++) delete graph->vertexes[i];

    delete graph;

    yylex_destroy();

}