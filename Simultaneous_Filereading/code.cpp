#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileHandler {
    string inputFile;
    string outputFile;

    public:
    FileHandler(const string& input, const string& output) : inputFile(input), outputFile(output) {}

    void ReadAndWrite() {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);

        if(!inFile.is_open()) {
            cout << "Error in opening reading file: " << inputFile << endl;
            return;
        }
        if(!outFile.is_open()) {
            cout << "Error in opening writing file: " << outputFile << endl;
            return;
        }

        cout << "Copying contents...!" << endl;

        string line;
        while(getline(inFile, line)) {
            outFile << line << endl;
        }
        
        cout << "File copy completed successfully." << endl;

        inFile.close();
        outFile.close();
    }

    void readFile(const string& name) {
        ifstream file(name);

        if(!file) {
            cout << "Error in opening file: " << name << endl;
            return;
        }

        cout << "Reading file: " << name << endl;
        string line;
        while(getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

};

int main() {
    string read, write;
    cout << "Enter a file name to read: ";
    getline(cin, read);

    cout << "Enter a file name to write: ";
    getline(cin, write);

    FileHandler test(read, write);
    test.ReadAndWrite();
    test.readFile(write);

    return 0;
}

