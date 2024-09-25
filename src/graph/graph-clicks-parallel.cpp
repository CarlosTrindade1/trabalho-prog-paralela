#include <graph.h>

void* Graph::count_clicks_parallel_entry(void *args) {
    thread_args *thread_args = static_cast<struct thread_args *>(args);

    count_clicks_args args_count_clicks = {
        thread_args->thread_id,
        thread_args->num_threads,
        thread_args->clicks,
        new shared_clicks {
            -1,
            vector<vector<int>>(0)
        },
        false,
        thread_args->k
    };

    int counter = thread_args->graph->count_clicks(args_count_clicks);
    thread_args->counter = counter;

    delete args_count_clicks.shared_c;

    pthread_exit(NULL);
    return NULL;
}

// 2nd Algorithm
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

        args[i].thread_id = i;
        args[i].clicks = clicks_thread;
        args[i].k = k;
        args[i].counter = 0;
        args[i].graph = this;
        args[i].num_threads = num_threads;

        pthread_create(&threads[i], NULL, count_clicks_parallel_entry, (void *) &args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        counter += args[i].counter;
    }

    delete[] threads;
    delete[] args;

    return counter;
}