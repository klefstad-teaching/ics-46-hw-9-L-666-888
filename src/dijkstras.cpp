#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    vector<int> G_distance(G.numVertices, INF);
    G_distance[source] = 0;
    previous[source] = source;
    vector<bool> visited(G.numVertices, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()){
        auto [v_weight, v] = pq.top();
        pq.pop();
        if (visited[v]){continue;}
        visited[v] = true;

        for (Edge e: G[v]){
            int new_distance = e.weight + v_weight;
            if (new_distance< G_distance[e.dst]){
                G_distance[e.dst] = new_distance;
                pq.push({new_distance,e.dst});
                previous[e.dst] = v;
            }
        }
    }
    return G_distance;
}

void insert_path(vector<int>& v, int new_replacement){
    if (v.empty()) {
        v.push_back(new_replacement);
        return;
    }
    // Move elements to the right
    v.insert(v.begin(), new_replacement);
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    //path.push_back(destination);
    int current_v = destination;
    
    while(previous[current_v] != current_v){
        insert_path(path, current_v);
        current_v = previous[current_v];
    }
    insert_path(path, current_v);
    return path;
}

void print_path(const vector<int>& v, int total){
    
    for (int i: v){
        cout << i << " ";
    }
    cout << "\nTotal cost is " << total << endl; 
}
