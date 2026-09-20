#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() {
        cout << "Roll No: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Course: " << course << endl;
        cout << "------------------------" << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    s.input();
    file.write((char*)&s, sizeof(s));

    file.close();
    cout << "Student added successfully!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    if (!file) {
        cout << "No student records found!\n";
        return;
    }

    cout << "\nStudent Records\n";
    cout << "========================\n";

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }

    file.close();
}

void updateStudent() {
    int roll;
    cout << "Enter Roll No to update: ";
    cin >> roll;

    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "Enter new student details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            found = true;
            cout << "Student updated successfully!\n";
            break;
        }
    }

    if (!found)
        cout << "Student not found!\n";

    file.close();
}

void deleteStudent() {
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    Student s;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            found = true;
        } else {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}