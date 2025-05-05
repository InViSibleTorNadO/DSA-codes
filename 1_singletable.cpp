#include <bits/stdc++.h>
using namespace std;

// Structure to store student details
struct Student {
    int prn;          // Primary key (e.g., roll number)
    int marks;        // Student marks
    int chain;        // Chain link to next index in case of collision (for chaining)
    bool isOccupied;  // To check if the slot is occupied

    // Default constructor
    Student() : prn(-1), marks(0), chain(-1), isOccupied(false) {}
};

// HashTable class using linear probing and chaining without replacement
class HashTable {
private:
    vector<Student> dataBase; // Hash table storing Student records
    int size;                 // Size of the hash table

    // Hash function to map PRN to index
    int hashFunction(int prn) {
        return prn % size;
    }

public:
    // Constructor to initialize hash table of given size
    HashTable(int n) : size(n), dataBase(n) {}

    // Insert using Linear Probing
    void insertLinearProbing(int prn, int marks) {
        int index = hashFunction(prn);
        int originalIndex = index;

        // Find next available slot using linear probing
        while (dataBase[index].isOccupied) {
            index = (index + 1) % size;
            if (index == originalIndex) {
                cout << "Table is full.\n";
                return;
            }
        }

        // Insert the student details
        dataBase[index].prn = prn;
        dataBase[index].marks = marks;
        dataBase[index].isOccupied = true;
        cout << "Inserted at index " << index << " using linear probing.\n";
    }

    // Insert using Chaining Without Replacement
    void insertChainingWithoutReplacement(int prn, int marks) {
        int index = hashFunction(prn);
        int originalIndex = index;

        // If home slot is free, insert directly
        if (!dataBase[index].isOccupied) {
            dataBase[index].prn = prn;
            dataBase[index].marks = marks;
            dataBase[index].isOccupied = true;
            cout << "Inserted at index " << index << ".\n";
        } else {
            // Traverse to end of existing chain
            while (dataBase[index].chain != -1) {
                index = dataBase[index].chain;
            }

            // Find a free slot for the new element
            int next = (index + 1) % size;
            while (dataBase[next].isOccupied) {
                next = (next + 1) % size;
                if (next == originalIndex) {
                    cout << "Table is full.\n";
                    return;
                }
            }

            // Update chain link and insert student data
            dataBase[index].chain = next;
            dataBase[next].prn = prn;
            dataBase[next].marks = marks;
            dataBase[next].isOccupied = true;
            cout << "Inserted at index " << next << " with chaining (without replacement).\n";
        }
    }

    // Delete entry using Linear Probing
    void deleteLinearProbing(int prn) {
        int index = hashFunction(prn);
        int originalIndex = index;

        // Search for the PRN using linear probing
        while (dataBase[index].isOccupied) {
            if (dataBase[index].prn == prn) {
                // Mark the slot as deleted
                dataBase[index].prn = -1;
                dataBase[index].marks = 0;
                dataBase[index].isOccupied = false;
                dataBase[index].chain = -1;
                cout << "Deleted PRN " << prn << " from index " << index << ".\n";
                return;
            }
            index = (index + 1) % size;
            if (index == originalIndex) break;
        }

        cout << "PRN " << prn << " not found.\n";
    }

    // Display the hash table
    void display() {
        cout << "Index\tPRN\tMarks\tChain\n";
        for (int i = 0; i < size; i++) {
            cout << i << "\t" 
                 << (dataBase[i].prn == -1 ? "-" : to_string(dataBase[i].prn)) << "\t"
                 << dataBase[i].marks << "\t"
                 << dataBase[i].chain << "\n";
        }
    }
};

int main() {
    int n;
    cout << "Enter number of students (table size): ";
    cin >> n;
    HashTable data(n);

    // Menu-driven interface
    cout << "\nMENU:\n";
    cout << "1. Insert (Linear Probing)\n";
    cout << "2. Insert (Chaining without Replacement)\n";
    cout << "3. Display Table\n";
    cout << "4. Delete\n";
    cout << "5. Exit\n";

    while (true) {
        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;
        int prn, marks;

        switch (choice) {
            case 1:
                cout << "Enter PRN: ";
                cin >> prn;
                cout << "Enter Marks: ";
                cin >> marks;
                data.insertLinearProbing(prn, marks);
                break;

            case 2:
                cout << "Enter PRN: ";
                cin >> prn;
                cout << "Enter Marks: ";
                cin >> marks;
                data.insertChainingWithoutReplacement(prn, marks);
                break;

            case 3:
                data.display();
                break;

            case 4:
                cout << "Enter PRN to delete: ";
                cin >> prn;
                data.deleteLinearProbing(prn);
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}