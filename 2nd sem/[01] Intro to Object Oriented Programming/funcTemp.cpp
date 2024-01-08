#include <iostream>

using namespace std;

template <class T>
T add(T a, T b) {
    return (a+b);
}

int main() {
    cout << "Add two numbers.\n";
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;
    cout << "Result is: " << add<int>(a,b) << endl;
    float x, y;
    cout << "Enter two floats: ";
    cin >> x >> y;
    cout << "Result is: " << add<float>(x, y) << endl;
    return 0;
}