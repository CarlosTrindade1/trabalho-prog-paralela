#include <graph.h>

int Graph::count_clicks(count_clicks_args args) {
    int counter = 0;

    vector<vector<int>> *clicks;
    int k = args.k;

    if (args.is_divided) {
        clicks = &args.shared_c[args.thread_id].clicks;
    } else {
        clicks = &args.clicks;
    }

    while (clicks->size()) {
        vector<vector<int>> new_clicks;
        vector<int> click;

        if (args.is_divided) {
            pthread_mutex_lock(&mtx);
            click = clicks->back();
            clicks->pop_back();
            pthread_mutex_unlock(&mtx);
        } else {
            click = clicks->back();
            clicks->pop_back();
        }

        vector<int> already_vertices;

        if (click.size() == k) {
            counter++;
            continue;
        }

        int last_vertex = click.back();

        for (int i = 0; i < click.size(); i++) {
            int vertex = click[i];

            Edge* neighbor = vertices[vertex].edges;

            while (neighbor) {
                if (
                    !is_on_click(click, neighbor->id) &&
                    makes_a_click(click, neighbor->id) &&
                    neighbor->id > last_vertex &&
                    !is_on_click(already_vertices, neighbor->id)
                ) {
                    vector<int> new_click = vector<int>(click);
                    new_click.push_back(neighbor->id);
                    already_vertices.push_back(neighbor->id);
                    new_clicks.push_back(new_click);
                }
                neighbor = neighbor->next;
            }
        }

        if (args.is_divided && new_clicks.size() > 0) {
            pthread_mutex_lock(&mtx);
            for (int i = 0; i < new_clicks.size(); i++) {
                clicks->push_back(new_clicks[i]);
            }
            pthread_mutex_unlock(&mtx);
        } else if (new_clicks.size() > 0) {
            for (int i = 0; i < new_clicks.size(); i++) {
                clicks->push_back(new_clicks[i]);
            }
        }

        if (args.is_divided && clicks->size() == 0) {
            int max = 0;
            int thread_id = 0;

            pthread_mutex_lock(&mtx);
            for (int i = 0; i < args.num_threads; i++) {
                if (args.shared_c[i].clicks.size() > max) {
                    max = args.shared_c[i].clicks.size();
                    thread_id = i;
                }
            }

            if (max > 0) {
                int length = args.r > max ? max - 1 : args.r;

                for (int i = 0; i < length; i++) {
                    clicks->push_back(args.shared_c[thread_id].clicks.back());
                    args.shared_c[thread_id].clicks.pop_back();
                }
            }
            pthread_mutex_unlock(&mtx);
        }
    }

    return counter;
}

// 1st Algorithm
int Graph::count_clicks_serial(int k) {
    vector<vector<int>> clicks(num_vertices, vector<int>(1));
    
    // Add all vertices to the clicksj array
    for (int i = 0; i < num_vertices; i++) {
        clicks[i].pop_back();
        clicks[i].push_back(vertices[i].id);
    }

    count_clicks_args clicks_args = {
        -1,
        0,
        clicks,
        new shared_clicks {
            -1,
            vector<vector<int>>(0)
        },
        false,
        k
    };

    int counter = count_clicks(clicks_args);

    return counter;
}