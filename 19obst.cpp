#include<bits/stdc++.h>
using namespace std;

const int N = 1e2;  // Maximum number of keys (100)
int w[N][N];  // Weight matrix for storing the sum of probabilities between keys
int r[N][N];  // Root matrix for storing the root of the subtree
int c[N][N];  // Cost matrix for storing the minimum cost of searching in the subtree
int p[N];     // Array to store the probability of successful search for each key
int q[N];     // Array to store the probability of unsuccessful search between the keys and at the boundaries

int main() {
    // Input number of elements (keys)
    cout << "ENTER NO. OF ELEMENTS: "; 
    int n; 
    cin >> n;
    
    // Input success probabilities for each key
    cout << "ENTER SUCCESS PROB: \n"; 
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    
    // Input failure probabilities between keys and at the boundaries
    cout << "ENTER UNSUCCESS: \n";
    for(int i = 0; i <= n; i++) {
        cin >> q[i];
    }

    // Base case: for a single key, the weight and cost are initialized
    for(int i = 0; i <= n; i++) {
        w[i][i] = q[i];        // Weight is just the failure probability at the boundary
        r[i][i] = 0;           // No root for a single key
        c[i][i] = 0;           // No cost for a single key
    }

    // Initialize the base case for a subtree of size 2 (i.e., two keys)
    for(int i = 0; i < n; i++) {
        w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];  // Weight for a 2-key subtree
        r[i][i + 1] = i + 1;                        // The root for a 2-key subtree is the second key
        c[i][i + 1] = q[i] + q[i + 1] + p[i + 1];  // The cost is the sum of all probabilities for this small subtree
    }

    // Dynamic programming loop for calculating the cost for larger subtrees
    for(int d = 2; d <= n; d++) {  // d is the size of the subtree
        for(int j = d; j <= n; j++) {  // j is the right endpoint of the subtree
            int i = j - d;  // i is the left endpoint of the subtree
            w[i][j] = w[i][j - 1] + p[j] + q[j];  // Update the weight for this larger subtree

            long long mn = INT_MAX;  // Variable to store the minimum cost
            int mnk;  // The root of the subtree with the minimum cost

            // Try each possible root 'k' for the subtree and calculate the total cost
            for(int k = i + 1; k <= j; k++) {
                int x = c[i][k - 1] + c[k][j];  // The cost of left and right subtrees
                if(x < mn) {  // If we found a smaller cost, update it
                    mn = x;
                    mnk = k;  // Update the root of the optimal subtree
                }
            }

            c[i][j] = w[i][j] + mn;  // Total cost is the weight of the subtree plus the minimum cost
            r[i][j] = mnk;            // Store the optimal root for this subtree
        }
    }

    // Output the final results
    cout << endl;
    cout << "WEIGHT: " << w[0][n] << endl;    // The total weight for the whole tree
    cout << "COST: " << c[0][n] << endl;      // The minimum cost of searching in the whole tree
    cout << "ROOT: " << r[0][n] << endl;      // The root of the optimal binary search tree

    // Use a queue to print the structure of the optimal binary search tree
    int que[100]; 
    int front = 0, rear = -1;

    // Push the initial state (start, end, root)
    que[++rear] = 0;
    que[++rear] = n;
    que[++rear] = r[0][n];

    // Print the structure of the tree using BFS-like approach
    while(front <= rear) {
        int i = que[front++];  // Start index of the subtree
        int j = que[front++];  // End index of the subtree
        int k = que[front++];  // Root of the subtree

        // If there is a left child, print it
        if(r[i][k - 1] != 0) {
            cout << "LEFT OF " << k << ": " << r[i][k - 1] << endl;
            que[++rear] = i;
            que[++rear] = k - 1;
            que[++rear] = r[i][k - 1];
        }

        // If there is a right child, print it
        if(r[k][j] != 0) {
            cout << "RIGHT OF " << k << ": " << r[k][j] << endl;
            que[++rear] = k;
            que[++rear] = j;
            que[++rear] = r[k][j];
        }
    }

    return 0;
}