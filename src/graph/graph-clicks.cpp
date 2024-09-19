#include <graph.h>

int Graph::count_clicks(vector<vector<int>> clicks, int k) {
    int counter = 0;

    while (clicks.size()) {
        vector<int> click = clicks.back();
        clicks.pop_back();

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
                    vector<int> *new_click = new vector<int>(click);
                    new_click->push_back(neighbor->id);
                    already_vertices.push_back(neighbor->id);
                    clicks.push_back(*new_click);
                }
                neighbor = neighbor->next;
            }
        }
    }

    return counter;
}

int Graph::count_clicks_serial(int k) {
    vector<vector<int>> clicks(num_vertices, vector<int>(1));
    int counter = 0;
    
    // Add all vertices to the clicksj array
    for (int i = 0; i < num_vertices; i++) {
        clicks[i].pop_back();
        clicks[i].push_back(vertices[i].id);
    }

    counter = count_clicks(clicks, k);

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
    for (int i = 0; i < click.size(); i++) {
        if (!is_neighbor(click[i], vertex))
            return false;
    }

    return true;
}

bool Graph::is_neighbor(int vertex_1, int vertex_2) {
    Vertex v1 = vertices[vertex_1];
    Edge *neighbor_1 = v1.edges;

    while (neighbor_1) {
        if (neighbor_1->id == vertex_2)
            return true;
        
        neighbor_1 = neighbor_1->next;
    }

    Vertex v2 = vertices[vertex_2];
    Edge *neighbor_2 = v2.edges;

    while (neighbor_2) {
        if (neighbor_2->id == vertex_1)
            return true;

        neighbor_2 = neighbor_2->next;
    }

    return false;
}