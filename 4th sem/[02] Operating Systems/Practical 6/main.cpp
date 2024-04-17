#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>

using namespace std;

struct Record {
    int data;
};

class FileOpr {
    string fileName;
    fstream fileObj;
public:
    FileOpr(string fn) {
        fileName = fn;
    }
    void write(Record r) {
        fileObj.open(fileName, ios::out | ios::binary);
        fileObj.write((char *) &r, sizeof(Record));
        fileObj.close();
    }

    Record read() {
        fileObj.open(fileName, ios::in | ios::binary);
        Record r;
        fileObj.read((char *) &r, sizeof(Record));
        fileObj.close();
        return r;
    }
};

void processDef(int wait, int data, int pno, int *s) {
    FileOpr file("store.dat");
    Record r;
    sleep(wait);
    r = file.read();
    cout << "Data read by process " << pno << " : "<< r.data << endl;
    r.data = data;
    sleep(wait);
    while (*s == 1);
    *s = 1;
    file.write(r);
    *s = 0;
    cout << "Data written by process " << pno << " : "<< r.data << endl;
    return;
}

int main() {
    int s = 0; // semaphore, if s = 1, no writing
    thread t1(processDef, 2, 10, 1, &s);
    thread t2(processDef, 1, 20, 2, &s);
    thread t3(processDef, 1, 30, 3, &s);
    thread t4(processDef, 3, 40, 4, &s);
    thread t5(processDef, 2, 50, 5, &s);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0;
}