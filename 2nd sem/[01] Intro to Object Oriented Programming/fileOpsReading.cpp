#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream f1("practical.txt");
    int n = 80;
    char line[n];
    while (f1) {
        f1.getline(line, n);
        cout << line << endl;
    }
    f1.close();
    return 0;
}