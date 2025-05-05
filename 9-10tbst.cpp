#include <bits/stdc++.h>
using namespace std;

// Struct to represent a node in the Threaded Binary Search Tree
struct TreeNode {
    int value;               // Value of the node
    TreeNode *leftChild, *rightChild;  // Pointers to left and right children
    bool isLeftThreaded, isRightThreaded;  // Flags to determine if the node's children are threaded

    // Constructor to initialize a new node
    TreeNode(int val) {
        value = val;
        leftChild = rightChild = nullptr;  // Initially no children
        isLeftThreaded = isRightThreaded = true;  // Threads are set to true initially
    }
};

// Class representing the Threaded Binary Search Tree (TBST)
class ThreadedBinarySearchTree {
private:
    TreeNode *rootNode;  // Pointer to the root node of the tree

public:
    // Constructor to initialize an empty tree
    ThreadedBinarySearchTree() {
        rootNode = nullptr;  // Initially, the tree is empty
    }

    // Function to add a new node to the TBST
    void addToTBST(int key) {
        rootNode = insertNode(rootNode, key);  // Insert the node and update the root
    }

    // Function for inorder traversal of the threaded BST
    void inorderTraversal() {
        TreeNode *current = leftMost(rootNode);  // Start with the leftmost node (smallest)
        while (current) {
            cout << current->value << " ";  // Print the current node's value
            if (current->isRightThreaded)  // If the right child is a thread, move to the threaded right child
                current = current->rightChild;
            else  // Otherwise, go to the leftmost node of the right subtree
                current = leftMost(current->rightChild);
        }
        cout << endl;
    }

    // Function for preorder traversal of the threaded BST
    void preorderTraversal() {
        TreeNode *current = rootNode;  // Start with the root node
        while (current) {
            cout << current->value << " ";  // Print the current node's value

            if (!current->isLeftThreaded)  // If the left child is not threaded, move to the left child
                current = current->leftChild;
            else if (!current->isRightThreaded)  // If the right child is not threaded, move to the right child
                current = current->rightChild;
            else {  // If both children are threaded, go to the right child by following threads
                while (current && current->isRightThreaded)
                    current = current->rightChild;
                if (current)
                    current = current->rightChild;
            }
        }
        cout << endl;
    }

private:
    // Function to insert a new node into the TBST
    TreeNode* insertNode(TreeNode* node, int key) {
        if (!node)  // If the tree is empty, create a new node
            return new TreeNode(key);
        
        // Traverse the tree to find the appropriate insertion point (BST behavior)
        TreeNode* parent = nullptr;
        TreeNode* current = node;

        while (current) {
            parent = current;
            if (key < current->value) {  // If the key is smaller, move left
                if (!current->isLeftThreaded)
                    current = current->leftChild;
                else
                    break;
            } else {  // If the key is larger, move right
                if (!current->isRightThreaded)
                    current = current->rightChild;
                else
                    break;
            }
        }

        TreeNode* newNode = new TreeNode(key);  // Create a new node with the given key
        if (key < parent->value) {  // Insert the new node to the left of the parent
            newNode->leftChild = parent->leftChild;
            newNode->rightChild = parent;
            parent->leftChild = newNode;
            parent->isLeftThreaded = false;  // Mark left child as not threaded
        } else {  // Insert the new node to the right of the parent
            newNode->rightChild = parent->rightChild;
            newNode->leftChild = parent;
            parent->rightChild = newNode;
            parent->isRightThreaded = false;  // Mark right child as not threaded
        }

        return node;  // Return the updated root
    }

    // Function to find the leftmost (smallest) node in the tree/subtree
    TreeNode* leftMost(TreeNode* node) {
        while (node && !node->isLeftThreaded)  // Keep going left until a thread is encountered
            node = node->leftChild;
        return node;  // Return the leftmost node
    }
};

int main() {
    ThreadedBinarySearchTree tree;  // Create an empty TBST

    cout << "Enter number of elements in TBST: ";
    int n;
    cin >> n;
    cout << "Enter elements: ";
    for (int i = 0, val; i < n; ++i) {
        cin >> val;  // Read input elements
        tree.addToTBST(val);  // Add each element to the TBST
    }

    int option, data;
    do {
        // Menu options for interacting with the tree
        cout << "\nOptions:\n";
        cout << "1. Insert Node into Threaded BST\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> data;
                tree.addToTBST(data);  // Insert a new node into the tree
                break;
            case 2:
                cout << "Inorder Traversal: ";
                tree.inorderTraversal();  // Perform inorder traversal
                break;
            case 3:
                cout << "Preorder Traversal: ";
                tree.preorderTraversal();  // Perform preorder traversal
                break;
            case 4:
                cout << "Exiting...\n";  // Exit the program
                break;
            default:
                cout << "Invalid option! Try again.\n";  // Handle invalid inputs
        }
    } while (option != 4);  // Repeat until the user chooses to exit

    return 0;
}