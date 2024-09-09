#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>

struct Edge {
    int id;
    Edge* next;
};

struct Vertex {
    int id;
    Edge* edges;
};

class Graph {
    public:
        Graph(char *file_name);
        void print();

    private:
        int num_vertices;
        Vertex* vertices;

        void read_graph(char* file_name_graph);
};