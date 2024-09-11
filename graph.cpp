#include <graph.h>

using namespace std;

map<int, int> Graph::rename_vertices(char* filename_graph) {
    ifstream file(filename_graph);
    map<int, int> new_ids;

    if (file.is_open()) {
        string line;
        int counter = 0;

        while (getline(file, line)) {
            int vertex_id = atoi(strtok((char *)line.c_str(), " "));
            
            new_ids[vertex_id] = 1;
        }

        for (const auto pair : new_ids) {
            new_ids[pair.first] = counter;
            counter++;
        }

        file.close();

        return new_ids;
    } else {
        cout << "Não foi possível abrir o arquivo" << endl;
    }
}

void Graph::read_graph(char* file_name_graph) {
    ifstream file(file_name_graph);
    if (file.is_open()) {
        string line;
        int counter = 0;
        while (getline(file, line)) {
            if (counter == 0) {
                num_vertices = atoi(line.c_str());
                if (num_vertices <= 0) {
                    cout << "Invalid number of vertices" << endl;
                    return;
                }
                vertices = (Vertex *)malloc(num_vertices * sizeof(Vertex));
            } else if (counter > 0 && counter <= num_vertices) {
                vertices[counter - 1].id = atoi(line.c_str());
                vertices[counter - 1].edges = NULL;
            } else {
                int vertex_id = atoi(strtok((char *)line.c_str(), " "));
                
                for (int i = 0; i < num_vertices; i++) {
                    if (vertices[i].id == vertex_id) {
                        if (vertices[i].edges != NULL) {
                            Edge *edge = vertices[i].edges;

                            while (edge->next != NULL)
                                edge = edge->next;
                            
                            Edge *new_edge = (Edge *)malloc(sizeof(Edge));
                            new_edge->id = atoi(strtok(NULL, " "));
                            new_edge->next = NULL;
                            edge->next = new_edge;
                            continue;
                        }

                        Edge *edge = (Edge *)malloc(sizeof(Edge));
                        edge->id = atoi(strtok(NULL, " "));
                        edge->next = NULL;
                        vertices[i].edges = edge;
                    }
                }
            }
            counter++;
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

Graph::Graph(char *file_name) {
    rename_vertices(file_name);
    // read_graph(file_name);
    cout << "Graph created" << endl;
}

void Graph::print() {
    for (int i = 0; i < num_vertices; i++) {
        cout << vertices[i].id << " -> ";
        Edge *edge = vertices[i].edges;
        while (edge != NULL) {
            cout << edge->id << " ";
            edge = edge->next;
        }
        cout << endl;
    }
}