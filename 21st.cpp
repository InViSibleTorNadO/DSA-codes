#include <bits/stdc++.h>  // Includes all standard libraries
using namespace std;

// Structure to represent a student
struct Student {
    string rollNo;     // Student Roll Number
    string name;       // Student Name
    string division;   // Student Division (e.g., A, B, C)
    string address;    // Student Address

    // Method to convert Student object to a comma-separated string for file storage
    string toString() const {
        return rollNo + "," + name + "," + division + "," + address;
    }

    // Static method to convert a comma-separated string back to a Student object
    static Student fromString(const string& data) {
        stringstream ss(data);  // Create a stream to read from string
        string rollNo, name, division, address;

        // Read values separated by commas
        getline(ss, rollNo, ',');
        getline(ss, name, ',');
        getline(ss, division, ',');
        getline(ss, address);

        // Return constructed student
        return Student{rollNo, name, division, address};
    }
};

// Function to add a student to the file
void addStudent(const Student& student) {
    ofstream file("students.txt", ios::app);  // Open file in append mode
    file << student.toString() << endl;       // Write student data as a line
    file.close();
    cout << "Student added successfully!" << endl;
}

// Function to display all students from the file
void displayStudents() {
    ifstream file("students.txt");  // Open file in read mode
    string line;
    while (getline(file, line)) {
        Student student = Student::fromString(line);  // Convert each line to Student object
        cout << "Roll No: " << student.rollNo 
             << ", Name: " << student.name
             << ", Division: " << student.division 
             << ", Address: " << student.address << endl;
    }
    file.close();
}

// Function to search for a student by roll number
void searchStudent(const string& rollNo) {
    ifstream file("students.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        Student student = Student::fromString(line);
        if (student.rollNo == rollNo) {
            // Match found, print details
            cout << "Student found:\n";
            cout << "Roll No: " << student.rollNo 
                 << ", Name: " << student.name
                 << ", Division: " << student.division 
                 << ", Address: " << student.address << endl;
            found = true;
            break;  // Exit loop after finding student
        }
    }

    if (!found) {
        cout << "Student with Roll No: " << rollNo << " not found!" << endl;
    }

    file.close();
}

// Function to delete a student by roll number
void deleteStudent(const string& rollNo) {
    ifstream file("students.txt");
    ofstream tempFile("temp.txt");  // Temporary file to store remaining students
    string line;
    bool found = false;

    while (getline(file, line)) {
        Student student = Student::fromString(line);
        if (student.rollNo == rollNo) {
            found = true;  // Skip this student (delete)
            continue;
        }
        tempFile << line << endl;  // Copy other students to temp file
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("students.txt");               // Delete original file
        rename("temp.txt", "students.txt");   // Rename temp file to original name
        cout << "Student deleted successfully!" << endl;
    } else {
        cout << "Student with Roll No: " << rollNo << " not found!" << endl;
    }
}

// Main function - menu driven interface
int main() {
    int choice;
    string rollNo, name, division, address;

    while (true) {
        // Display menu
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Delete Student by Roll No\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Input student details and add to file
                cout << "Enter Roll No: ";
                cin >> rollNo;
                cin.ignore();  // Ignore leftover newline
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Division: ";
                getline(cin, division);
                cout << "Enter Address: ";
                getline(cin, address);
                addStudent(Student{rollNo, name, division, address});
                break;

            case 2:
                // Display all students
                displayStudents();
                break;

            case 3:
                // Search for a student
                cout << "Enter Roll No to search: ";
                cin >> rollNo;
                searchStudent(rollNo);
                break;

            case 4:
                // Delete a student
                cout << "Enter Roll No to delete: ";
                cin >> rollNo;
                deleteStudent(rollNo);
                break;

            case 5:
                // Exit the program
                cout << "Exiting...\n";
                return 0;

            default:
                // Handle invalid menu input
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}