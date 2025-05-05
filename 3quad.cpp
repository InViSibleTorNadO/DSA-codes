#include <bits/stdc++.h>
using namespace std;

const int TABLE_SIZE = 10; // Size of the hash table

// Structure to hold student information
struct Student {
    int pnr;            // Student's unique PNR number
    int marks;          // Student's marks
    bool isOccupied;    // Indicates if the slot is filled

    // Constructor to initialize student entry as empty
    Student() {
        pnr = -1;
        marks = 0;
        isOccupied = false;
    }
};

// =================== LINEAR PROBING ===================
class HashTableLinear {
private:
    Student table[TABLE_SIZE]; // Fixed-size hash table

    // Hash function to compute index
    int hash(int key) {
        return key % TABLE_SIZE;
    }

public:
    // Insert student record using linear probing
    void insert(int pnr, int marks) {
        int index = hash(pnr);
        int start = index;

        do {
            // If slot is empty, insert the record
            if (!table[index].isOccupied) {
                table[index].pnr = pnr;
                table[index].marks = marks;
                table[index].isOccupied = true;
                cout << "Inserted (Linear) at index " << index << endl;
                return;
            }
            // Move to next slot (linear probing)
            index = (index + 1) % TABLE_SIZE;
        } while (index != start); // Loop until we come back to starting index

        cout << "Hash table is full (Linear)!\n";
    }

    // Search for a record using linear probing
    void search(int pnr) {
        int index = hash(pnr);
        int start = index;

        do {
            // If the matching record is found
            if (table[index].isOccupied && table[index].pnr == pnr) {
                cout << "Found (Linear): Marks = " << table[index].marks << " at index " << index << endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (table[index].isOccupied && index != start); // Stop if looped back

        cout << "Student not found (Linear).\n";
    }

    // Display contents of the hash table
    void display() {
        cout << "\nHash Table (Linear Probing):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied)
                cout << "[" << i << "] PNR: " << table[i].pnr << ", Marks: " << table[i].marks << endl;
            else
                cout << "[" << i << "] Empty\n";
        }
    }
};

// =================== QUADRATIC PROBING ===================
class HashTableQuadratic {
private:
    Student table[TABLE_SIZE]; // Fixed-size hash table

    // Hash function to compute index
    int hash(int key) {
        return key % TABLE_SIZE;
    }

public:
    // Insert student record using quadratic probing
    void insert(int pnr, int marks) {
        int index = hash(pnr);
        int i = 0;

        // Try different slots using quadratic formula
        while (i < TABLE_SIZE) {
            int newIndex = (index + i * i) % TABLE_SIZE;
            if (!table[newIndex].isOccupied) {
                table[newIndex].pnr = pnr;
                table[newIndex].marks = marks;
                table[newIndex].isOccupied = true;
                cout << "Inserted (Quadratic) at index " << newIndex << endl;
                return;
            }
            i++;
        }

        cout << "Hash table is full (Quadratic)!\n";
    }

    // Search for a record using quadratic probing
    void search(int pnr) {
        int index = hash(pnr);
        int i = 0;

        // Use quadratic formula to check possible positions
        while (i < TABLE_SIZE) {
            int newIndex = (index + i * i) % TABLE_SIZE;

            // If match found
            if (table[newIndex].isOccupied && table[newIndex].pnr == pnr) {
                cout << "Found (Quadratic): Marks = " << table[newIndex].marks << " at index " << newIndex << endl;
                return;
            }

            // Stop early if we hit an empty spot
            if (!table[newIndex].isOccupied)
                break;

            i++;
        }

        cout << "Student not found (Quadratic).\n";
    }

    // Display contents of the hash table
    void display() {
        cout << "\nHash Table (Quadratic Probing):\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied)
                cout << "[" << i << "] PNR: " << table[i].pnr << ", Marks: " << table[i].marks << endl;
            else
                cout << "[" << i << "] Empty\n";
        }
    }
};

// =================== MAIN MENU ===================
int main() {
    HashTableLinear linearHash;         // Object for linear probing
    HashTableQuadratic quadraticHash;   // Object for quadratic probing

    int choice, method, pnr, marks;

    do {
        // Display menu options
        cout << "\n--- Student Hash Table Menu ---\n";
        cout << "1. Insert\n2. Search\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 4) break;

        // Ask for method
        cout << "Select Method: 1. Linear Probing  2. Quadratic Probing\n";
        cin >> method;

        switch (choice) {
            case 1: // Insert
                cout << "Enter PNR and Marks: ";
                cin >> pnr >> marks;
                if (method == 1)
                    linearHash.insert(pnr, marks);
                else
                    quadraticHash.insert(pnr, marks);
                break;

            case 2: // Search
                cout << "Enter PNR to search: ";
                cin >> pnr;
                if (method == 1)
                    linearHash.search(pnr);
                else
                    quadraticHash.search(pnr);
                break;

            case 3: // Display table
                if (method == 1)
                    linearHash.display();
                else
                    quadraticHash.display();
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (true); // Loop until user chooses to exit

    return 0;
}