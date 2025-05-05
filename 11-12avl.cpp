#include <bits/stdc++.h>
using namespace std;

// Node structure representing a single node in the AVL tree
struct Node {
    int key;       // Value stored in the node
    Node* left;    // Pointer to the left child
    Node* right;   // Pointer to the right child
    int height;    // Height of the node for balancing

    // Constructor to initialize a node with a key
    Node(int val) {
        key = val;
        left = right = nullptr;
        height = 1;  // New node starts with a height of 1
    }
};

// AVL tree class with necessary operations
class AVL {
private:
    Node* root;  // Pointer to the root of the tree

    // Get the height of a node
    int getHeight(Node* node) {
        return node ? node->height : 0;  // If node is null, height is 0
    }

    // Get the balance factor of a node (difference in heights of left and right subtrees)
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Right rotation to balance the tree in case of left-heavy imbalance
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights after rotation
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;  // Return new root after rotation
    }

    // Left rotation to balance the tree in case of right-heavy imbalance
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights after rotation
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;  // Return new root after rotation
    }

    // Recursive function to insert a key into the tree and balance it if necessary
    Node* insert(Node* node, int key) {
        // Perform standard BST insert
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;  // Duplicate keys are not allowed

        // Update height of this ancestor node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Check the balance factor of this node
        int balance = getBalance(node);

        // Left-heavy case (LL case)
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right-heavy case (RR case)
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left-Right case (LR case)
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right-Left case (RL case)
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;  // Return the (unchanged) node pointer
    }

    // Inorder traversal (ascending order)
    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->key << " ";
        inOrder(node->right);
    }

    // Reverse inorder traversal (descending order)
    void reverseInOrder(Node* node) {
        if (!node) return;
        reverseInOrder(node->right);
        cout << node->key << " ";
        reverseInOrder(node->left);
    }

    // Find the node with the minimum value (used for deletion)
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)  // Go left until the leftmost node is found
            current = current->left;
        return current;
    }

    // Recursive function to delete a node with a given key
    Node* deleteNode(Node* root, int key) {
        if (!root) return root;  // Base case: tree is empty

        // Perform standard BST delete
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            // Node with only one child or no child
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;  // Copy the contents of the non-empty child
                }
                delete temp;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                Node* temp = minValueNode(root->right);
                root->key = temp->key;  // Copy the inorder successor's key
                root->right = deleteNode(root->right, temp->key);  // Delete the inorder successor
            }
        }

        // If the tree has only one node, return it
        if (!root) return root;

        // Update height of the current node
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Check balance factor and perform rotations to balance the tree
        int balance = getBalance(root);

        // Left-heavy case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left-Right case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right-heavy case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right-Left case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;  // Return the (unchanged) node pointer
    }

public:
    // Constructor to initialize the tree
    AVL() {
        root = nullptr;  // Initially the tree is empty
    }

    // Public insert function
    void insert(int key) {
        root = insert(root, key);
    }

    // Public delete function
    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    // Display tree in ascending order (inorder traversal)
    void displayAscending() {
        cout << "Ascending order: ";
        inOrder(root);
        cout << endl;
    }

    // Display tree in descending order (reverse inorder traversal)
    void displayDescending() {
        cout << "Descending order: ";
        reverseInOrder(root);
        cout << endl;
    }
};

// Main function to interact with the AVL tree
int main() {
    AVL avl;  // Create an AVL tree
    int choice, key;

    int s;
    cout << "Enter the size of the array: ";
    cin >> s;

    cout << "Enter the elements in space separated format: \n";
    for (int i = 0; i < s; i++) {
        int x;
        cin >> x;
        avl.insert(x);  // Insert elements into the AVL tree
    }

    // Menu loop for user interaction
    do {
        cout << "\n--- AVL Tree Operations ---\n";
        cout << "1. Display in ascending order\n";
        cout << "2. Display in descending order\n";
        cout << "3. Delete a key\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                avl.displayAscending();  // Display tree in ascending order
                break;
            case 2:
                avl.displayDescending();  // Display tree in descending order
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                avl.deleteKey(key);  // Delete the specified key from the tree
                cout << "Deleted key: " << key << endl;
                break;
            case 4:
                cout << "Exiting...\n";  // Exit the program
                break;
            default:
                cout << "Invalid choice!\n";  // Handle invalid input
        }

    } while (choice != 4);  // Repeat until the user chooses to exit

    return 0;
}

// 10 20 30 40 50 25 35