#include <graph.h>
#include <mutex>

int Graph::count_clicks(count_clicks_args args) {
    int counter = 0;
    mutex mtx;

    vector<vector<int>> *clicks;
    int k = args.k;

    if (args.is_divided) {
        clicks = &args.shared_c->clicks;
    } else {
        clicks = &args.clicks;
    }

    while (clicks->size()) {
        vector<vector<int>> new_clicks;

        vector<int> click = clicks->back();
        clicks->pop_back();

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

        if (args.is_divided) {
            mtx.lock();
            for (int i = 0; i < new_clicks.size(); i++) {
                args.shared_c->clicks.push_back(new_clicks[i]);
            }
            mtx.unlock();
        } else {
            for (int i = 0; i < new_clicks.size(); i++) {
                clicks->push_back(new_clicks[i]);
            }
        }

        if (clicks->size() == 0) {
            // TODO: Implement a way to take other clicks from the shared_clicks
        }
    }

    return counter;
}

int Graph::count_clicks_serial(int k) {
    vector<vector<int>> clicks(num_vertices, vector<int>(1));
    
    // Add all vertices to the clicksj array
    for (int i = 0; i < num_vertices; i++) {
        clicks[i].pop_back();
        clicks[i].push_back(vertices[i].id);
    }

    count_clicks_args clicks_args = {
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