#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <map>

using namespace std;

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

        map<int, int> rename_vertices(char* file_name_graph);
        void read_graph(char* file_name_graph, map<int, int> new_ids);
};