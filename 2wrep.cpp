#include <bits/stdc++.h>
using namespace std;

const int TABLE_SIZE = 10;

// Structure to represent a student record
struct Student {
    int pnr;           // Unique student ID
    int marks;         // Student marks
    bool isOccupied;   // Whether the slot is currently occupied
    bool isDeleted;    // Whether the record has been logically deleted
    int chain;         // For chaining with replacement (index of next node in chain)

    // Default constructor initializing fields
    Student() : pnr(-1), marks(0), isOccupied(false), isDeleted(false), chain(-1) {}
};

// --------------------- LINEAR PROBING ---------------------
class HashTableLinear {
private:
    Student table[TABLE_SIZE]; // Fixed-size hash table

    // Simple hash function using modulo
    int hash(int key) {
        return key % TABLE_SIZE;
    }

public:
    // Insert a record using linear probing
    void insert(int pnr, int marks) {
        int index = hash(pnr);   // Home index
        int start = index;       // Keep track to avoid infinite loop

        do {
            // Insert if slot is empty or logically deleted
            if (!table[index].isOccupied || table[index].isDeleted) {
                table[index].pnr = pnr;
                table[index].marks = marks;
                table[index].isOccupied = true;
                table[index].isDeleted = false;
                cout << "Inserted (Linear) at index " << index << endl;
                return;
            }
            // Move to next slot (linear probing)
            index = (index + 1) % TABLE_SIZE;
        } while (index != start); // Stop if we return to the start

        cout << "Hash table (Linear) is full!\n";
    }

    // Search a record using linear probing
    void search(int pnr) {
        int index = hash(pnr);
        int start = index;

        do {
            // Found record
            if (table[index].isOccupied && !table[index].isDeleted && table[index].pnr == pnr) {
                cout << "Found (Linear): Marks = " << table[index].marks << " at index " << index << endl;
                return;
            }
            // Go to next slot
            index = (index + 1) % TABLE_SIZE;
        } while (table[index].isOccupied && index != start); // Stop on cycle

        cout << "Student not found (Linear).\n";
    }

    // Delete a record logically using linear probing
    void remove(int pnr) {
        int index = hash(pnr);
        int start = index;

        do {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].pnr == pnr) {
                table[index].isDeleted = true;  // Mark as deleted
                cout << "Deleted (Linear) student with PNR " << pnr << " from index " << index << endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (table[index].isOccupied && index != start);

        cout << "Student not found (Linear).\n";
    }

    // Display the current hash table (linear probing)
    void display() {
        cout << "\nHash Table (Linear Probing):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied && !table[i].isDeleted)
                cout << "[" << i << "] PNR: " << table[i].pnr << ", Marks: " << table[i].marks << endl;
            else
                cout << "[" << i << "] Empty\n";
        }
    }
};

// --------------------- CHAINING WITH REPLACEMENT ---------------------
class HashTableChaining {
private:
    Student table[TABLE_SIZE];

    // Hash function
    int hash(int key) {
        return key % TABLE_SIZE;
    }

