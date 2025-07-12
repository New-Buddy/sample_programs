#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string filename = "items.txt";

void addItem() {
    ofstream file(filename, ios::app);
    string id, name;
    double price;
    cout << "Enter ID Name Price: ";
    cin >> id >> name >> price;
    file << id << " " << name << " " << price << endl;
    file.close();
}

void modifyItem() {
    ifstream fileIn(filename);
    ofstream fileOut("temp.txt");

    string id, name, targetId;
    double price;
    bool found = false;

    cout << "Enter ID to modify: ";
    cin >> targetId;

    while (fileIn >> id >> name >> price) {
        if (id == targetId) {
            cout << "Enter new Name and Price: ";
            string newName;
            double newPrice;
            cin >> newName >> newPrice;
            fileOut << id << " " << newName << " " << newPrice << endl;
            found = true;
        } else {
            fileOut << id << " " << name << " " << price << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    // Replace original file with modified file
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (!found)
        cout << "Item not found.\n";
}

void displayItems() {
    ifstream file(filename);
    string id, name;
    double price;
    while (file >> id >> name >> price) {
        cout << "ID: " << id << ", Name: " << name << ", Price: " << price << endl;
    }
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n1. Add Item\n2. Modify Item\n3. Display Items\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addItem(); break;
            case 2: modifyItem(); break;
            case 3: displayItems(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
