#include <iostream>

using namespace std;

template <class T1, class T2>
class Assignment {
    T1 a;
    T2 b;
public:
    Assignment(T1 x, T2 y) {
        a = x;
        b = y;
    }
    void sum() {
        cout << "Result: " << a + b << "\n";
    }
};

int main() {
    cout << "using float and int:\n";
    Assignment<float, int> a1(2.2, 20);
    a1.sum();
    cout << "Using int and char:\n";
    Assignment<int, char> a2(100, 'W');
    a2.sum();
    return 0;
}