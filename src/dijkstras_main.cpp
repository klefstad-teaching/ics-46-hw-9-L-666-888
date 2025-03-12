#include "dijkstras.h"

// g++ dijkstras_main.cpp dijkstras.cpp

int main(){
    Graph G;
    file_to_graph("small.txt", G);
    vector<int> previous(G.numVertices);
    vector<int> distance = dijkstra_shortest_path(G, 0, previous);
    vector<int> path = extract_shortest_path(distance, previous, 2);
    int total = distance[2];
    print_path(path, total);
}