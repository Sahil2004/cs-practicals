#include <iostream>
#include <fstream>

using namespace std;

struct Record {
    int value;
    long long factorial;
    bool isEven;
};

Record createRecord(int val) {
    Record r;
    r.value = val;
    r.factorial = 1;
    for (int i = val; i > 0; i--) {
        r.factorial *= i;
    }
    r.isEven = false;
    if (val % 2 == 0) {
        r.isEven = true;
    }
    return r;
}

class FileOpr {
    string storeName;
    fstream filePtr;
    int readPtr = 0;
public:
    FileOpr(string sn) {
        storeName = sn;
        filePtr.open(storeName, ios::out | ios::trunc);
        filePtr.close();
    }
    void write(int val) {
        filePtr.open(storeName, ios::app);
        filePtr << val << endl;
        filePtr.close();
    }
    Record read() {
        int val;
        filePtr.open(storeName, ios::in);
        if (readPtr != 0) {
            filePtr.seekg(readPtr);
        }
        filePtr >> val;
        readPtr = filePtr.tellg();
        filePtr.close();
        Record r = createRecord(val);
        return r;
    }
};

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Insufficient number of arguments." << endl;
        exit(1);
    }
    FileOpr fptr(argv[1]);
    for (int i = 2; i < argc; i++) {
        cout << "Writing " << strtol(argv[i], nullptr, 0) << " to file." << endl;
        fptr.write(strtol(argv[i], nullptr, 0));
    }
    cout << "Contents of file with their factorials: " << endl;
    for (int i = 2; i < argc; i++) {
        Record r = fptr.read();
        cout << r.value << ": " << r.factorial << ", is even = " << r.isEven << endl;
    }
    return 0;
}