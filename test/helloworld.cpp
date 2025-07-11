#include <iostream>
using namespace std;

class Helloworld {
public:
    Helloworld() {
        print();
    }

    static void print() {
        cout << "Hi Buddy!" ;
    }

    ~Helloworld () {}

};

int main() {
    Helloworld msg;
    return 0;
}