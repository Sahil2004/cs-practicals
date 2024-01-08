// Q - Write a program to calculate the factorial of a number using classes.
#include <iostream>

using namespace std;

class calculation {
    int number;
    int fact = 1;
public:
    void input(int no) {
        number = no;
    }
    int factorial() {
        for (int i = 1; i <= number; i++) {
            fact *= i;
        }
        return fact;
    }
};

int main() {
    int inpt;
    cout << "Enter the number: ";
    cin >> inpt;
    calculation c1;
    c1.input(inpt);
    int ans = c1.factorial();
    cout << "Factorial of " << inpt << " is " << ans;
    return 0;
}