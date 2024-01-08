#include <iostream>

using namespace std;

class A {
public:
    void hello() {
        cout << "Hello world!\n";
    }
};

int main() {
    A *arr[10];
    for (int i = 0; i < 10; i++) {
        arr[i]->hello();
    }
    return 0;
}