#include <iostream>
#include <vector>

using namespace std;

// Global variables for simplicity
int totalNodes;
vector<vector<int>> graph;
vector<bool> visited;
vector<bool> recStack; // Tracks nodes currently in the recursion path

// Depth First Search (DFS) to detect cycles
bool dfsCycleDetection(int node) {
    if (!visited[node]) {
        // Mark the current node as visited and add it to the recursion stack
        visited[node] = true;
        recStack[node] = true;

        // Check all adjacent nodes (where an edge exists)
        for (int i = 0; i < totalNodes; i++) {
            if (graph[node][i] == 1) {
                // If the adjacent node is unvisited, recursively visit it
                if (!visited[i] && dfsCycleDetection(i)) {
                    return true; /* <-- The Messenger */
                } 
                // If the adjacent node is ALREADY in our current path stack, we found a cycle!
                else if (recStack[i]) {
                    return true; // <--- Discovery
                }
            }
        }
    }
    
    // Remove the node from the recursion stack as we backtrack
    recStack[node] = false;
    return false;
}

// Wrapper function to check for deadlock across all disconnected subgraphs
bool isDeadlock() {
    for (int i = 0; i < totalNodes; i++) {
        // Only run DFS if the node hasn't been explored yet
        if (!visited[i]) {
            if (dfsCycleDetection(i)) {
                return true; // Deadlock (cycle) found
            }
        }
    }
    return false;
}

int main() {
    int N, M, E;
    cout << "Enter number of processes and resources: ";
    cin >> N >> M;
    cout << "Enter number of edges: ";
    cin >> E;

    totalNodes = N + M;

    // Initialize the 2D adjacency matrix and tracking arrays dynamically
    graph.assign(totalNodes, vector<int>(totalNodes, 0));
    visited.assign(totalNodes, false);
    recStack.assign(totalNodes, false);

    cout << "Enter edges (u v type):\n";
    cout << "type 'R' for Request (Process -> Resource)\n";
    cout << "type 'A' for Assignment (Resource -> Process)\n";

    for (int i = 0; i < E; i++) {
        int u, v;
        char type;
        cin >> u >> v >> type;

        // Note: Processes are nodes 0 to (N-1). 
        // Resources are offset by N, so they are nodes N to (N+M-1).
        if (type == 'R' || type == 'r') {
            // Process u requests Resource v
            graph[u][N + v] = 1;
        } else if (type == 'A' || type == 'a') {
            // Resource u is assigned to Process v
            graph[N + u][v] = 1;
        }
    }

    if (isDeadlock()) {
        cout << "\nDEADLOCK DETECTED\n";
        cout << "Processes trapped in this path: ";
        
        // Any process still marked 'true' in the recStack was part of the cycle path
        for (int i = 0; i < N; i++) {
            if (recStack[i]) {
                cout << "P" << i << " ";
            }
        }
        cout << "\n";
    } else {
        cout << "\nNO DEADLOCK\n";
    }

    return 0;
}