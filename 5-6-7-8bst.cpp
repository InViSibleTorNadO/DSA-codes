#include <bits/stdc++.h>
using namespace std;

// Node class to represent each node in the binary tree
class node {
public:
    int val;       // Value of the node
    node* right;   // Pointer to the right child
    node* left;    // Pointer to the left child
    
    // Default constructor initializing node with value 0 and no children
    node() {
        left = right = NULL;
        this->val = 0;
    }

    // Constructor to initialize a node with a given value
    node(int val) {
        this->val = val;
        right = NULL;
        left = NULL;
    }
};

// Tree class to represent the Binary Search Tree (BST)
class tree {
    node* rootNode = NULL; // Pointer to the root node of the tree
public:
    tree() {}

    // Function to get the root node of the tree
    node* getRoot() {
        return rootNode;
    }

    // Function to get the in-order successor of a node
    node* getSuccessor(node* curr) {
        curr = curr->right;  // Move to the right child
        // Keep moving to the leftmost node in the right subtree
        while (curr != nullptr && curr->left != nullptr)
            curr = curr->left;
        return curr;
    }

    // Insert a new element into the tree
    void insert(int ele) {
        node* NEW = new node(ele);  // Create a new node with the given value
        if (rootNode == NULL) {
            rootNode = NEW;  // If tree is empty, make the new node the root
        } else {
            node* temp = rootNode;
            node* root = rootNode;
            // Traverse the tree to find the correct position for the new node
            while (temp != NULL) {
                root = temp;
                if (temp->val > ele) {
                    temp = temp->left;
                } else temp = temp->right;
            }
            // Insert the node in the correct position based on comparison
            if (root->val >= ele) {
                root->left = NEW;
            } else root->right = NEW;
        }
    }

    // Delete a node from the tree
    node* delnode(int x, node* root) {
        if (root == nullptr)
            return root;  // Base case: If the node to be deleted is not found

        // Recursively find the node to delete
        if (root->val > x)
            root->left = delnode(x, root->left);
        else if (root->val < x)
            root->right = delnode(x, root->right);
        else {
            // Node to be deleted is found
            if (root->left == nullptr) {
                node* temp = root->right;
                delete root;
                return temp;  // No left child, return right child
            }
            if (root->right == nullptr) {
                node* temp = root->left;
                delete root;
                return temp;  // No right child, return left child
            }
            // Node with two children: Get the in-order successor
            node* succ = getSuccessor(root);
            root->val = succ->val;  // Replace root's value with successor's value
            root->right = delnode(succ->val, root->right);  // Delete successor node
        }
        return root;
    }

    // Recursive Preorder Traversal (Root, Left, Right)
    void Preorder(node* root) {
        if (root == NULL) return;
        cout << root->val << " ";  // Print the root node
        Preorder(root->left);  // Recurse on the left subtree
        Preorder(root->right); // Recurse on the right subtree
    }

    // Recursive Inorder Traversal (Left, Root, Right)
    void Inorder(node* root) {
        if (root == NULL) return;
        Inorder(root->left);  // Recurse on the left subtree
        cout << root->val << " ";  // Print the root node
        Inorder(root->right); // Recurse on the right subtree
    }

    // Recursive Postorder Traversal (Left, Right, Root)
    void Postorder(node* root) {
        if (root == NULL) return;
        Postorder(root->left);  // Recurse on the left subtree
        Postorder(root->right); // Recurse on the right subtree
        cout << root->val << " ";  // Print the root node
    }

    // Non-recursive Preorder Traversal
    void PreorderNON(node* root) {
        stack<node*> st;
        node* curr = root;
        // Traverse until all nodes are visited
        while (curr != NULL || !st.empty()) {
            while (curr != NULL) {
                st.push(curr);  // Push the current node to the stack
                cout << curr->val << " ";  // Print the current node
                curr = curr->left;  // Move to the left child
            }
            curr = st.top();  // Pop the top element from the stack
            st.pop();
            curr = curr->right; // Move to the right child
        }
        cout << '\n';
    }

    // Non-recursive Inorder Traversal
    void InorderNON(node* root) {
        stack<node*> st;
        node* curr = root;
        // Traverse until all nodes are visited
        while (curr != NULL || !st.empty()) {
            while (curr != NULL) {
                st.push(curr);  // Push the current node to the stack
                curr = curr->left;  // Move to the left child
            }
            curr = st.top();  // Pop the top element from the stack
            st.pop();
            cout << curr->val << " ";  // Print the current node
            curr = curr->right; // Move to the right child
        }
        cout << '\n';
    }

    // Non-recursive Postorder Traversal
    void PostorderNON(node* root) {
        stack<node*> st;
        node* curr = root;
        // Traverse until all nodes are visited
        while (curr != NULL || !st.empty()) {
            while (curr != NULL) {
                st.push(curr);  // Push the current node to the stack
                cout << curr->val << " ";  // Print the current node
                curr = curr->right;  // Move to the right child
            }
            curr = st.top();  // Pop the top element from the stack
            st.pop();
            curr = curr->left; // Move to the left child
        }
        cout << '\n';
    }

