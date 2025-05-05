#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight; // Source vertex, destination vertex, and weight of the edge
};

// Comparison function to sort edges by their weights
bool compare(Edge a, Edge b) {
    return a.weight < b.weight; // Sort in ascending order of edge weight
}

// Find function with path compression to efficiently find the parent of a vertex
int findParent(int v, vector<int>& parent) {
    if (parent[v] != v) {
        parent[v] = findParent(parent[v], parent); // Path compression to flatten the tree structure
    }
    return parent[v]; // Return the parent of vertex v
}

// Union function to connect two subsets (perform union by rank)
void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
    int uRoot = findParent(u, parent); // Find the root of the first vertex
    int vRoot = findParent(v, parent); // Find the root of the second vertex

    // Union by rank: attach the smaller tree under the larger tree
    if (rank[uRoot] < rank[vRoot])
        parent[uRoot] = vRoot; // If the rank of u's root is smaller, make v's root the parent of u's root
    else if (rank[uRoot] > rank[vRoot])
        parent[vRoot] = uRoot; // If the rank of v's root is smaller, make u's root the parent of v's root
    else {
        parent[vRoot] = uRoot; // If both roots have the same rank, make one root the parent of the other
        rank[uRoot]++; // Increase the rank of the new root
    }
}

// Function to find the Minimum Spanning Tree using Kruskal's Algorithm
void kruskalMST(vector<Edge>& edges, int V) {
    // Sort the edges by weight in ascending order
    sort(edges.begin(), edges.end(), compare);

    // Initialize parent and rank vectors for union-find
    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; ++i)
        parent[i] = i; // Initially, each vertex is its own parent

    // Vector to store the edges that will be included in the MST
    vector<Edge> result;

    int totalCost = 0; // Variable to store the total weight of the MST

    // Iterate through all the edges, and process them one by one
    for (const Edge& e : edges) {
        int u = findParent(e.src, parent); // Find the root of the source vertex
        int v = findParent(e.dest, parent); // Find the root of the destination vertex

        // If the roots are different, there is no cycle, and we can add this edge to the MST
        if (u != v) {
            result.push_back(e); // Add the edge to the MST
            totalCost += e.weight; // Add the weight of the edge to the total cost
            unionSet(u, v, parent, rank); // Union the two subsets
        }

        // If we've added V-1 edges, we don't need any more
        if (result.size() == V - 1)
            break;
    }

    // Print the edges in the MST and their weights
    cout << "Edge \tWeight\n";
    for (const Edge& e : result)
        cout << e.src + 1 << " - " << e.dest + 1 << "\t" << e.weight << endl;

    // Print the total weight of the MST
    cout << "Total Minimum Cost = " << totalCost << endl;
}

int main() {
    int V = 6; // Number of vertices in the graph

    // Define all the edges of the graph with source, destination, and weight
    vector<Edge> edges = {
        {0, 1, 2}, {0, 3, 1}, {0, 4, 4}, // Edges connected to vertex 0
        {1, 2, 3}, {1, 3, 3}, {1, 5, 7}, // Edges connected to vertex 1
        {2, 3, 5}, {2, 5, 8}, {3, 4, 9}  // Edges connected to vertex 2
    };

    // Call Kruskal's algorithm to find and print the MST
    kruskalMST(edges, V);

    return 0;
}