#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define V 6 // Number of vertices in the graph

// Function to find the vertex with the minimum key value which is not yet included in the MST
int minKey(vector<int>& key, vector<bool>& mstSet) {
    int min = INT_MAX, min_index;

    // Loop through all vertices to find the one with the minimum key value that is not included in MST
    for (int v = 0; v < V; v++)
        if (!mstSet[v] && key[v] < min)  // Check if vertex 'v' is not yet in MST and its key is smaller than the current min
            min = key[v], min_index = v;  // Update min value and its index

    return min_index; // Return the index of the vertex with the minimum key value
}

// Function to print the Minimum Spanning Tree (MST) edges and total weight
void printMST(vector<int>& parent, vector<vector<int>>& graph) {
    int totalCost = 0;
    cout << "Edge \tWeight\n";

    // Loop through the parent array to print the edges included in the MST
    for (int i = 1; i < V; i++) {
        // Print the edge and its weight, adjusting for 1-based indexing
        cout << parent[i]+1 << " - " << i+1 << "\t" << graph[i][parent[i]] << "\n";
        totalCost += graph[i][parent[i]]; // Add the weight of the edge to the total cost
    }

    // Print the total minimum cost of the MST
    cout << "Total Minimum Cost = " << totalCost << endl;
}

// Function to implement Prim's algorithm for finding the Minimum Spanning Tree (MST)
void primMST(vector<vector<int>>& graph) {
    // 'parent' array stores the parent of each vertex in the MST
    vector<int> parent(V);       

    // 'key' array stores the minimum weight edge connecting a vertex to the MST
    vector<int> key(V, INT_MAX); 

    // 'mstSet' array keeps track of vertices included in the MST (true means included)
    vector<bool> mstSet(V, false); 

    // The starting vertex (0) has a key value of 0, and no parent (-1)
    key[0] = 0;     
    parent[0] = -1; // First node is the root of the MST

    // Iterate over all vertices, making sure we add V-1 edges to the MST
    for (int count = 0; count < V - 1; count++) {
        // Pick the vertex with the smallest key value, which is not yet included in MST
        int u = minKey(key, mstSet);

        // Mark the picked vertex as processed (included in MST)
        mstSet[u] = true;

        // Update the key and parent values of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Check if there is an edge between u and v, and v is not in MST yet
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u; // Set parent of v to u (u is connected to v)
                key[v] = graph[u][v]; // Update key value of vertex v with the weight of the edge
            }
        }
    }

    // Call printMST to print the edges of the MST and the total cost
    printMST(parent, graph);
}

int main() {
    // Adjacency matrix representation of the graph
    vector<vector<int>> graph = {
        {0, 2, 0, 1, 4, 0}, // Vertex 0 connected to 1, 3, 4 with weights 2, 1, 4
        {2, 0, 3, 3, 0, 7}, // Vertex 1 connected to 0, 2, 3, 5 with weights 2, 3, 3, 7
        {0, 3, 0, 5, 0, 8}, // Vertex 2 connected to 1, 3, 5 with weights 3, 5, 8
        {1, 3, 5, 0, 9, 0}, // Vertex 3 connected to 0, 1, 2, 4 with weights 1, 3, 5, 9
        {4, 0, 0, 9, 0, 0}, // Vertex 4 connected to 0, 3 with weights 4, 9
        {0, 7, 8, 0, 0, 0}  // Vertex 5 connected to 1, 2 with weights 7, 8
    };

    // Call the function to find and print the MST using Prim's algorithm
    primMST(graph);

    return 0;
}