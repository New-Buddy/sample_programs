#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class File
{

private:
    string filename;
    int linesCount;

public:
    File(const string &name) : filename(name), linesCount(0) {}

    void countLines()
    {
        linesCount = 0;
        ifstream file(filename);
        if (!file)
        {
            cout << "Error in opening file: " << filename << endl;
            return;
        }
        string line;
        while (getline(file, line))
            linesCount++;

        cout << "Number of lines in file '" << filename << "' is: " << linesCount << endl;
    }
};

int main()
{
    string fileName;

    cout << "Enter the file name to read: ";
    getline(cin, fileName);

    File Test(fileName);
    Test.countLines();

    return 0;
}