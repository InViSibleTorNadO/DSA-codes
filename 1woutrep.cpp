#include <bits/stdc++.h>
using namespace std;

const int TABLE_SIZE = 10;

// Structure to represent a student record
struct Student {
    int pnr;
    int marks;
    bool isOccupied;  // true if the slot is filled
    bool isDeleted;   // true if deleted (for linear probing)
    int chain;        // used in chaining without replacement

    Student() : pnr(-1), marks(0), isOccupied(false), isDeleted(false), chain(-1) {}
};

// ----------------- Linear Probing -----------------
class HashTableLinear {
private:
    Student table[TABLE_SIZE];

    // Hash function
    int hash(int key) {
        return key % TABLE_SIZE;
    }

public:
    // Insert using linear probing
    void insert(int pnr, int marks) {
        int index = hash(pnr);
        int start = index;

        // Loop until an empty or deleted slot is found
        do {
            if (!table[index].isOccupied || table[index].isDeleted) {
                table[index].pnr = pnr;
                table[index].marks = marks;
                table[index].isOccupied = true;
                table[index].isDeleted = false;
                cout << "Inserted (Linear) at index " << index << endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (index != start);  // Stop if full circle is done

        cout << "Hash table (Linear) is full!\n";
    }

    // Search using linear probing
    void search(int pnr) {
        int index = hash(pnr);
        int start = index;

        do {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].pnr == pnr) {
                cout << "Found (Linear): Marks = " << table[index].marks << " at index " << index << endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (table[index].isOccupied && index != start);

        cout << "Student not found (Linear).\n";
    }

    // Delete using linear probing (lazy deletion)
    void remove(int pnr) {
        int index = hash(pnr);
        int start = index;

        do {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].pnr == pnr) {
                table[index].isDeleted = true;  // mark as deleted
                cout << "Deleted (Linear) student with PNR " << pnr << " from index " << index << endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (table[index].isOccupied && index != start);

        cout << "Student not found (Linear).\n";
    }

    // Display the linear probing table
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

// ----------------- Chaining Without Replacement -----------------
class HashTableChaining {
private:
    Student table[TABLE_SIZE];

    // Hash function
    int hash(int key) {
        return key % TABLE_SIZE;
    }

    // Finds the next empty slot (starting from the next index)
    int findEmptySlot(int start_index) {
        int i = (start_index + 1) % TABLE_SIZE;
        while (i != start_index) {
            if (!table[i].isOccupied || table[i].isDeleted) return i;
            i = (i + 1) % TABLE_SIZE;
        }
        return -1;  // Table is full
    }

public:
    // Insert using chaining without replacement
    void insert(int pnr, int marks) {
        int index = hash(pnr);

        // If the slot is empty or deleted, insert directly
        if (!table[index].isOccupied || table[index].isDeleted) {
            table[index].pnr = pnr;
            table[index].marks = marks;
            table[index].isOccupied = true;
            table[index].isDeleted = false;
            table[index].chain = -1;
            cout << "Inserted (Chaining) at index " << index << endl;
        } else {
            int original = index;

            // Find an empty slot to store the new record
            int newIndex = findEmptySlot(index);
            if (newIndex == -1) {
                cout << "Hash table (Chaining) is full!\n";
                return;
            }

            // Insert new record
            table[newIndex].pnr = pnr;
            table[newIndex].marks = marks;
            table[newIndex].isOccupied = true;
            table[newIndex].isDeleted = false;
            table[newIndex].chain = -1;

            // Traverse the chain to the last node and link the new record
            int prev = original;
            while (table[prev].chain != -1)
                prev = table[prev].chain;

            table[prev].chain = newIndex;
            cout << "Inserted (Chaining) at index " << newIndex << ", chained from index " << prev << endl;
        }
    }

    // Search using chaining without replacement
    void search(int pnr) {
        int index = hash(pnr);

        while (index != -1) {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].pnr == pnr) {
                cout << "Found (Chaining): Marks = " << table[index].marks << " at index " << index << endl;
                return;
            }
            index = table[index].chain;
        }

        cout << "Student not found (Chaining).\n";
    }

    // Delete using chaining without replacement
    void remove(int pnr) {
        int index = hash(pnr);
        int prev = -1;

        while (index != -1) {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].pnr == pnr) {
                table[index].isDeleted = true;

                // Maintain the chain
                if (prev != -1) {
                    table[prev].chain = table[index].chain;
                } else {
                    int next = table[index].chain;
                    if (next != -1) {
                        table[hash(pnr)] = table[next];  // Replace with next chained value
                        table[next].isDeleted = true;
                        table[hash(pnr)].chain = table[next].chain;
                    }
                }

                table[index].chain = -1;
                cout << "Deleted (Chaining) student with PNR " << pnr << " from index " << index << endl;
                return;
            }
            prev = index;
            index = table[index].chain;
        }

        cout << "Student not found (Chaining).\n";
    }

    // Display the chaining hash table
    void display() {
        cout << "\nHash Table (Chaining Without Replacement):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied && !table[i].isDeleted)
                cout << "[" << i << "] PNR: " << table[i].pnr << ", Marks: " << table[i].marks << ", Chain: " << table[i].chain << endl;
            else
                cout << "[" << i << "] Empty\n";
        }
    }
};

// ----------------- Main Program -----------------
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

        cout << "Select Method: 1. Linear Probing  2. Chaining Without Replacement\n";
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