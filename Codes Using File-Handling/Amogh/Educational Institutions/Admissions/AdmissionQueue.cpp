#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;


struct Student {
    string name;
    int age;
    float marks;
};


void readFromFileAndQueue(queue<Student> &admissionQueue, const string &filename) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    Student student;


    while (getline(inFile, student.name)) {
        inFile >> student.age >> student.marks;
        inFile.ignore(); // Ignore the newline after the marks value

        // Enqueue the student data
        admissionQueue.push(student);
    }

    inFile.close();
}


void displayAdmissionQueue(queue<Student> &admissionQueue) {
    cout << "Admission Queue: " << endl;
    while (!admissionQueue.empty()) {
        Student student = admissionQueue.front();
        admissionQueue.pop();

        cout << "Name: " << student.name << endl;
        cout << "Age: " << student.age << endl;
        cout << "Marks: " << student.marks << endl;
        cout << "-----------------------" << endl;
    }
}

int main() {
    queue<Student> admissionQueue;
    string filename = "student_data.txt";  

 
    readFromFileAndQueue(admissionQueue, filename);

    displayAdmissionQueue(admissionQueue);

    return 0;
}
