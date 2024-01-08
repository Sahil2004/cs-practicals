#include <iostream>
#include <vector>

using namespace std;

template <class T>
class vectorFunc {
    vector<T> arr;
    vector<T> arr2;
    T elem;
public:
    vectorFunc(int n) {
        for (int i = 0; i < n; i++) {
            cin >> elem;
            arr.insert(arr.end(), elem);
        }
    }
    void reverse() {
        for (auto itr = arr.begin(); itr != arr.end(); itr++) {
            arr2.insert(arr2.begin(), *itr);
        }
    }
    void displayReversed() {
        for (auto itr = arr2.begin(); itr != arr2.end(); itr++) {
            cout << *itr;
        }
    }
};

int main() {
    int n;
    cout << "Enter element numbers: ";
    cin >> n;
    cout << "Enter elements...\n";
    vectorFunc<int> v1(n);
    v1.reverse();
    v1.displayReversed();
    return 0;
}