#include <graph.h>

int Graph::count_clicks(int k) {
    vector<vector<int>> clicks(num_vertices, vector<int>(1));
    int counter = 0;
    
    // Add all vertices to the clicks array
    for (int i = 0; i < num_vertices; i++) {
        clicks[i].pop_back();
        clicks[i].push_back(vertices[i].id);
    }

    while (clicks.size()) {
        vector<int> click = clicks.back();
        clicks.pop_back();

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
                    neighbor->id > last_vertex
                ) {
                    vector<int> new_click = click;
                    new_click.push_back(neighbor->id);
                    clicks.push_back(new_click);

                    for (int i = 0; i < clicks[clicks.size()].size(); i++) {
                        cout << clicks[clicks.size()][i] << " ";
                    }
                    cout << endl;
                }

                neighbor = neighbor->next;
            }
        }
    }

    return counter;
}

bool Graph::is_on_click(vector<int> click, int vertex) {
    for (int i = 0; i < click.size(); i++) {
        if (click[i] == vertex) {
            return true;
        }
    }

    return false;
}

bool Graph::makes_a_click(vector<int> click, int vertex) {
    Edge* edge = vertices[vertex].edges;

    for (int i = 0; i < click.size(); i++) {
        bool found = false;

        while (edge) {
            if (!found && edge->id == click[i]) {
                found = true;
            }

            edge = edge->next;
        }

        if (!found) {
            return false;
        }
    }

    return true;
}