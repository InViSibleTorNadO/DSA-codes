#include <bits/stdc++.h>
using namespace std;

class Graph {
    int V;  // Number of vertices (cities)
    vector<vector<pair<int, int>>> adj; // Adjacency list for storing graph (city routes)

public:
    // Constructor to initialize the graph with 'V' vertices
    Graph(int V) : V(V) {
        adj.resize(V);  // Resize adjacency list to V vertices
    }

    // Add an edge from u to v with weight w
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w}); // Add an edge from u to v with weight w
    }

    // Dijkstra's algorithm to find the shortest paths from the source vertex
    vector<int> dijkstra(int src, vector<vector<int>>& parent) {
        vector<int> dist(V, INT_MAX);  // Initialize distance array with infinity
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[src] = 0;  // Distance to the source is 0
        pq.push({0, src});  // Push the source node to the priority queue
        parent[src].clear();  // Clear parent for the source node

        while (!pq.empty()) {
            int u = pq.top().second;  // Get the node with the smallest distance
            int d = pq.top().first;   // Get its distance
            pq.pop();

            if (d > dist[u]) continue;  // If the current distance is greater, skip it

            // Loop through all neighbors of u
            for (auto p : adj[u]) {
                int v = p.first;      // Neighbor vertex
                int weight = p.second; // Weight of the edge

                // If a shorter path to v is found, update distance and parent
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;  // Update distance to v
                    pq.push({dist[v], v});      // Push v to the priority queue
                    parent[v].clear();          // Clear previous parents
                    parent[v].push_back(u);     // Set u as the parent of v
                } 
                // If another shortest path is found to v (same distance), add u as an additional parent
                else if (dist[u] + weight == dist[v]) {
                    parent[v].push_back(u);  // Store u as an additional parent of v
                }
            }
        }
        return dist;  // Return the distance array
    }

    // Recursive function to find all paths from source to destination using parent information
    void findPaths(int src, int dest, vector<vector<int>>& parent, vector<int>& path, vector<vector<int>>& result) {
        if (dest == src) {  // Base case: when destination is the source, we've found a path
            result.push_back(path);  // Add current path to result
            return;
        }

        // Loop through all parents of the destination vertex
        for (int p : parent[dest]) {
            path.push_back(p);          // Add the parent to the current path
            findPaths(src, p, parent, path, result);  // Recursively find paths from the parent
            path.pop_back();            // Backtrack: remove the parent from the current path
        }
    }

    // Function to print the minimum paths between source and destination
    void printMinPaths(int start, int end) {
        vector<vector<int>> parent(V);  // To store parent vertices for path reconstruction
        vector<int> dist = dijkstra(start, parent);  // Run Dijkstra to find shortest distances

        if (dist[end] == INT_MAX) {  // If no path exists to the destination
            cout << "No path exists from " << start << " to " << end << endl;
            return;
        } else {
            cout << "Minimum Distance: " << dist[end] << endl;  // Print the minimum distance

            vector<int> path = {end};  // Start path with the destination
            vector<vector<int>> result;  // To store all the paths

            findPaths(start, end, parent, path, result);  // Find all paths from start to end

            cout << "Paths with Minimum Distance: " << endl;
            // Print all paths
            for (auto& p : result) {
                reverse(p.begin(), p.end());  // Reverse the path to show from start to end
                for (int city : p) cout << city << " ";  // Print the cities in the path
                cout << endl;
            }
        }
    }
};

// Function to handle user input and the route-finding menu
void menuRoutes() {
    int V;
    cout << "Enter the number of cities(vertices): "; cin >> V;  // Input number of cities
    Graph g(V);  // Create a graph with V vertices
    int E; 
    cout << "Enter the number of paths(edges): "; cin >> E;  // Input number of routes (edges)
    cout << "Format : Source Destination Route (with weights)\n";
    
    // Input all edges
    for(int i = 0; i < E; i++) {
        int a, b, c;
        cout << "route " << i + 1 << ": "; cin >> a >> b >> c;  // Input route with source, destination, and weight
        g.addEdge(a, b, c);  // Add edge to the graph
    }

    // Menu for route finding
    while (true) {
        cout << "\nRoute Finder Menu:";
        cout << "\n1. Find Shortest Routes";
        cout << "\n2. Exit\nEnter choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int S, F;
            cout << "Enter Source City (0 indexed): "; cin >> S;  // Input source city (0-indexed)
            cout << "Enter Destination City (0 indexed): "; cin >> F;  // Input destination city (0-indexed)
            g.printMinPaths(S, F);  // Find and print the minimum paths
        } else if (choice == 2) {
            break;  // Exit the menu
        } else {
            cout << "Invalid choice! Try again." << endl;
        }
    }
}

// Main function to start the program
int main() {
    menuRoutes();  // Start the route-finding menu
    return 0;
}