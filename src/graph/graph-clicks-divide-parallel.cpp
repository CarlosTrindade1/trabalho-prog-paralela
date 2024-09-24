#include <graph.h>

void print_clicks(vector<vector<int>> clicks) {
    for (int i = 0; i < clicks.size(); i++) {
        for (int j = 0; j < clicks[i].size(); j++) {
            cout << clicks[i][j] << " ";
        }
        cout << endl;
    }
}

int Graph::count_clicks_divide_parallel(int k, int num_threads) {
    vector<vector<int>> clicks(num_vertices, vector<int>(1));
    int counter = 0;

    // Add all vertices to the clicks array
    for (int i = 0; i < num_vertices; i++) {
        clicks[i].pop_back();
        clicks[i].push_back(vertices[i].id);
    }

    pthread_t *threads = new pthread_t[num_threads];

    int vertices_per_thread = ceil(num_vertices / num_threads);

    shared_clicks *args = new shared_clicks[num_threads];

    for (int i = 0; i < num_threads; i++) {
        int start = i * vertices_per_thread;
        int end = (i + 1) * vertices_per_thread;

        if (end > num_vertices)
            end = num_vertices;

        args[i].thread_id = i;
        args[i].clicks = vector<vector<int>>(clicks.begin() + start, clicks.begin() + end);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, count_clicks_divide_parallel_entry, (void *) args);
    }

    delete[] args;
    delete[] threads;

    return 0;
}

void* Graph::count_clicks_divide_parallel_entry(void *args) {
    shared_clicks *shared_clicks = static_cast<struct shared_clicks *>(args);


    pthread_exit(NULL);
    return NULL;
}