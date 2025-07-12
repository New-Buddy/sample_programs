#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class StudentData
{
private:
    int *rollNo;
    string *name;
    float *marks;
    int size = 100;
    string filename;
    int numStudents;

public:
    StudentData(const string &file_name) : filename(file_name)
    {
        rollNo = new int[size];
        name = new string[size];
        marks = new float[size];
        numStudents = 0;

        ifstream file(filename);
        if (!file)
        {
            cout << "Error in opening file: " << filename << endl;
            return;
        }

        string line;
        int count = 0;
        while (getline(file, line))
        {
            // Skip header and separator lines
            if (line.find('-') != string::npos || line.find("Roll") != string::npos)
                continue;

            // Parse line only if it has enough length
            if (line.length() < 45) continue;

            try {
                int r = stoi(line.substr(2, 10));
                string n = line.substr(14, 20);
                float m = stof(line.substr(36, 8));
                n.erase(n.find_last_not_of(" ") + 1);
                rollNo[count] = r;
                name[count] = n;
                marks[count] = m;
                count++;
            } catch (...) {
                // skip malformed lines
                continue;
            }
        }

        numStudents = count;
        file.close();
    }

    StudentData(int n, const string &file_name) : filename(file_name), numStudents(n)
    {
        rollNo = new int[size];
        name = new string[size];
        marks = new float[size];
    }

    void createFile()
    {
        ofstream file(filename);
        if (!file)
        {
            cout << "Error in creating file: " << filename << endl;
            return;
        }

        file << string(45, '-') << endl;
        file << "| " << left << setw(10) << "Roll No"
             << "| " << setw(20) << "Name"
             << "| " << setw(8) << "Marks" << "|\n";
        file << string(45, '-') << endl;

        cout << "File created successfully: " << filename << endl;
        file.close();
    }

    void addData()
    {
        int n;
        cout << "Enter number of students to add: ";
        cin >> n;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int originalSize = numStudents;
        numStudents += n;

        cout << "\nEnter student data:\n";
        cout << string(32, '-') << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "Enter details for student " << (i + 1) << ":\n";

            cout << "Enter Roll Number: ";
            cin >> rollNo[i + originalSize];
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Enter Student Name: ";
            getline(cin, name[i + originalSize]);

            cout << "Enter Marks: ";
            cin >> marks[i + originalSize];
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << endl;
        }
    }

    void modifyStudent()
    {
        int roll;
        cout << "Enter Roll Number of student to modify: ";
        cin >> roll;
        cin.ignore();

        for (int i = 0; i < numStudents; i++)
        {
            if (rollNo[i] == roll)
            {
                cout << "Enter new details for student " << roll << ":\n";
                cout << "Enter Student Name: ";
                getline(cin, name[i]);

                cout << "Enter Marks: ";
                cin >> marks[i];
                cin.ignore();
                cout << endl;
                return;
            }
        }
        cout << "Student with Roll Number " << roll << " not found.\n";
    }

    void writeToFile()
    {
        ofstream file(filename);
        if (!file)
        {
            cout << "Error in writing to file: " << filename << endl;
            return;
        }

        file << string(45, '-') << endl;
        file << "| " << left << setw(10) << "Roll No"
             << "| " << setw(20) << "Name"
             << "| " << setw(8) << "Marks" << "|\n";
        file << string(45, '-') << endl;

        for (int i = 0; i < numStudents; ++i)
        {
            file << "| " << left << setw(10) << rollNo[i]
                 << "| " << setw(20) << name[i]
                 << "| " << fixed << setprecision(2) << setw(8) << marks[i] << "|\n";
        }

        file << string(45, '-') << endl;
        file.close();

        cout << "Data written to file successfully.\n";
    }

    void readFromFile()
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "Error in opening file: " << filename << endl;
            return;
        }

        cout << "\nReading data from file: " << filename << "\n\n";
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }

    ~StudentData()
    {
        delete[] rollNo;
        delete[] name;
        delete[] marks;
    }
};

int main()
{
    string filename;
    int choice;

    cout << "Select the Operation:" << endl;
    cout << "1. Create a new file" << endl;
    cout << "2. Open an existing file" << endl;
    cin >> choice;
    cin.ignore();

    cout << "Enter filename: ";
    getline(cin, filename);
    // Append .txt only if not present
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt") {
        filename += ".txt";
    }

    StudentData *Robotics = nullptr;

    if (choice == 1)
    {
        cout << "Enter number of students: ";
        int n;
        cin >> n;
        cin.ignore();
        Robotics = new StudentData(n, filename);
        Robotics->createFile();
        Robotics->addData();
        Robotics->writeToFile();
    }
    else if (choice == 2)
    {
        Robotics = new StudentData(filename);
    }
    else
    {
        cout << "Invalid choice.\n";
        return 0;
    }

    int menuChoice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Modify Student\n";
        cout << "3. Display All Students\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> menuChoice;
        cin.ignore();

        switch (menuChoice)
        {
        case 1:
            Robotics->addData();
            Robotics->writeToFile();
            break;
        case 2:
            Robotics->readFromFile();
            Robotics->modifyStudent();
            Robotics->writeToFile();
            break;
        case 3:
            Robotics->readFromFile();
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (menuChoice != 4);

    delete Robotics;
    return 0;
}
