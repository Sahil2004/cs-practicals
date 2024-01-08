#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

#define ARRAY_SIZE 100

using namespace std;

// Data structures

struct Address {
    int houseNumber;
    string streetName;
    string city;
    string state;
    string country;
};

struct Record {
    int rollNumber;
    string studentName;
    string fatherName;
    string motherName;
    string classOfStudent;
    int semester;
    string branch;
    Address address;
};

/**
 * Displays the properties of a record
 * 
 * @param {Record} r - The record that has to be displayed
*/
void display(Record r) {
    cout << "Displaying the record:\n";
    cout << "Roll Number: " << r.rollNumber << endl;
    cout << "Student Name: " << r.studentName << endl;
    cout << "Father Name: " << r.fatherName << endl;
    cout << "Mother Name: " << r.motherName << endl;
    cout << "Class: " << r.classOfStudent << endl;
    cout << "Semester: " << r.semester << endl;
    cout << "Branch: " << r.branch << endl;
    cout << "House Number: " << r.address.houseNumber << endl;
    cout << "Street Name: " << r.address.streetName << endl;
    cout << "City: " << r.address.city << endl;
    cout << "State: " << r.address.state << endl;
    cout << "Country: " << r.address.country << endl;
}

/**
 * Get the data of a record from the user through console.
 * 
 * @return {Record} The record filled with the data user entered
*/
Record getDataFromUser() {
    Record r;
    cout << "Enter your details:\n";
    cout << "Roll number: ";
    cin >> r.rollNumber;
    cout << "Student Name: ";
    cin >> r.studentName;
    cout << "Father Name: ";
    cin >> r.fatherName;
    cout << "Mother Name: ";
    cin >> r.motherName;
    cout << "Class: ";
    cin >> r.classOfStudent;
    cout << "Semester: ";
    cin >> r.semester;
    cout << "Branch: ";
    cin >> r.branch;
    cout << "Now, enter your address:\n";
    cout << setw(5) << "House Number: ";
    cin >> r.address.houseNumber;
    cout << setw(5) << "Street Name: ";
    cin >> r.address.streetName;
    cout << setw(5) << "City: ";
    cin >> r.address.city;
    cout << setw(5) << "State: ";
    cin >> r.address.state;
    cout << setw(5) << "Country: ";
    cin >> r.address.country;

    return r;
}

template <typename T>
T* insertElemAtIndex(T* arr, T elem, int index) {
    // shifting every element forward by 1
    for (int i = ARRAY_SIZE - 2; i >= index; i--) {
        arr[i] = arr[i+1];
    }
    // setting the element at its index
    arr[index] = elem;
    return arr;
}

Record* input(Record* db) {
    Record data = getDataFromUser();
    int i;
    // checking if the database if full
    if (db[ARRAY_SIZE - 1].rollNumber != 0) {
        cout << "Unable to take input as database is full";
        return db;
    }
    // Checking if database is empty
    if (db[0].rollNumber == 0) {
        db[0] = data;
        return db;
    }
    // inserting the element in its sorted place
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (db[i].rollNumber > data.rollNumber) {
            return insertElemAtIndex<Record>(db, data, i);
        }
    }
    // If nothing worked above, entered record has highest roll number
    // Entering at the end
    return insertElemAtIndex<Record>(db, data, i+1);
}

Record* deleteElem(Record *db, int rollNo) {
    int i;
    for (i = 0; i < ARRAY_SIZE; i++) {
        if (db[i].rollNumber == rollNo) break;
    }
    for (int j = i; j < ARRAY_SIZE - 1; j++) {
        db[j] = db[j+1];
    }
    return db;
}

void search(Record *db, string query) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (db[i].address.city == query || db[i].address.state == query || db[i].address.country == query) {
            cout << "---------------------------------" << endl;
            display(db[i]);
            cout << "---------------------------------" << endl;
        }
    }
}

int main() {
    Record *db = (Record *) malloc(ARRAY_SIZE * sizeof(Record));
    int rollNo;
    int choice;
    string query;
    if (db == NULL) {
        cout << "There is not enough memory on the device.";
        exit(0);
    }
    while (true) {
        cout << "Enter your choice:\n";
        cout << "1. Add an element\n";
        cout << "2. Delete an element\n";
        cout << "3. Display all the elements\n";
        cout << "4. Search for an element\n";
        cout << "5. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                db = input(db);
                break;
            case 2:
                cout << "Enter the roll number whose data you want to delete: ";
                cin >> rollNo;
                db = deleteElem(db, rollNo);
                break;
            case 3:
                for (int i = 0; i < ARRAY_SIZE; i++) {
                    if (db[i].rollNumber != 0) {
                        cout << "---------------------------------" << endl;
                        display(db[i]);
                        cout << "---------------------------------" << endl;
                    }
                }
                break;
            case 4:
                cout << "Enter a city name, state name or a country name to search elements: ";
                cin >> query;
                search(db, query);
                break;
            case 5:
                return 0;
        }
    }
    return 0;
}