#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <vector>
#include <math.h>

using namespace std;

class Graph {
    public:
        Graph(char *file_name);
        int count_clicks_serial(int k);
        int count_clicks_parallel(int k, int num_threads);
        void print();

    private:
        struct Edge {
            int id;
            Edge* next;
        };

        struct Vertex {
            int id;
            Edge* edges;
        };
        struct thread_args {
            Graph *graph;
            vector<vector<int>> *clicks;
            int k;
            int counter;
        };

        int num_vertices;
        Vertex* vertices;

        static void* count_clicks_entry(void *args);
        int count_clicks(vector<vector<int>> clicks, int k);
        map<int, int> rename_vertices(char* file_name_graph);
        void read_graph(char* file_name_graph, map<int, int> new_ids);
        bool is_on_click(vector<int> click, int vertex);
        bool makes_a_click(vector<int> click, int vertex);
        bool is_neighbor(int vertex_1, int vertex_2);
};