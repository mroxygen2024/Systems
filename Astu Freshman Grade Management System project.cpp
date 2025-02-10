#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


const int TOTAL_STUDENTS = 30; // Maximum number of students, since the number of students is 20-30 per section in this university.

// Student structure to hold student data
struct Student {
    string studentID;
    string name;
    int marks[6]; // Marks for c++, emerging, maths, english, logic, drawing
};

// Function prototypes
void enterStudentData(Student students[], int &total);
void displayAllStudents(Student students[], int total);
void searchStudentByStudentID(Student students[], int total);
string calculateGrade(int marks);
double calculateGPA(int marks[], int creditHours[]);

int main(){


    Student students[TOTAL_STUDENTS]; // Array to store student data
    int total = 0; // To keep the total number of students

    int choice;
    do {
        cout << "\n ASTU Pre-Engineering Students Grade Management System\n";
        cout << "1. Enter student data\n";
        cout << "2. Display all students\n";
        cout << "3. Search student by Student ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.get(); // To clear the newline character from the input buffer, we haven't learned this but we used it just to make our code more functional.

        switch (choice) {
            case 1:
                enterStudentData(students, total);
                break;
            case 2:
                displayAllStudents(students, total);
                break;
            case 3:
                searchStudentByStudentID(students, total);
                break;
            case 4:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again later.\n";
        }
    } while (choice != 4);

    return 0;
}

// This is the function to enter student data
void enterStudentData(Student students[], int &total) {
    if (total >= TOTAL_STUDENTS) {
        cout << "Cannot add more students. Maximum limit reached." << endl;
        return;
    }

    cout << "Enter student's ID: ";
    getline(cin, students[total].studentID);
    cout << "Enter student's full name: ";
    getline(cin, students[total].name);
    cout << "Enter marks for the following subjects (only write 1-100):\n";
        for (int i = 0; i < 6; ++i) {
        do {
            switch (i) {
                case 0: cout << "Emerging: "; break;
                case 1: cout << "Maths: "; break;
                case 2: cout << "English: "; break;
                case 3: cout << "Logic: "; break;
                case 4: cout << "Drawing: "; break;
                case 5: cout << "C++: "; break;
            }
            cin >> students[total].marks[i];
            if (students[total].marks[i] < 0 || students[total].marks[i] > 100) {
                cout << "Invalid marks. Please enter a value between 0 and 100.\n";
            }
        } while (students[total].marks[i] < 0 || students[total].marks[i] > 100);
    }
    cin.get(); // To clear the newline character from the input buffer

    total++;
    cout << "Student data entered successfully." << endl;
}

// This is the function to display all students
void displayAllStudents(Student students[], int total) {
    if (total == 0) {
        cout << "No students in the system." << endl;
        return;
    }

    for (int i = 0; i < total; ++i) {
        cout << "Name: " << students[i].name <<"\nStudent ID: " << students[i].studentID << "\nMarks: ";
        cout << "C++: " << students[i].marks[0] << " (" << calculateGrade(students[i].marks[0]) << "), ";
        cout << "Emerging: " << students[i].marks[1] << " (" << calculateGrade(students[i].marks[1]) << "), ";
        cout << "Maths: " << students[i].marks[2] << " (" << calculateGrade(students[i].marks[2]) << "), ";
        cout << "English: " << students[i].marks[3] << " (" << calculateGrade(students[i].marks[3]) << "), ";
        cout << "Logic: " << students[i].marks[4] << " (" << calculateGrade(students[i].marks[4]) << "), ";
        cout << "Drawing: " << students[i].marks[5] << " (" << calculateGrade(students[i].marks[5]) << ")\n";

        int creditHours[6];
        cout << "Enter credit hours (respectively separated with space) for C++, Emerging, Maths, English, Logic, Drawing: ";
        for (int j = 0; j < 6; ++j) {
            cin >> creditHours[j];
        }

        double gpa = calculateGPA(students[i].marks, creditHours);
        cout << "Cumulative GPA: " << gpa << endl;
    }
}

// Function to search student by Student ID
void searchStudentByStudentID(Student students[], int total) {
    if (total == 0) {
        cout << "No students in the system." << endl;
        return;
    }

    string studentID;
    cout << "Enter student's ID to search: ";
    getline(cin, studentID);

    bool found = false;
    for (int i = 0; i < total; ++i) {
        if (students[i].studentID == studentID) {
            found = true;
            cout << "Student found:\n";
            cout << "Student ID: " << students[i].studentID << "\nName: " << students[i].name << "\nMarks: ";
            cout << "Emerging: " << students[i].marks[0] << " (" << calculateGrade(students[i].marks[0]) << "), ";
            cout << "Maths: " << students[i].marks[1] << " (" << calculateGrade(students[i].marks[1]) << "), ";
            cout << "English: " << students[i].marks[2] << " (" << calculateGrade(students[i].marks[2]) << "), ";
            cout << "Logic: " << students[i].marks[3] << " (" << calculateGrade(students[i].marks[3]) << "), ";
            cout << "Drawing: " << students[i].marks[4] << " (" << calculateGrade(students[i].marks[4]) << "),";
            cout << "C++: " << students[i].marks[5] << " (" << calculateGrade(students[i].marks[5]) << ")\n";

            int creditHours[6];
            cout << "Enter credit hours (respectively separated with space) for C++, Emerging, Maths, English, Logic, Drawing : ";
            for (int j = 0; j < 6; ++j) {
                cin >> creditHours[j];
            }

            double gpa = calculateGPA(students[i].marks, creditHours);
            cout << "Cumulative GPA: " << gpa << endl;
            break;
        }
    }

    if (!found) {
        cout << "Student with ID " << studentID << " not found." << endl;
    }
}

// Function to calculate grade
string calculateGrade(int marks) {
    if (marks >= 90) return "A+";
    else if (marks >= 85) return "A";
    else if (marks >= 80) return "A-";
    else if (marks >= 75) return "B+";
    else if (marks >= 70) return "B";
    else if (marks >= 65) return "B-";
    else if (marks >= 60) return "C+";
    else if (marks >= 50) return "C";
    else if (marks >= 45) return "C-";
    else if (marks >= 40) return "D";
    else return "F";
}

// This is function to calculate GPA
double calculateGPA(int marks[], int creditHours[]) {
    double totalPoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < 5; ++i) {
        double gradePoint;
        if (marks[i] >= 90) gradePoint = 4.0;
        else if (marks[i] >= 85) gradePoint = 4.0;
        else if (marks[i] >= 80) gradePoint = 3.75;
        else if (marks[i] >= 75) gradePoint = 3.5;
        else if (marks[i] >= 70) gradePoint = 3.0;
        else if (marks[i] >= 65) gradePoint = 2.75;
        else if (marks[i] >= 60) gradePoint = 2.5;
        else if (marks[i] >= 50) gradePoint = 2.0;
        else if (marks[i] >= 45) gradePoint = 1.75;
        else if (marks[i] >= 40) gradePoint = 1.0;
        else gradePoint = 0.0;

        totalPoints += gradePoint * creditHours[i];
        totalCredits += creditHours[i];
    }

    return totalPoints / totalCredits;
}

