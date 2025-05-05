#include <bits/stdc++.h> // Includes all standard C++ libraries
using namespace std;

const int TABLE_SIZE = 101; // Prime number for hash table size (better distribution of hash values)

// -------------------- Hash Table Class --------------------
class HashTable {
private:
    vector<list<string>> table; // Hash table using chaining (each index stores a list of strings)

    // Hash function using polynomial rolling hash
    int hash(const string& word) {
        int hashVal = 0;
        for (char ch : word) {
            hashVal = (hashVal * 31 + ch) % TABLE_SIZE; // 31 is a small prime multiplier
        }
        return hashVal;
    }

public:
    // Constructor to initialize the hash table
    HashTable() {
        table.resize(TABLE_SIZE); // Resize vector to TABLE_SIZE (each entry is a list)
    }

    // Insert a word into the hash table
    void insert(const string& word) {
        int index = hash(word);           // Compute hash index
        table[index].push_back(word);     // Insert word at that index (chaining)
    }

    // Search for a word in the hash table
    bool search(const string& word) {
        int index = hash(word);           // Compute hash index
        for (const auto& w : table[index]) {
            if (w == word)                // Check each word in the list at index
                return true;
        }
        return false;                     // Not found
    }

    // Load dictionary file and insert each word into hash table
    void loadDictionary(const string& filename) {
        ifstream file(filename);          // Open the file
        if (!file) {
            cerr << "Error: Unable to open dictionary file.\n";
            exit(1);                      // Exit if file can't be opened
        }

        string word;
        while (file >> word) {            // Read each word
            insert(word);                 // Insert word into hash table
        }

        file.close();                     // Close the file
        cout << "Dictionary loaded successfully.\n";
    }
};

// -------------------- Main Program --------------------
int main() {
    HashTable dictionary;                 // Create a HashTable object

    string filename = "dictionary.txt";   // Name of dictionary file
    dictionary.loadDictionary(filename);  // Load words into the hash table

    cout << "\nEnter words to check spelling (type 'exit' to stop):\n";

    string input;
    while (true) {
        cout << "> ";
        cin >> input;

        if (input == "exit") break;       // Stop loop on 'exit'

        if (dictionary.search(input))
            cout << "'" << input << "' is spelled correctly.\n";
        else
            cout << "'" << input << "' is not found in dictionary.\n";
    }

    return 0;
}