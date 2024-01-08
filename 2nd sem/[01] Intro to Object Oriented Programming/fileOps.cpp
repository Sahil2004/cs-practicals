//reading write using class objects
#include <iostream>
#include <fstream>

using namespace std;

class FileClass {
    ofstream ofile;
    ifstream ifile;
public:
    FileClass() {
        ofile.open("classPrac.txt");
        ifile.open("classPrac.txt");
    }
    FileClass(string file) {
        ofile.open(file);
        ifile.open(file);
    }
    void input(string s) {
        ofile << s;
    }
    void output() {
        int n = 80;
        char str[n];
        while (ifile) {
            ifile.getline(str, n);
            cout << str << endl;
        }
    }
    void close() {
        ifile.close();
        ofile.close();
    }
};

int main() {
    FileClass f1("classPrac.txt");
    int n;
    cout << "Number of line: ";
    cin >> n;
    string l;
    for (int i = 0; i < n; i++) {
        cin >> l;
        f1.input(l);
    }
    cout << "Diplaying:\n";
    f1.output();
    f1.close();
    return 0;
}