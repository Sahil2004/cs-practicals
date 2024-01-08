// Q - Make a pyramid of stars using classes.
#include <iostream>

using namespace std;

class pattern {
    int levels;
    public:
        void input(int inpt) {
            levels = inpt;
        }
        void pyramid() {
            for (int i = 1; i <= levels; i++) {
                for (int j = levels; j > i; j--) {
                    cout << " ";
                }
                for (int j = 1; j <= i; j++) {
                    cout << "* ";
                }
                cout << endl;
            }
        }
};

int main() {
    pattern p1;
    int lvls;
    cout << "Enter the number of levels: ";
    cin >> lvls;
    p1.input(lvls);
    p1.pyramid();
    return 0;
}