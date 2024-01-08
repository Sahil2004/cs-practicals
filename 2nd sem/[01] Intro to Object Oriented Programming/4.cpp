// Q - To find the element in the array using classes.
#include <iostream>

using namespace std;

class searching {
    int n;
    int inpt;
    int arr;
    public:
        void input(int number) {
            n = number;
            arr = (int)malloc(n*sizeof(int));
        }
        void arrayPopulate() {
            for (int i = 0; i < n; i++) {
                cin >> inpt;
                *(&arr + i) = inpt;
            }
        }
        int find(int elem) {
            for (int i = 0; i < n; i++) {
                if (*(&arr + i) == elem) {
                    return i;
                }
            }
            return -1;
        }
};

int main() {
    searching s1;
    int inpt;
    cout << "Enter the size of array: ";
    cin >> inpt;
    s1.input(inpt);
    cout << "Enter the elements of array: ";
    s1.arrayPopulate();
    cout << "Enter the number you want to search: ";
    cin >> inpt;
    int inpt = s1.find(inpt);
    if (inpt == -1) {
        cout << "Element not found.";
    } else {
        cout << "Element found at index " << inpt;
    }
    return 0;
}