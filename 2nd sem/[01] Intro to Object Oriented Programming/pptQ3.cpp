#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream F;
    F.open("my.txt", ios::in | ios::out);
    cout << F.tellg() << endl;
    F.seekg(8, ios::beg);
    cout << F.tellg() << endl;
    char c = F.get();
    cout << c << endl;
    cout << F.tellg() << endl;
    F.seekg(10, ios::cur);
    cout << F.tellg() << endl;
    c = F.get();
    cout << c << endl;
    cout << F.tellg() << endl;
    F.seekp(7, ios::beg);
    F.put('Z');
    F.seekg(-7, ios::end);
    cout << "End:" << F.tellg() << endl;
    c = F.get();
    cout << c << endl;
    F.close();
    return 0;
}

