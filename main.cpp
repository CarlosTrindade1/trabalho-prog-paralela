#include <graph.h>

using namespace std;

int main(int argc, char* argv[]) {
    char* file_name_graph = argv[1];
    int size_of_click = atoi(argv[2]);
    int algorithm = atoi(argv[3]);
    int r = atoi(argv[4]);

    Graph *graph = new Graph(file_name_graph);

    switch (algorithm) {
        case 0:
            cout << graph->count_clicks_serial(size_of_click) << endl;
        break;

        case 1:
            cout << graph->count_clicks_parallel(size_of_click, 8) << endl;
        break;

        case 2:
            cout << graph->count_clicks_divide_parallel(size_of_click, 8, r) << endl;
        break;

        default:
            break;
    }

    delete graph;

    return 0;
}