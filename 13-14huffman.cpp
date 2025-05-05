#include <bits/stdc++.h>
using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;          // Character stored in the node
    int freq;         // Frequency of the character
    Node* left;       // Pointer to the left child
    Node* right;      // Pointer to the right child

    // Constructor to initialize the node with character and frequency
    Node(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = nullptr; // Initializing left and right children as null
    }
};

// Comparison object to be used in the priority queue (min-heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        if (a->freq == b->freq)
            return a->ch < b->ch; // For lexicographical order in case of a tie in frequency
        return a->freq > b->freq; // Priority is given to the node with smaller frequency
    }
};

class HuffmanCoding {
private:
    Node* root;  // Root of the Huffman tree
    unordered_map<char, string> huffmanCodes; // Map to store the generated Huffman codes for each character
    unordered_map<string, char> reverseCodes; // Reverse mapping of Huffman code to character (for decoding)

    // Function to generate Huffman codes by traversing the Huffman tree
    void generateCodes(Node* node, string code) {
        if (!node) return; // Base case: return if the node is null

        // If the node is a leaf node, store its Huffman code
        if (!node->left && !node->right) {
            huffmanCodes[node->ch] = code;  // Assign code to character
            reverseCodes[code] = node->ch;  // Reverse map code to character
        }

        // Traverse the left and right children of the current node
        generateCodes(node->left, code + "0"); // Add '0' to the code for left child
        generateCodes(node->right, code + "1"); // Add '1' to the code for right child
    }

public:
    // Constructor to initialize the HuffmanCoding object
    HuffmanCoding() {
        root = nullptr; // Initially, the root is null
    }

    // Function to build the Huffman tree based on the frequency map
    void buildTree(const unordered_map<char, int>& freqMap) {
        priority_queue<Node*, vector<Node*>, Compare> pq; // Priority queue (min-heap) for building the tree

        // Create a node for each character and its frequency, then add to the priority queue
        for (auto pair : freqMap) {
            pq.push(new Node(pair.first, pair.second));
        }

        // Build the tree by combining two nodes with the smallest frequencies
        while (pq.size() > 1) {
            // Pop two nodes with the lowest frequencies
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();

            // Create a new internal node with the combined frequency
            Node* merged = new Node('\0', left->freq + right->freq);
            merged->left = left;
            merged->right = right;

            // Push the merged node back to the priority queue
            pq.push(merged);
        }

        // The remaining node is the root of the Huffman tree
        root = pq.top();
        generateCodes(root, ""); // Generate Huffman codes by traversing the tree
    }

    // Function to print the generated Huffman codes
    void printCodes() {
        cout << "Huffman Codes:\n";
        for (auto pair : huffmanCodes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    // Function to encode a given text using the generated Huffman codes
    string encode(const string& text) {
        string encoded = "";
        for (char ch : text) {
            encoded += huffmanCodes[ch]; // Append the Huffman code of each character to the encoded string
        }
        return encoded; // Return the full encoded string
    }

    // Function to decode a given bit sequence using the Huffman tree
    string decode(const string& encoded) {
        string result = "";
        Node* current = root; // Start from the root of the Huffman tree

        // Traverse the encoded string and decode it
        for (char bit : encoded) {
            // Traverse the tree based on the current bit
            if (bit == '0')
                current = current->left; // Move left for '0'
            else
                current = current->right; // Move right for '1'

            // If we reach a leaf node, add the character to the result and reset to the root
            if (!current->left && !current->right) {
                result += current->ch;
                current = root;
            }
        }
        return result; // Return the decoded string
    }
};

int main() {
    HuffmanCoding huff;  // Create an instance of the HuffmanCoding class
    unordered_map<char, int> freqMap;  // Map to store characters and their frequencies
    int n;
    char ch;
    int freq;

    cout << "Enter number of characters: ";
    cin >> n; // Input the number of characters

    cout << "Enter character and its frequency:\n";
    // Input each character and its frequency
    for (int i = 0; i < n; ++i) {
        cin >> ch >> freq;  // Read character and frequency
        freqMap[ch] = freq;  // Store the character and frequency in the frequency map
    }

    // Build the Huffman tree and generate the Huffman codes
    huff.buildTree(freqMap);

    // Print the Huffman codes for each character
    huff.printCodes();

    int choice;
    string input;

    // Menu for encoding and decoding options
    do {
        cout << "\n1. Encode string\n2. Decode bit sequence\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter string to encode: ";
                cin >> input;  // Input the string to encode
                cout << "Encoded: " << huff.encode(input) << endl;  // Display the encoded string
                break;
            case 2:
                cout << "Enter bit sequence to decode: ";
                cin >> input;  // Input the bit sequence to decode
                cout << "Decoded: " << huff.decode(input) << endl;  // Display the decoded string
                break;
            case 3:
                cout << "Exiting...\n";  // Exit the program
                break;
            default:
                cout << "Invalid choice!\n";  // Invalid choice handling
        }
    } while (choice != 3);  // Continue the menu until option 3 (Exit) is selected

    return 0;
}
