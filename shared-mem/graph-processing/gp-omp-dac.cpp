#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>

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

void dfs(int u, vector<bool>& visited, Graph& graph) {
    visited[u] = true;
    for (int v : graph.neighbors(u)) {
        if (!visited[v]) {
            dfs(v, visited, graph);
        }
    }
}

void dfs_parallel(int u, vector<bool>& visited, Graph& graph, int threshold) {
    int num_neighbors = graph.neighbors(u).size();
    if (num_neighbors <= threshold) {
        dfs(u, visited, graph);
    } else {
        // Divide the neighbors into two halves
        int mid = num_neighbors / 2;
        vector<int> left_half(graph.neighbors(u).begin(), graph.neighbors(u).begin() + mid);
        vector<int> right_half(graph.neighbors(u).begin() + mid, graph.neighbors(u).end());

        // Traverse the left half in a new task
        #pragma omp task
        {
            for (int i = mid-1; i >= 0; --i) {
                int v = left_half[i];
                if (!visited[v]) {
                    dfs_parallel(v, visited, graph, threshold);
                }
            }
        }

        // Traverse the right half in a new task
        #pragma omp task
        {
            for (int i = 0; i < right_half.size(); ++i) {
                int v = right_half[i];
                if (!visited[v]) {
                    dfs_parallel(v, visited, graph, threshold);
                }
            }
        }

        // Wait for the tasks to complete
        #pragma omp taskwait
    }
}

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
    int threshold = 100;  // Threshold for sequential processing

    // Generate random graph
    Graph graph = generateRandomGraph(V, E);

    // Initialize visited vector
    vector<bool> visited(V, false);

    // Start timer
    timeval start, end;
    gettimeofday(&start, nullptr);

    // Traverse graph using DFS (parallelized with OpenMP)
    #pragma omp parallel
    #pragma omp single
    {
        dfs_parallel(0, visited, graph, threshold);
    }

    // Stop timer
    gettimeofday(&end, nullptr);

    // Calculate and print runtime
    double runtime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    cout << "Elapsed time: " << runtime << " seconds" << endl;

    return 0;
}
