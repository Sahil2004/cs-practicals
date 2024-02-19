#include <iostream>
#include <fstream>

using namespace std;

struct Record {
    int rollNo;
    int name;
};

class Write {
    ofstream fileObj;
    string fileName;
    int pointer = 0;
public:
    Write(string fn) {
        fileName = fn;
    }
    void writeToFile(Record r) {
        fileObj.open(fileName, ios::app);
        fileObj.seekp(pointer);
        fileObj.write((char *)&r, sizeof(r));
        pointer = fileObj.tellp();
        fileObj.close();
    }
};

class Read {
    ifstream fileObj;
    string fileName;
    int pointer;
public:
    Read(string fn) {
        fileName = fn;
    }
    Record readFromFile() {
        Record r;
        fileObj.open(fileName, ios::in);
        fileObj.seekg(pointer);
        fileObj.read((char*)&r, sizeof(r));
        pointer = fileObj.tellg();
        fileObj.close();
        return r;
    }
};

void display(Record r) {
    cout << "Roll number: " << r.rollNo << endl;
    cout << "Name: " << r.name << endl;
}

int main() {
    Write w("assignment.dat");
    Read r("assignment.dat");
    int totalRecords;
    cout << "Enter total records: ";
    cin >> totalRecords;
    Record *rec = new Record[totalRecords];
    Record read;
    for (int i = 0; i < totalRecords; i++) {
        cout << "Enter roll number: ";
        cin >> rec[i].rollNo;
        cout << "Enter name: ";
        cin >> rec[i].name;
        w.writeToFile(rec[i]);
        read = r.readFromFile();
        display(read);
    }
    return 0;
}