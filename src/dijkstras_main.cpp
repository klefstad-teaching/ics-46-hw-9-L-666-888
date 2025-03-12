#include "dijkstras.h"

// g++ dijkstras_main.cpp dijkstras.cpp

int main(){
    Graph G;
    file_to_graph("small.txt", G);
    vector<int> previous(G.numVertices);
    vector<int> distance = dijkstra_shortest_path(G, 0, previous);
    // for (int v: previous){
    //     cout << v << " ";
    // }
    vector<int> path = extract_shortest_path(distance, previous, 2);
    // for (int v: path){
    //     cout << v << " ";
    // }
    // int total = 0;
    // for (int v: path){
    //     total+= distance[v];
    // }
    int total = distance[2];
    print_path(path, total);
}