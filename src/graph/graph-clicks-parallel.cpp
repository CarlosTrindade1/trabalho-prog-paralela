#include <graph.h>

void print_clicks(vector<vector<int>> clicks) {
    for (int i = 0; i < clicks.size(); i++) {
        for (int j = 0; j < clicks[i].size(); j++) {
            cout << clicks[i][j] << " ";
        }
        cout << endl;
    }
}

void* Graph::count_clicks_entry(void *args) {
    thread_args *thread_args = static_cast<struct thread_args *>(args);
    int counter = thread_args->graph->count_clicks(thread_args->clicks, thread_args->k);
    thread_args->counter = counter;
    pthread_exit(NULL);
    return NULL;
}

int Graph::count_clicks_parallel(int k, int num_threads) {
    vector<vector<int>> clicks(num_vertices, vector<int>(1));
    int counter = 0;

    // Add all vertices to the clicks array
    for (int i = 0; i < num_vertices; i++) {
        clicks[i].pop_back();
        clicks[i].push_back(vertices[i].id);
    }
    
    pthread_t *threads = new pthread_t[num_threads];

    int vertices_per_thread = ceil(num_vertices / num_threads);

    thread_args *args = new thread_args[num_threads];

    for (int i = 0; i < num_threads; i++) {
        int start = i * vertices_per_thread;
        int end = (i + 1) * vertices_per_thread;

        if (end > num_vertices)
            end = num_vertices;

        vector<vector<int>> clicks_thread = vector<vector<int>>(clicks.begin() + start, clicks.begin() + end);

        args[i].clicks = clicks_thread;
        args[i].k = k;
        args[i].counter = 0;
        args[i].graph = this;

        pthread_create(&threads[i], NULL, count_clicks_entry, (void *) &args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        counter += args[i].counter;
    }

    delete[] threads;
    delete[] args;

    return counter;
}