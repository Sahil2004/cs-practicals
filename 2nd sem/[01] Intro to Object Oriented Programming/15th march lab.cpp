#include <iostream>

using namespace std;

class mainClass {
    int firstNum;
    int secondNum;
    static int count;
public:
    void input(int a, int b);
    int sum();
    friend int mul(mainClass curr);
    int fact(int a);
    static void increment();
    static void showCount();
};

int mainClass::count;

void mainClass::input(int a, int b) {
    firstNum = a;
    secondNum = b;
}

inline int mainClass::sum() {
    return (firstNum + secondNum);
}

int mul(mainClass curr) {
    return (curr.firstNum * curr.secondNum);
}

inline int mainClass::fact(int a) {
    if (a > 1) {
        return (a*fact(a-1));
    } else {
        return 1;
    }
}

void mainClass::increment() {
    count++;
}

void mainClass::showCount() {
    cout << "Current count is: " << count << endl;
}

void redundant(mainClass obj) {
    int a, b;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    obj.input(a, b);
    mainClass::showCount();
    cout << "We will be incrementing counter after every calculation." << endl;
    cout << "Sum is: " << obj.sum() << endl; // Using inline function
    mainClass::increment();
    cout << "After multiplication: " << mul(obj) << endl; // Using friend function
    mainClass::increment();
    cout << "Using the first number for calculating factorial... " << endl;
    cout << "Factorial: " << obj.fact(a) << endl; // Using inline recursive function
    mainClass::increment();
    mainClass::showCount();
}

int main() {
    mainClass obj1, obj2;
    redundant(obj1);
    cout << "Now moving to second object..." << endl;
    redundant(obj2);
    return 0;
}