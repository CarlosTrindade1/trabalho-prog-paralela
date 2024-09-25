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
            int edge_id = atoi(strtok(NULL, " "));
            
            new_ids[vertex_id] = 1;
            new_ids[edge_id] = 1;
        }

        for (const auto pair : new_ids) {
            new_ids[pair.first] = counter;
            counter++;
        }

        file.close();

        return new_ids;
    } else {
        cout << "Não foi possível abrir o arquivo" << endl;
        return map<int, int>();
    }
}

void Graph::read_graph(char* file_name_graph, map<int, int> new_ids) {
    ifstream file(file_name_graph);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            int vertex_id = atoi(strtok((char *)line.c_str(), " "));
            int vertex_id_new = new_ids[vertex_id];

            int edge_id = atoi(strtok(NULL, " "));
            int edge_id_new = new_ids[edge_id];

            // Add a edge to the vertex
            if (vertices[vertex_id_new].edges != NULL) {
                Edge *edge = vertices[vertex_id_new].edges;
                while (edge->next != NULL) {
                    edge = edge->next;
                }
                edge->next = new Edge{edge_id_new, NULL};
            } else {
                vertices[vertex_id_new].edges = new Edge{edge_id_new, NULL};
            }

            // Add a vertex to the edge's vertex
            if (vertices[edge_id_new].edges != NULL) {
                Edge *edge = vertices[edge_id_new].edges;
                while (edge->next != NULL) {
                    edge = edge->next;
                }
                edge->next = new Edge{vertex_id_new, NULL};
            } else {
                vertices[edge_id_new].edges = new Edge{vertex_id_new, NULL};
            }
        }

        file.close();
    } else {
        cout << "Não foi possível abrir o arquivo" << endl;
    }
}

Graph::Graph(char *file_name) {
    pthread_mutex_init(&mtx, NULL);
    map<int, int> new_ids = rename_vertices(file_name);

    if (new_ids.empty()) {
        cout << "Não foi possível criar o grafo" << endl;
        return;
    }

    vertices = new Vertex[new_ids.size()];
    num_vertices = new_ids.size();

    for (const auto pair : new_ids) {
        vertices[pair.second].id = pair.second;
        vertices[pair.second].edges = NULL;
    }
    
    read_graph(file_name, new_ids);
}

Graph::~Graph() {
    for (int i = 0; i < num_vertices; i++) {
        Edge *edge = vertices[i].edges;
        while (edge != NULL) {
            Edge *next = edge->next;
            delete edge;
            edge = next;
        }
    }

    delete[] vertices;
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