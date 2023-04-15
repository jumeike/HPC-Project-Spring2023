#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <omp.h>

using namespace std;

struct Edge {
    int src;
    int dst;
};

class Graph {
private:
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list representation

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int src, int dst) {
        adj[src].push_back(dst);
    }

    vector<int>& neighbors(int v) {
        return adj[v];
    }
};

// Simple depth-first search (DFS) traversal
void dfs(int u, vector<bool>& visited, Graph& graph) {
    visited[u] = true;
    for (int v : graph.neighbors(u)) {
        if (!visited[v]) {
            dfs(v, visited, graph);
        }
    }
}

// Generate a random graph with V vertices and E edges
Graph generateRandomGraph(int V, int E) {
    Graph graph(V);
    srand(time(nullptr));
    for (int i = 0; i < E; ++i) {
        int u = rand() % V;
        int v = rand() % V;
        graph.addEdge(u, v);
    }
    return graph;
}

int main() {
    int V = 10000;  // Number of vertices
    int E = 20000;  // Number of edges
    timeval start, end;

    // Generate random graph
    Graph graph = generateRandomGraph(V, E);

    // Initialize visited vector
    vector<bool> visited(V, false);

    // Start timer
    gettimeofday(&start, nullptr);

    #pragma omp parallel for
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(i, visited, graph);
        }
    }

    // Stop timer
    gettimeofday(&end, nullptr);

    // Calculate and print runtime
    double runtime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    cout << "Elapsed time: " << runtime << " seconds" << endl;

    return 0;
}
