#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileHandler {
    
    string filename;

    public:
    FileHandler(const string& name) : filename(name) {}

    void createFile() {
        ofstream file(filename);
        if(!file) {
            cout << "Error in creating file: " <<filename << endl;
        } else {
            cout << "File created successfully: " << filename <<endl;
        }
    }

    void writeToFile(const string& content) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << content;
            cout << "Successfully wrote to file: " << filename << endl;
        } else {
            cout << "Error in writing to file: " << filename << endl;
        }
    }

    void readFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            cout << "Reading from file: " << filename<< endl;
            while (getline(file, line)) {
                cout << line << endl;
            }
        } else {
            cout << "Error in reading file: " << filename << endl;
        }
    }

    ~FileHandler() {}

};

int main() {
    FileHandler file("sample.txt");
    file.createFile();
    file.writeToFile("Hi Buddy!\n");
    file.readFromFile();
    return 0;
}
