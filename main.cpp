#include <graph.h>
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char* argv[]) {
    if (!argv[1]) {
        printf("filename was not provided\n");
        return 1;
    }

    if (!argv[2]) {
        printf("size of click was not provided\n");
        return 1;
    }

    if (!argv[3]) {
        printf("number of algorithm was not provided\n");
        return 1;
    }

    char* file_name_graph = argv[1];
    int size_of_click = atoi(argv[2]);
    int algorithm = atoi(argv[3]);
    int r = 0;

    Graph *graph = new Graph(file_name_graph);

    chrono::high_resolution_clock::time_point start, end;

    int num_of_threads = std::thread::hardware_concurrency();

    switch (algorithm) {
        case 0:
            start = chrono::high_resolution_clock::now();
            cout << graph->count_clicks_serial(size_of_click) << endl;
            end = chrono::high_resolution_clock::now();
            break;

        case 1:
            start = chrono::high_resolution_clock::now();
            cout << graph->count_clicks_parallel(size_of_click, num_of_threads) << endl;
            end = chrono::high_resolution_clock::now();
        break;

        case 2:
            if (!argv[4]) {
                printf("r parameter was not provided\n");
                return 1;
            }

            r = atoi(argv[4]);

            start = chrono::high_resolution_clock::now();
            cout << graph->count_clicks_divide_parallel(size_of_click, num_of_threads, r) << endl;
            end = chrono::high_resolution_clock::now();
        break;

        default:
            break;
    }

    printf("Execution time of the %d algorithm: ", algorithm);
    cout << chrono::duration_cast<chrono::duration<double>>(end - start).count() << " s" << endl;

    delete graph;

    return 0;
}