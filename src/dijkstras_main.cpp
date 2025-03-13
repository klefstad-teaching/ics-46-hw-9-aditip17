#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("src/medium.txt", G);

    vector<int> prev;
    vector<int> distances = dijkstra_shortest_path(G, 0, prev);

    for (int d=0; d<G.numVertices; ++d) {
        vector<int> path = extract_shortest_path(prev, d);
        print_path(path, distances[d]);
    }

    return 0;

}