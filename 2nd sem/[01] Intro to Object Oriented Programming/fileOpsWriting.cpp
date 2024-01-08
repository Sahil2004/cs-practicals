#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream f1("practical.txt");
    string l;
    int n;
    cout << "number of lines: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l;
        f1 << l << "\n";
    }
    f1.close();
    return 0;
}