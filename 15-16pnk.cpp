#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Class representing an edge in the graph with source, destination, and weight.
class Edge {
public:
    int src, dest, weight; // source, destination, and weight of the edge
    
    // Constructor to initialize the edge with source, destination, and weight
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Comparison function to sort edges based on their weight (for Kruskal's Algorithm)
bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight; // Return true if the first edge has lesser weight
}

// DSU (Disjoint Set Union) class to manage the connected components using Union-Find technique
class DSU {
public:
    vector<int> parent, rank; // parent array and rank array for Union-Find
    
    // Constructor to initialize DSU with the number of vertices
    DSU(int n) {
        parent.resize(n, -1);  // Initially each vertex is its own parent (disjoint set)
        rank.resize(n, 1);     // Initially, the rank of each vertex is 1
    }
    
    // Find function with path compression: Recursively finds the parent of a vertex
    int find(int v) {
        if (parent[v] == -1) 
            return v;  // If the vertex is its own parent, return it
        return parent[v] = find(parent[v]); // Path compression: Update the parent to the root
    }
    
    // Union function to merge two sets containing v1 and v2
    void unite(int v1, int v2) {
        int p1 = find(v1), p2 = find(v2);  // Find the roots (parents) of both vertices
        if (p1 != p2) {  // If the roots are different, they belong to different sets
            if (rank[p1] > rank[p2]) 
                parent[p2] = p1; // Attach the smaller rank tree under the larger rank tree
            else if (rank[p1] < rank[p2]) 
                parent[p1] = p2; // Attach the smaller rank tree under the larger rank tree
            else { 
                parent[p2] = p1;  // If ranks are equal, arbitrarily choose one as the root
                rank[p1]++;       // Increase the rank of the new root
            }
        }
    }
};

// Function to implement Kruskal's Algorithm to find the MST of the graph
void kruskalMST(vector<Edge>& edges, int V) {
    // Sort the edges based on their weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Create a DSU object to manage the connected components
    DSU dsu(V);  
    vector<Edge> mst;  // Vector to store the edges of the MST
    int totalWeight = 0;  // Variable to store the total weight of the MST

    // Process each edge in the sorted list
    for (auto edge : edges) {
        // If the vertices of the edge belong to different sets, include this edge in MST
        if (dsu.find(edge.src) != dsu.find(edge.dest)) {
            mst.push_back(edge); // Add edge to MST
            totalWeight += edge.weight;  // Add the edge's weight to the total weight
            dsu.unite(edge.src, edge.dest);  // Unite the two sets
        }
    }

    // Print the total weight of the MST and the edges in the MST
    cout << "Kruskal's MST Total Weight: " << totalWeight << endl;
    cout << "Edges in MST:\n";
    for (auto edge : mst)
        cout << edge.src << " - " << edge.dest << " - "<< edge.weight << endl;
}

// Function to implement Prim's Algorithm to find the MST of the graph
void primMST(int V, int E, vector<vector<int>> &edges) {
    // Create an adjacency list to represent the graph
    vector<vector<pair<int, int>>> adj(V);
    for (int i = 0; i < E; i++) {
        int u = edges[i][0];  // Source vertex
        int v = edges[i][1];  // Destination vertex
        int wt = edges[i][2]; // Weight of the edge
        adj[u].push_back({v, wt});  // Add edge to the adjacency list
        adj[v].push_back({u, wt});  // Since the graph is undirected, add reverse edge too
    }

    // Min-heap (priority queue) to pick the edge with the smallest weight
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(V, false);  // Array to mark visited vertices
    vector<int> parent(V, -1);  // Array to store the parent of each vertex in MST
    vector<int> key(V, INT_MAX);  // Array to store the key (weight) of each vertex
    int res = 0;  // Total weight of the MST
    
    pq.push({0, 0});  // Push the first vertex (0) with weight 0
    key[0] = 0;  // The key of the starting vertex is 0

    // Main loop of Prim's algorithm
    while (!pq.empty()) {
        int u = pq.top().second;  // Extract the vertex with minimum weight
        pq.pop();
        
        if (visited[u]) continue;  // Skip the vertex if it is already in MST
        visited[u] = true;  // Mark the vertex as visited
        res += key[u];  // Add the weight of the edge to the MST cost

        // Iterate through all adjacent vertices of u
        for (auto it : adj[u]) {
            int v = it.first;  // Destination vertex
            int weight = it.second;  // Weight of the edge

            // If the destination vertex is not yet in MST and the edge weight is smaller than the current key
            if (!visited[v] && weight < key[v]) {
                key[v] = weight;  // Update the key of vertex v
                pq.push({key[v], v});  // Push the updated vertex into the priority queue
                parent[v] = u;  // Set u as the parent of v
            }
        }
    }

    // Print the total weight of the MST and the edges in the MST
    cout << "Prim's MST Cost: " << res << endl;
    cout << "Edges in MST:\n";
    for (int i = 1; i < V; i++) {  // Starting from vertex 1 (since vertex 0 is the starting point)
        if (parent[i] != -1) {  // If the vertex is connected to another vertex in MST
            cout << parent[i] << " - " << i << "\n";  // Print the edge
        }
    }
}

// Function to display the menu and take user input to choose between Kruskal's and Prim's Algorithm
void menuMST() {
    int V;  // Number of vertices (offices)
    cout << "Enter number of offices (vertices): "; cin >> V;
    int E;  // Number of edges (lines)
    cout << "Enter the number of lines(edges): "; cin >> E;
    
    vector<Edge> edges;  // List to store all the edges
    vector<vector<int>> edgeList;  // List to store edge details in format {source, destination, weight}
    
    // Input edges (source, destination, weight) from the user
    cout << "Format : Source Destination Route \n";
    for (int i = 0; i < E; i++) {
        int a, b, c;  // a = source, b = destination, c = weight
        cout << "edge " << i + 1 << ": "; cin >> a >> b >> c;
        edges.push_back(Edge(a, b, c));  // Add edge to the edges list for Kruskal's Algorithm
        edgeList.push_back({a, b, c});  // Add edge to the edgeList for Prim's Algorithm
    }

    // Main menu for MST algorithms
    while (true) {
        cout << "\nMST Menu:\n1. Kruskal's Algorithm\n2. Prim's Algorithm\n3. Exit\nEnter choice: ";
        int choice;
        cin >> choice;

        // Execute the selected algorithm
        if (choice == 1) {
            kruskalMST(edges, V);  // Run Kruskal's Algorithm
        } else if (choice == 2) {
            primMST(V, edgeList.size(), edgeList);  // Run Prim's Algorithm
        } else if (choice == 3) {
            break;  // Exit the program
        } else {
            cout << "Invalid choice! Try again." << endl;  // Invalid choice
        }
    }
}

int main() {
    menuMST();  // Start the MST menu
    return 0;
}