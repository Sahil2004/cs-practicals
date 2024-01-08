#include <iostream>

using namespace std;

int main() {
    int a, b;
    cout << "Enter value of a and b: ";
    cin >> a >> b;
    int x = a - b;
    try {
        if (x != 0)
            cout << "Result(a/x) = " << a/x << "\n";
        else
            throw(x);
    } catch(int i) {
        cout << "Exception caught: DIVIDE BY ZERO\n";
    }
    return 0;
}