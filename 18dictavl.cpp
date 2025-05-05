#include <bits/stdc++.h>
using namespace std;

// Structure to represent a node in the AVL tree
struct Node {
    string keyword;   // Keyword for the dictionary entry
    string meaning;   // Meaning of the keyword
    Node* left;       // Pointer to the left child
    Node* right;      // Pointer to the right child
    int height;       // Height of the node
};

class AVLTree {
private:
    Node* root;  // Root node of the AVL tree

public:
    // Constructor to initialize the AVL Tree with root as nullptr
    AVLTree() {
        root = nullptr;
    }

    // Get the height of a node, returns -1 for nullptr (empty node)
    int getHeight(Node* node) {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    // Update the height of a node based on the heights of its children
    void updateHeight(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + max(leftHeight, rightHeight);  // Height is 1 + max of left and right child heights
    }

    // Perform left rotation on a subtree rooted at node
    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;  // Right child becomes the new root
        node->right = newRoot->left;  // Move the left child of the new root to the right child of node
        newRoot->left = node;         // Make node the left child of the new root
        updateHeight(node);           // Update the height of the original node
        updateHeight(newRoot);        // Update the height of the new root
        return newRoot;               // Return the new root of the subtree
    }

    // Perform right rotation on a subtree rooted at node
    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;   // Left child becomes the new root
        node->left = newRoot->right;  // Move the right child of the new root to the left child of node
        newRoot->right = node;        // Make node the right child of the new root
        updateHeight(node);           // Update the height of the original node
        updateHeight(newRoot);        // Update the height of the new root
        return newRoot;               // Return the new root of the subtree
    }

    // Balance the subtree rooted at node to maintain the AVL property
    Node* balance(Node* node) {
        if (node == nullptr)
            return nullptr;
        updateHeight(node);  // Update height of the node after modification
        int balanceFactor = getHeight(node->left) - getHeight(node->right);  // Balance factor = left height - right height

        // If balance factor is > 1, the left subtree is too tall, perform rotations
        if (balanceFactor > 1 && getHeight(node->left->left) >= getHeight(node->left->right))
            return rotateRight(node);  // Perform right rotation

        // If balance factor is > 1 and the left subtree's right child is taller, perform left-right rotation
        if (balanceFactor > 1 && getHeight(node->left->left) < getHeight(node->left->right)) {
            node->left = rotateLeft(node->left);  // Left rotation on left child
            return rotateRight(node);             // Right rotation on current node
        }

        // If balance factor is < -1, the right subtree is too tall, perform rotations
        if (balanceFactor < -1 && getHeight(node->right->right) >= getHeight(node->right->left))
            return rotateLeft(node);  // Perform left rotation

        // If balance factor is < -1 and the right subtree's left child is taller, perform right-left rotation
        if (balanceFactor < -1 && getHeight(node->right->right) < getHeight(node->right->left)) {
            node->right = rotateRight(node->right);  // Right rotation on right child
            return rotateLeft(node);                  // Left rotation on current node
        }

        return node;  // Return the node if it's already balanced
    }

    // Insert a keyword and its meaning into the AVL tree
    Node* insert(Node* node, const string& keyword, const string& meaning) {
        if (node == nullptr) {
            node = new Node;
            node->keyword = keyword;
            node->meaning = meaning;
            node->left = nullptr;
            node->right = nullptr;
            node->height = 0;
            return node;
        }

        // Insert keyword in the appropriate place based on alphabetical order
        if (keyword < node->keyword)
            node->left = insert(node->left, keyword, meaning);
        else if (keyword > node->keyword)
            node->right = insert(node->right, keyword, meaning);
        else {
            cout << "Keyword already exists!" << endl;  // Duplicate keyword case
            return node;
        }

        return balance(node);  // Balance the node after insertion
    }

    // Remove a keyword from the AVL tree
    Node* remove(Node* node, const string& keyword) {
        if (node == nullptr) {
            cout << "Keyword not found!" << endl;
            return nullptr;
        }

        // Find the node to delete
        if (keyword < node->keyword)
            node->left = remove(node->left, keyword);
        else if (keyword > node->keyword)
            node->right = remove(node->right, keyword);
        else {  // Node with the keyword is found
            if (node->left == nullptr && node->right == nullptr) {
                delete node;  // No children, delete the node
                return nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node->right;  // Only right child, replace node with its right child
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;  // Only left child, replace node with its left child
                delete node;
                return temp;
            }
            else {  // Node has two children
                Node* minRightNode = findMinNode(node->right);  // Find the minimum node in the right subtree
                node->keyword = minRightNode->keyword;           // Copy the keyword of the min node
                node->meaning = minRightNode->meaning;           // Copy the meaning of the min node
                node->right = remove(node->right, minRightNode->keyword);  // Delete the min node
            }
        }

        return balance(node);  // Balance the node after deletion
    }

    // Find the node with the minimum keyword in a subtree
    Node* findMinNode(Node* node) {
        if (node == nullptr)
            return nullptr;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Find the node with the maximum keyword in a subtree
    Node* findMaxNode(Node* node) {
        if (node == nullptr)
            return nullptr;
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    // Update the meaning of an existing keyword
    void updateMeaning(Node* node, const string& keyword, const string& newMeaning) {
        if (node == nullptr) {
            cout << "Keyword not found!" << endl;
            return;
        }
        if (keyword < node->keyword)
            updateMeaning(node->left, keyword, newMeaning);
        else if (keyword > node->keyword)
            updateMeaning(node->right, keyword, newMeaning);
        else {
            node->meaning = newMeaning;  // Update the meaning if keyword is found
            cout << "Meaning updated successfully!" << endl;
        }
    }

    // Display all keywords and their meanings in ascending alphabetical order
    void displayAscending(Node* node) {
        if (node != nullptr) {
            displayAscending(node->left);  // Traverse left subtree
            cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
            displayAscending(node->right);  // Traverse right subtree
        }
    }

    // Display all keywords and their meanings in descending alphabetical order
    void displayDescending(Node* node) {
        if (node != nullptr) {
            displayDescending(node->right);  // Traverse right subtree
            cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
            displayDescending(node->left);  // Traverse left subtree
        }
    }

    // Search for a keyword and count the number of comparisons
    Node* search(Node* node, const string& keyword, int& comparisons) {
        if (node == nullptr)
            return nullptr;
        comparisons++;  // Increment the number of comparisons
        if (keyword < node->keyword)
            return search(node->left, keyword, comparisons);  // Search in left subtree
        else if (keyword > node->keyword)
            return search(node->right, keyword, comparisons);  // Search in right subtree
        else
            return node;  // Keyword found
    }

    // Get the maximum number of comparisons required to search for a keyword
    int getMaxComparisons(const string& keyword) {
        int comparisons = 0;
        search(root, keyword, comparisons);
        return comparisons;
    }

    // Add a new keyword to the dictionary
    void addKeyword() {
        string keyword, meaning;
        cout << "Enter the keyword: ";
        cin >> keyword;
        cin.ignore();
        cout << "Enter the meaning: ";
        getline(cin, meaning);
        root = insert(root, keyword, meaning);  // Insert the new keyword into the AVL tree
        cout << "Keyword added successfully!" << endl;
    }

    // Delete a keyword from the dictionary
    void deleteKeyword() {
        string keyword;
        cout << "Enter the keyword to delete: ";
        cin >> keyword;
        root = remove(root, keyword);  // Remove the keyword from the AVL tree
    }

    // Update the meaning of a keyword
    void updateKeyword() {
        string keyword, newMeaning;
        cout << "Enter the keyword to update: ";
        cin >> keyword;
        cin.ignore();
        cout << "Enter the new meaning: ";
        getline(cin, newMeaning);
        updateMeaning(root, keyword, newMeaning);  // Update the meaning of the keyword
    }

    // Display all keywords and their meanings in ascending order
    void displayAscendingOrder() {
        if (root == nullptr) {
            cout << "No data found!" << endl;
            return;
        }
        cout << "Keywords and meanings in ascending order:" << endl;
        displayAscending(root);  // Display keywords in ascending order
    }

    // Display all keywords and their meanings in descending order
    void displayDescendingOrder() {
        if (root == nullptr) {
            cout << "No data found!" << endl;
            return;
        }
        cout << "Keywords and meanings in descending order:" << endl;
        displayDescending(root);  // Display keywords in descending order
    }

    // Search for a keyword and display its meaning
    void searchKeyword() {
        string keyword;
        cout << "Enter the keyword to search: ";
        cin >> keyword;
        int comparisons = 0;
        Node* result = search(root, keyword, comparisons);  // Search for the keyword
        if (result != nullptr)
            cout << "Meaning: " << result->meaning << endl;
        else
            cout << "Keyword not found!" << endl;
        cout << "Number of comparisons: " << comparisons << endl;  // Display the number of comparisons
    }
};

// Main function to interact with the Dictionary Management System
int main() {
    AVLTree dictionary;  // Create an AVLTree object
    int choice;
    do {
        cout << "\nDictionary Management System" << endl;
        cout << "1. Add Keyword" << endl;
        cout << "2. Delete Keyword" << endl;
        cout << "3. Update Meaning" << endl;
        cout << "4. Display in Ascending Order" << endl;
        cout << "5. Display in Descending Order" << endl;
        cout << "6. Search Keyword" << endl;
        cout << "7. Calculate Maximum Comparisons" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                dictionary.addKeyword();
                break;
            case 2:
                dictionary.deleteKeyword();
                break;
            case 3:
                dictionary.updateKeyword();
                break;
            case 4:
                dictionary.displayAscendingOrder();
                break;
            case 5:
                dictionary.displayDescendingOrder();
                break;
            case 6:
                dictionary.searchKeyword();
                break;
            case 7:{
                string keyword;
                cout << "Enter the keyword: ";
                cin >> keyword;
                cout << "Maximum comparisons required: " << dictionary.getMaxComparisons(keyword) << endl;
                break;
            }
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }
    } while (choice != 8);
    return 0;
}