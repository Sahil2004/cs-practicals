#include <iostream>
#include <climits>

using namespace std;

#define VERTEX 9

void dijkstra(int graph[VERTEX][VERTEX], int src) {
    int dist[VERTEX];
    bool sptSet[VERTEX];
    for (int i = 0; i < VERTEX; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < VERTEX - 1; count++) {
        int minDist = INT_MAX, minIndex;
        for (int v = 0; v < VERTEX; v++) {
            if (!sptSet[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }
        int u = minIndex;
        sptSet[u] = true;
        for (int v = 0; v < VERTEX; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    
    cout << "Vertex \t Distance from Source\n";
    cout << "--------------------------------\n";
    for (int i = 0; i < VERTEX; i++) {
        cout << i << "\t" << dist[i] << endl;
    }
}

int main() {
    int graph[VERTEX][VERTEX] = {
        {0, 3, 0, 0, 0, 0, 0, 5, 0},
        {3, 0, 5, 0, 0, 0, 0, 7, 0},
        {0, 5, 0, 4, 0, 3, 0, 0, 2},
        {0, 0, 4, 0, 6, 8, 0, 0, 0},
        {0, 0, 0, 6, 0, 7, 0, 0, 0},
        {0, 0, 3, 8, 7, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 4},
        {5, 7, 0, 0, 0, 0, 1, 0, 6},
        {0, 0, 2, 0, 0, 0, 4, 6, 0}
    };

    
    dijkstra(graph, 0);
    
    return 0;
}
