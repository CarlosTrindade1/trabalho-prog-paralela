#include <graph.h>

using namespace std;

int main(int argc, char* argv[]) {
    char* file_name_graph = argv[1];
    int size_of_click = atoi(argv[2]);

    Graph *graph = new Graph(file_name_graph);

    cout << graph->count_clicks_divide_parallel(size_of_click, 4) << endl;

    delete graph;

    return 0;
}