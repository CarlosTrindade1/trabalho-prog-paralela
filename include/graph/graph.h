#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <map>
#include <vector>
#include <math.h>
#include <pthread.h>

using namespace std;

class Graph {
    public:
        Graph(char *file_name);
        ~Graph();
        int count_clicks_serial(int k);
        int count_clicks_parallel(int k, int num_threads);
        int count_clicks_divide_parallel(int k, int num_threads, int r);
        void print();

    private:
        pthread_mutex_t mtx;

        struct Edge {
            int id;
            Edge* next;
        };

        struct Vertex {
            int id;
            Edge* edges;
        };

        struct shared_clicks {
            int thread_id;
            vector<vector<int>> clicks;
        };

        struct thread_args {
            int thread_id;
            int num_threads;
            Graph *graph;
            vector<vector<int>> clicks;
            shared_clicks *shared_c;
            int k;
            int r;
            int counter;
        };

        struct count_clicks_args {
            int thread_id;
            int num_threads;
            vector<vector<int>> clicks;
            shared_clicks *shared_c;
            bool is_divided;
            int k;
            int r;
        };

        int num_vertices;
        Vertex* vertices;

        static void* count_clicks_parallel_entry(void *args);
        static void* count_clicks_divide_parallel_entry(void *args);

        int count_clicks(count_clicks_args args);

        map<int, int> rename_vertices(char* file_name_graph);
        void read_graph(char* file_name_graph, map<int, int> new_ids);

        bool is_on_click(vector<int> click, int vertex);
        bool makes_a_click(vector<int> click, int vertex);
        bool is_neighbor(int vertex_1, int vertex_2);
};