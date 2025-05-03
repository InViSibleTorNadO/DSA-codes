#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

class StudentDatabase
{
    // Structure to represent a student record
    struct Student
    {
        char name[10];      // Name of the student
        int rollNumber;     // Roll number of the student
        int division;       // Division of the student
        char address[10];   // Address of the student
    };

    Student studentRecord;  // Object to hold individual student record
    static int totalRecords;  // Static variable to keep track of total student records

public:
    // Function to add a new student record to the database
    void addStudent()
    {
        // Input the student's details
        cout << "ENTER NAME: ";
        cin.ignore();  // To ignore any previous newline character left in the input buffer
        cin.getline(studentRecord.name, 10);  // Name (maximum 10 characters)

        cout << "ENTER ROLL NO: ";
        cin >> studentRecord.rollNumber;  // Roll number

        cout << "ENTER DIVISION: ";
        cin >> studentRecord.division;  // Division

        cout << "ENTER ADDRESS: ";
        cin.ignore();  // Clear the input buffer
        cin.getline(studentRecord.address, 10);  // Address (maximum 10 characters)

        // Open the file in append binary mode
        fstream file("STUDENT.DAT", ios::out | ios::app | ios::binary);

        // Write the student record to the file
        file.write((char *)&studentRecord, sizeof(studentRecord));
        file.close();

        totalRecords++;  // Increment the total records count
    }

    // Function to delete a student by roll number
    void deleteStudent(int rollNumber)
    {
        fstream file("STUDENT.DAT", ios::in | ios::out | ios::binary);
        int index = 0;

        // Traverse through all the records to find the matching roll number
        while (index < totalRecords)
        {
            file.seekg(index * sizeof(studentRecord));  // Move to the current student record
            file.read((char *)&studentRecord, sizeof(studentRecord));  // Read the record

            if (studentRecord.rollNumber == rollNumber)  // If student is found
            {
                // Mark the record as deleted by setting its fields to default values
                strcpy(studentRecord.name, "");
                strcpy(studentRecord.address, "");
                studentRecord.rollNumber = -1;
                studentRecord.division = -1;

                // Write the updated record (marked as deleted) back to the file
                file.seekp(index * sizeof(studentRecord));
                file.write((char *)&studentRecord, sizeof(studentRecord));
                file.close();
                return;
            }

            index++;  // Move to the next record
        }

        cout << "STUDENT NOT FOUND \n";  // If student with given roll number is not found
        file.close();
    }

    // Function to display all student records
    void displayAllStudents()
    {
        // Print the column headers with proper alignment
        cout << setw(15) << "NAME"
             << setw(15) << "ROLL NO"
             << setw(15) << "DIVISION"
             << setw(15) << "ADDRESS\n";

        fstream file("STUDENT.DAT", ios::in | ios::binary);

        // Traverse through all records and display valid student records
        for (int i = 0; i < totalRecords; i++)
        {
            file.seekg(i * sizeof(studentRecord));  // Move to the current student record
            file.read((char *)&studentRecord, sizeof(studentRecord));  // Read the record

            // Display the record only if it is not marked as deleted (roll number != -1)
            if (studentRecord.rollNumber != -1)
            {
                cout << setw(15) << studentRecord.name
                     << setw(15) << studentRecord.rollNumber
                     << setw(15) << studentRecord.division
                     << setw(15) << studentRecord.address << "\n";
            }
        }

        file.close();
    }

    // Function to search for a student by roll number
    void findStudent(int rollNumber)
    {
        fstream file("STUDENT.DAT", ios::in | ios::binary);
        int index = 0;

        // Traverse through all the student records to find the matching roll number
        while (index < totalRecords)
        {
            file.seekg(index * sizeof(studentRecord));  // Move to the current student record
            file.read((char *)&studentRecord, sizeof(studentRecord));  // Read the record

            if (studentRecord.rollNumber == rollNumber)  // If student is found
            {
                // Display the found student's details
                cout << "\n STUDENT FOUND:\n";
                cout << "NAME: " << studentRecord.name << endl;
                cout << "ROLL NO: " << studentRecord.rollNumber << endl;
                cout << "DIVISION: " << studentRecord.division << endl;
                cout << "ADDRESS: " << studentRecord.address << endl;
                file.close();
                return;
            }

            index++;  // Move to the next record
        }

        cout << "STUDENT NOT FOUND \n";  // If student with given roll number is not found
        file.close();
    }
};

// Static member variable to keep track of total student records
int StudentDatabase::totalRecords = 0;

int main()
{
    StudentDatabase db;  // Create a StudentDatabase object

    while (true)
    {
        // Display the menu to the user
        cout << "\n MENU:\n"
             << "1. Add Student\n"
             << "2. Display All Students\n"
             << "3. Search Student by Roll No\n"
             << "4. Delete Student\n";
        cout << " Enter your choice: ";

        int choice;
        cin >> choice;  // Get the user's choice

        // Perform the operation based on the user's choice
        switch (choice)
        {
        case 1:  // Add a new student
        {
            db.addStudent();
            break;
        }
        case 2:  // Display all students
        {
            db.displayAllStudents();
            break;
        }
        case 3:  // Search for a student by roll number
        {
            cout << " Enter Roll No to Search: ";
            int roll;
            cin >> roll;
            db.findStudent(roll);
            break;
        }
        case 4:  // Delete a student by roll number
        {
            cout << " Enter Roll No to Delete: ";
            int roll;
            cin >> roll;
            db.deleteStudent(roll);
            break;
        }
        default:
            cout << "Invalid choice, try again\n";  // Handle invalid menu choice
        }
    }
}