    // Find the next empty slot starting after a given index (circularly)
    int findEmptySlot(int start_index) {
        int i = (start_index + 1) % TABLE_SIZE;
        while (i != start_index) {
            if (!table[i].isOccupied || table[i].isDeleted)
                return i;  // Found free spot
            i = (i + 1) % TABLE_SIZE;
        }
        return -1; // Table full
    }

public:
    // Insert record using chaining with replacement
    void insert(int pnr, int marks) {
        int index = hash(pnr); // Home index

        if (!table[index].isOccupied || table[index].isDeleted) {
            // Directly insert at home index
            table[index].pnr = pnr;
            table[index].marks = marks;
            table[index].isOccupied = true;
            table[index].isDeleted = false;
            table[index].chain = -1;
            cout << "Inserted (Chaining With Replacement) at index " << index << endl;
        } else {
            int existing_home = hash(table[index].pnr); // Check if existing is at its correct home

            if (existing_home != index) {
                // Existing is not in its home index -> replacement needed
                int newIndex = findEmptySlot(index);
                if (newIndex == -1) {
                    cout << "Hash table (Chaining) is full!\n";
                    return;
                }

                // Move displaced record to new index
                table[newIndex] = table[index];

                // Fix chain: update previous node pointing to displaced element
                int pred = existing_home;
                while (pred != -1 && table[pred].chain != index)
                    pred = table[pred].chain;
                if (pred != -1)
                    table[pred].chain = newIndex;

                // Insert new record at home index
                table[index].pnr = pnr;
                table[index].marks = marks;
                table[index].isOccupied = true;
                table[index].isDeleted = false;
                table[index].chain = -1;

                cout << "Replaced misplaced record, inserted new at index " << index << ", old moved to " << newIndex << endl;
            } else {
                // Existing is at home index, so add new record in chain
                int newIndex = findEmptySlot(index);
                if (newIndex == -1) {
                    cout << "Hash table (Chaining) is full!\n";
                    return;
                }

                table[newIndex].pnr = pnr;
                table[newIndex].marks = marks;
                table[newIndex].isOccupied = true;
                table[newIndex].isDeleted = false;
                table[newIndex].chain = -1;

                // Find end of current chain and link new node
                int ptr = index;
                while (table[ptr].chain != -1)
                    ptr = table[ptr].chain;
                table[ptr].chain = newIndex;

                cout << "Inserted (Chaining With Replacement) at index " << newIndex << ", chained from " << ptr << endl;
            }
        }
    }

    // Search for a student using chaining
    void search(int pnr) {
        int index = hash(pnr);

        // Follow chain till found or end
        while (index != -1) {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].pnr == pnr) {
                cout << "Found (Chaining): Marks = " << table[index].marks << " at index " << index << endl;
                return;
            }
            index = table[index].chain;
        }

        cout << "Student not found (Chaining).\n";
    }

    // Delete a student using chaining (logical deletion)
    void remove(int pnr) {
        int index = hash(pnr);
        int prev = -1;

        while (index != -1) {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].pnr == pnr) {
                table[index].isDeleted = true;
                // Fix chain of previous node
                if (prev != -1)
                    table[prev].chain = table[index].chain;
                table[index].chain = -1; // Break chain from current node
                cout << "Deleted (Chaining) student with PNR " << pnr << " from index " << index << endl;
                return;
            }
            prev = index;
            index = table[index].chain;
        }

        cout << "Student not found (Chaining).\n";
    }

    // Display chaining hash table with chain links
    void display() {
        cout << "\nHash Table (Chaining With Replacement):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied && !table[i].isDeleted)
                cout << "[" << i << "] PNR: " << table[i].pnr << ", Marks: " << table[i].marks << ", Chain: " << table[i].chain << endl;
            else
                cout << "[" << i << "] Empty\n";
        }
    }
};

// --------------------- MAIN FUNCTION ---------------------
int main() {
    HashTableLinear linearHash;
    HashTableChaining chainHash;

    int choice, method, pnr, marks;

    do {
        cout << "\n--- Student Hash Table Menu ---\n";
        cout << "1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) break;

        cout << "Select Method: 1. Linear Probing  2. Chaining With Replacement\n";
        cin >> method;

        switch (choice) {
            case 1:
                cout << "Enter PNR and Marks: ";
                cin >> pnr >> marks;
                if (method == 1)
                    linearHash.insert(pnr, marks);
                else
                    chainHash.insert(pnr, marks);
                break;

            case 2:
                cout << "Enter PNR to search: ";
                cin >> pnr;
                if (method == 1)
                    linearHash.search(pnr);
                else
                    chainHash.search(pnr);
                break;

            case 3:
                cout << "Enter PNR to delete: ";
                cin >> pnr;
                if (method == 1)
                    linearHash.remove(pnr);
                else
                    chainHash.remove(pnr);
                break;

            case 4:
                if (method == 1)
                    linearHash.display();
                else
                    chainHash.display();
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (true);

    return 0;
}