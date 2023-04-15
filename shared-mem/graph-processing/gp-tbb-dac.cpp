#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <tbb/tbb.h>

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

// Divide and conquer DFS
void dfs_dc(int u, vector<bool>& visited, Graph& graph, tbb::task_group& group) {
    visited[u] = true;
    vector<int>& neighbors = graph.neighbors(u);
    int n = neighbors.size();

    if (n > 1) {
        // Split neighbors into two halves
        int mid = n / 2;
        vector<int> left(neighbors.begin(), neighbors.begin() + mid);
        vector<int> right(neighbors.begin() + mid, neighbors.end());

        // Call DFS recursively on each half in parallel
        group.run([&] { dfs_dc(left[0], visited, graph, group); });
        for (int i = 1; i < mid; ++i) {
            group.run([&] { dfs(left[i], visited, graph); });
        }
        group.wait();

        group.run([&] { dfs_dc(right[0], visited, graph, group); });
        for (int i = 1; i < n - mid; ++i) {
            group.run([&] { dfs(right[i], visited, graph); });
        }
        group.wait();
    } else if (n == 1) {
        // Call DFS recursively on the only neighbor
        dfs_dc(neighbors[0], visited, graph, group);
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

    // Traverse graph using DFS (parallelized with TBB)
    tbb::task_group group;
    dfs_dc(0, visited, graph, group);

    // Stop timer
    gettimeofday(&end, nullptr);

    // Calculate and print runtime
    double runtime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    cout << "Elapsed time: " << runtime << " seconds" << endl;

    return 0;
}
