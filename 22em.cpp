#include <bits/stdc++.h> // Includes all standard headers
using namespace std;

// Structure to represent an Employee
struct Employee {
    string employeeID;    // Unique ID for employee
    string name;          // Employee's full name
    string designation;   // Job title or position
    float salary;         // Salary of the employee

    // Convert an Employee object into a comma-separated string
    string toString() const {
        return employeeID + "," + name + "," + designation + "," + to_string(salary);
    }

    // Create an Employee object from a comma-separated string
    static Employee fromString(const string &data) {
        stringstream ss(data);
        string employeeID, name, designation;
        float salary;

        // Parse components of the employee record
        getline(ss, employeeID, ',');
        getline(ss, name, ',');
        getline(ss, designation, ',');
        ss >> salary; // Salary is read after last comma (not using getline)

        return Employee{employeeID, name, designation, salary};
    }
};

// Add a new employee record to the file
void addEmployee(const Employee &employee) {
    ofstream file("employees.txt", ios::app); // Open in append mode
    file << employee.toString() << endl;      // Write employee data
    file.close();
    cout << "Employee added successfully!" << endl;
}

// Display details of a specific employee using their ID
void displayEmployee(const string &employeeID) {
    ifstream file("employees.txt");  // Open file to read
    string line;
    bool found = false;

    while (getline(file, line)) {
        Employee employee = Employee::fromString(line);
        if (employee.employeeID == employeeID) {
            // If employee ID matches, print their details
            cout << "Employee found:\n";
            cout << "Employee ID: " << employee.employeeID << endl;
            cout << "Name: " << employee.name << endl;
            cout << "Designation: " << employee.designation << endl;
            cout << "Salary: " << employee.salary << endl;
            found = true;
            break; // Stop searching after finding the employee
        }
    }

    if (!found) {
        cout << "Employee with ID " << employeeID << " not found!" << endl;
    }

    file.close();
}

// Delete a specific employee from the file using their ID
void deleteEmployee(const string &employeeID) {
    ifstream file("employees.txt");        // Open original file for reading
    ofstream tempFile("temp.txt");         // Temporary file to store remaining records
    string line;
    bool found = false;

    while (getline(file, line)) {
        Employee employee = Employee::fromString(line);
        if (employee.employeeID == employeeID) {
            // Skip writing this employee (effectively deleting)
            found = true;
            continue;
        }
        tempFile << line << endl;  // Write valid records to temp file
    }

    file.close();
    tempFile.close();

    if (found) {
        // Replace original file with updated temp file
        remove("employees.txt");
        rename("temp.txt", "employees.txt");
        cout << "Employee deleted successfully!" << endl;
    } else {
        cout << "Employee with ID " << employeeID << " not found!" << endl;
    }
}

// Main function: Menu-driven interface
int main() {
    int choice;
    string employeeID, name, designation;
    float salary;

    while (true) {
        // Display the main menu
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employee Details\n";
        cout << "3. Delete Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Take input and add a new employee
                cout << "Enter Employee ID: ";
                cin >> employeeID;
                cin.ignore();  // Flush newline character
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Designation: ";
                getline(cin, designation);
                cout << "Enter Salary: ";
                cin >> salary;

                addEmployee(Employee{employeeID, name, designation, salary});
                break;

            case 2:
                // Search and display an employee by ID
                cout << "Enter Employee ID to display: ";
                cin >> employeeID;
                displayEmployee(employeeID);
                break;

            case 3:
                // Delete an employee record by ID
                cout << "Enter Employee ID to delete: ";
                cin >> employeeID;
                deleteEmployee(employeeID);
                break;

            case 4:
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