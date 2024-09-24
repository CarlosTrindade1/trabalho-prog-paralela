#include <graph.h>

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