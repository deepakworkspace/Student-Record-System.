#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string name;
    int roll;
    float grade;
};

vector<Student> students;

void addStudent() {
    Student s;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter roll number: ";
    cin >> s.roll;
    cout << "Enter grade: ";
    cin >> s.grade;
    students.push_back(s);
    cout << "Student added successfully.\n";
}

void displayStudents() {
    if (students.empty()) {
        cout << "No student records to display.\n";
        return;
    }
    cout << "\nStudent Records:\n";
    for (const auto& s : students) {
        cout << "Name: " << s.name << ", Roll No: " << s.roll << ", Grade: " << s.grade << endl;
    }
}

void deleteStudent() {
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->roll == roll) {
            students.erase(it);
            cout << "Student deleted successfully.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void saveToFile(const string& filename) {
    ofstream fout(filename);
    for (const auto& s : students) {
        fout << s.name << "," << s.roll << "," << s.grade << endl;
    }
    fout.close();
    cout << "Records saved to file.\n";
}

void loadFromFile(const string& filename) {
    ifstream fin(filename);
    students.clear();
    Student s;
    string line;
    while (getline(fin, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        s.name = line.substr(0, pos1);
        s.roll = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        s.grade = stof(line.substr(pos2 + 1));
        students.push_back(s);
    }
    fin.close();
    cout << "Records loaded from file.\n";
}

int main() {
    int choice;
    string filename = "students.txt";
    loadFromFile(filename);

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n2. Display Students\n3. Delete Student\n4. Save Records\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); break;
            case 4: saveToFile(filename); break;
            case 5: saveToFile(filename); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
