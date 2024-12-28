#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    int roll_no;
    string name;
    int age;
    float marks;
};

void save_to_file(Student students[], int count, const string &filename) {
    ofstream out_file(filename);
    if (!out_file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        out_file << students[i].roll_no << endl;
        out_file << students[i].name << endl;
        out_file << students[i].age << endl;
        out_file << students[i].marks << endl;
    }

    out_file.close();
    cout << "Data has been saved to " << filename << endl;
}

int main() {
    int n;

    cout << "Enter the number of students: ";
    cin >> n;

    Student students[n];

    for (int i = 0; i < n; i++) {
        cin.ignore();
        cout << "Enter roll number of student " << i + 1 << ": ";
        cin >> students[i].roll_no;

        cin.ignore();

        cout << "Enter name of student " << i + 1 << ": ";
        getline(cin, students[i].name);

        cout << "Enter age of student " << i + 1 << ": ";
        cin >> students[i].age;

        cout << "Enter marks of student " << i + 1 << ": ";
        cin >> students[i].marks;
    }

    string filename = "student_data.txt";
    save_to_file(students, n, filename);

    return 0;
}
