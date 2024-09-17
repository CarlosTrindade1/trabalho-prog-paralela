#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <vector>

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
        int count_clicks(int k);
        void print();
        bool is_neighbor(int vertex_1, int vertex_2);

    private:
        int num_vertices;
        Vertex* vertices;

        map<int, int> rename_vertices(char* file_name_graph);
        void read_graph(char* file_name_graph, map<int, int> new_ids);
        bool is_on_click(vector<int> click, int vertex);
        bool makes_a_click(vector<int> click, int vertex);
};