    // Clone the tree by recursively copying nodes
    node* clone(node* root) {
        if (root == NULL) return NULL;
        node* NEW = new node(root->val);  // Create a new node
        NEW->left = clone(root->left);  // Clone the left subtree
        NEW->right = clone(root->right); // Clone the right subtree
        return NEW;
    }

    // Create a mirror image of the tree
    node* mirror(node* root) {
        if (root == NULL) return NULL;
        node* NEW = new node(root->val);  // Create a new node
        NEW->left = mirror(root->right);  // Mirror the left subtree
        NEW->right = mirror(root->left);  // Mirror the right subtree
        return NEW;
    }

    // Clear the tree by deleting all nodes
    void clearTree(node*& root) {
        if (root == NULL) return;
        clearTree(root->left);  // Clear the left subtree
        clearTree(root->right); // Clear the right subtree
        delete root;  // Delete the current node
        root = NULL;  // Set the root to NULL
    }

    // Calculate the height of the tree
    int height(node* root) {
        if (root == NULL) {
            return 0;  // Return height as 0 if the node is NULL
        }
        // Return the maximum height of left and right subtrees plus 1 for the current node
        return 1 + max(height(root->left), height(root->right));
    }

    // Build a tree from preorder and inorder traversals
    node* buildTree(vector<int>& preorder, vector<int>& inorder, int& preorderIndex, int inorderStart, int inorderEnd, unordered_map<int, int>& inorderMap) {
        if (inorderStart > inorderEnd) {
            return NULL;  // Base case: If there are no nodes to process
        }
        int rootVal = preorder[preorderIndex++];  // Get the root value from preorder
        node* NEW = new node(rootVal);  // Create a new node with the root value
        int rootIndexInInorder = inorderMap[rootVal];  // Find the index of the root value in inorder

        // Recursively build the left and right subtrees
        NEW->left = buildTree(preorder, inorder, preorderIndex, inorderStart, rootIndexInInorder - 1, inorderMap);
        NEW->right = buildTree(preorder, inorder, preorderIndex, rootIndexInInorder + 1, inorderEnd, inorderMap);
        return NEW;
    }
};

// Main function to drive the operations
int main() {
    tree obj;
    do {
        // Display menu of tree operations
        cout << "\nTree Operations\n1. Insert\n2. Delete\n3. Recursive Traversals\n4. Non-recursive Traversals\n5. Clone and Delete Original\n6. Height\n7. Mirror\n8. Generate tree from inorder and preorder\n9. Exit\n";
        int n; cout << "Enter your choice: "; cin >> n;
        node* N = obj.getRoot();
        switch (n) {
        case 1: {
            int ele; cout << "Enter element : "; cin >> ele; obj.insert(ele);
        } break;
        case 2: {
            int ele; cout << "Enter element : "; cin >> ele; obj.delnode(ele, N);
        } break;
        case 3: {
            cout << "1. Inorder\n2. Preorder\n3. Postorder\n";
            int h; cin >> h;
            switch (h) {
            case 1: obj.Inorder(N); break;
            case 2: obj.Preorder(N); break;
            case 3: obj.Postorder(N); break;
            default: break;
            }
        } break;
        case 4: {
            cout << "1. Inorder\n2. Preorder\n3. Postorder\n";
            int h; cin >> h;
            switch (h) {
            case 1: obj.InorderNON(N); break;
            case 2: obj.PreorderNON(N); break;
            case 3: obj.PostorderNON(N); break;
            default: break;
            }
        } break;
        case 5: {
            node* cloneRoot = obj.clone(N);
            cout << "Inorder of Clone Tree: "; obj.Inorder(cloneRoot);
            obj.clearTree(N);
            cout << "\nOriginal tree deleted.\n";
            cout << "Inorder of Original Tree (should be empty): "; obj.Inorder(N);
        } break;
        case 6: {
            cout << obj.height(N)-1;
        } break;
        case 7: {
            node* mirrorRoot = obj.mirror(N);
            cout << "Inorder (Original): "; obj.Inorder(N);
            cout << "\nInorder (Mirror)  : "; obj.Inorder(mirrorRoot);
        } break;
        case 8: {
            vector<int> preorder, inorder;
            int n; cout << "Enter the sequence size:"; cin >> n;
            cout << "Enter the preorder sequence:";
            for (int i = 0; i < n; i++) {
                int y; cin >> y; preorder.push_back(y);
            }
            cout << "Enter the inorder sequence:";
            for (int i = 0; i < n; i++) {
                int y; cin >> y; inorder.push_back(y);
            }
            unordered_map<int, int> inorderMap;
            for (int i = 0; i < inorder.size(); ++i) {
                inorderMap[inorder[i]] = i;
            }
            int preorderIndex = 0;
            node* root = obj.buildTree(preorder, inorder, preorderIndex, 0, inorder.size() - 1, inorderMap);
            cout << "Postorder traversal of the constructed tree: "; obj.Postorder(root);
        } break;
        case 9:
            return 0;
        default:
            break;
        }
        cout << "\n";
    } while (true);
}