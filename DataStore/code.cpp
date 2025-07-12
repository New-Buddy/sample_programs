#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class StudentData {
private:
    int* rollNo;
    string* name;
    float* marks;
    int size;
    string filename;

public:
    StudentData(int n, const string& file_name) : filename(file_name) {
        size = n;
        rollNo = new int[size];
        name = new string[size];
        marks = new float[size];
    }

    void addData() {
        cout << "\nEnter student data:\n";
        cout << string(32, '-') << endl;
        for (int i = 0; i < size; i++) {
            cout << "Enter details for student " << (i + 1) << ":\n";

            cout << "Enter Roll Number: ";
            cin >> rollNo[i];
            cin.ignore();  

            cout << "Enter Student Name: ";
            getline(cin, name[i]);

            cout << "Enter Marks: ";
            cin >> marks[i];
            cout << endl;
        }
    }

    void writeToFile() {
        ofstream file(filename);
        if (!file) {
            cout << "Error in creating file: " << filename << endl;
            return;
        }

        cout << "Writing data to file: " << filename << endl;
        file << string(45, '-') << endl;
        file << "| " << left << setw(10) << "Roll No"
             << "| " << setw(20) << "Name"
             << "| " << setw(8) << "Marks" << "|\n";
        file << string(45, '-') << endl;

        for (int i = 0; i < size; ++i) {
            file << "| " << left << setw(10) << rollNo[i]
                 << "| " << setw(20) << name[i]
                 << "| " << fixed << setprecision(2) << setw(8) << marks[i] << "|\n";
        }

        file << string(45, '-') << endl;
        file.close();

        cout << "Data written to file successfully.\n";
    }

    void readFromFile() {
        ifstream file(filename);
        if (!file) {
            cout << "Error in opening file: " << filename << endl;
            return;
        }

        cout << "\nReading data from file: " << filename << "\n\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    ~StudentData() {
        delete[] rollNo;
        delete[] name;
        delete[] marks;
    }
};

int main() {
    int n;
    string filename;

    cout << "Enter filename to store student data: ";
    getline(cin, filename);

    cout << "Enter number of students: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of students. Exiting...\n";
        return 1;
    }



    filename += ".txt";

    StudentData studentData(n, filename);
    studentData.addData();
    studentData.writeToFile();
    studentData.readFromFile();

    return 0;
}
