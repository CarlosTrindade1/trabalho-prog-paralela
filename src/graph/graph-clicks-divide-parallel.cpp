#include <graph.h>

void print_clicks(vector<vector<int>> clicks) {
    for (int i = 0; i < clicks.size(); i++) {
        for (int j = 0; j < clicks[i].size(); j++) {
            cout << clicks[i][j] << " ";
        }
        cout << endl;
    }
}

// 3rd Algorithm
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

    shared_clicks *shared_c = new shared_clicks[num_threads];

    for (int i = 0; i < num_threads; i++) {
        int start = i * vertices_per_thread;
        int end = (i + 1) * vertices_per_thread;

        if (end > num_vertices)


            end = num_vertices;

        shared_c[i].thread_id = i;
        shared_c[i].clicks = vector<vector<int>>(clicks.begin() + start, clicks.begin() + end);
    }

    thread_args *args = new thread_args[num_threads];

    for (int i = 0; i < num_threads; i++) {
        args[i].thread_id = i;
        args[i].graph = this;
        args[i].clicks = shared_c[i].clicks;
        args[i].shared_c = shared_c;
        args[i].k = k;
        args[i].counter = counter;
        
        pthread_create(&threads[i], NULL, count_clicks_divide_parallel_entry, (void *) &args[i]);
    }

    delete[] shared_c;
    delete[] threads;

    return 0;
}

void* Graph::count_clicks_divide_parallel_entry(void *args) {
    thread_args *thread_args = static_cast<struct thread_args *>(args);

    count_clicks_args args_count_clicks = {
        thread_args->thread_id,
        thread_args->clicks,
        thread_args->shared_c,
        true,
        thread_args->k
    };

    int counter = thread_args->graph->count_clicks(args_count_clicks);
    thread_args->counter = counter;

    pthread_exit(NULL);
    return NULL;
}