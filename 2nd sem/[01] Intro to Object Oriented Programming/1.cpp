// Q - Write down a program to print welcome on the screen using classes.
#include <iostream>

using namespace std;

class welcome {
    public:
        void display() {
            cout << "Welcome";
        }
};

int main() {
    welcome w1;
    w1.display();
    return 0;
}