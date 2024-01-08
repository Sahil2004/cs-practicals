#include <iostream>
#include <string>

using namespace std;

struct Date {
    int date;
    int month;
    int year;
};

struct Address {
    int houseNo;
    char street[100];
    char city[100];
    char state[100];
    char country[100];
    int pin;
};

struct Record {
    int aadhaar;
    char name[100];
    char fatherName[100];
    char motherName[100];
    char rank[100];
    char dept[100];
    struct Date doj;
    struct Address adr;
};

struct Node {
    struct Record info;
    Node *next;
};

typedef Node ND;

Date* getDateFromUser() {
    Date *d = (Date *)malloc(sizeof(Date));
    cout << "Date: ";
    cin >> d->date;
    while(true) {
        if (d->date >= 1 && d->date <= 31) {
            break;
        } else {
            cout << "Enter correct date: ";
            cin.ignore();
            cin >> d->date;
        }
    }
    cout << "Month: ";
    cin.ignore();
    cin >> d->month;
    while(true) {
        if (d->month >= 1 && d->month <= 12) {
            break;
        } else {
            cout << "Enter correct month: ";
            cin.ignore();
            cin >> d->month;
        }
    }
    cout << "Year: ";
    cin.ignore();
    cin >> d->year;
    while(true) {
        if (d->year >= 1920 && d->year <= 2023) {
            break;
        } else {
            cout << "Enter correct year: ";
            cin >> d->year;
        }
    }
    return d;
}

void getStringFromUser(char *str) {
    char ch;
    int k = 0;
    fflush(stdin);
    cin.ignore();
    while (ch != '\n') {
        ch = getchar();
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '.') {
            str[k] = ch;
            fflush(stdin);
            k++;
        }
    }
    str[k] = '\0';
}

Record* getDataFromUser() {
    Record *r = (Record *)malloc(sizeof(Record));
    cout << "Addhaar No: ";
    cin >> r->aadhaar;
    cout << "Name: ";
    getStringFromUser(r->name);
    cout << "Father Name: ";
    getStringFromUser(r->fatherName);
    cout << "Mother Name: ";
    getStringFromUser(r->motherName);
    cout << "Rank/position: ";
    getStringFromUser(r->rank);
    cout << "Department: ";
    getStringFromUser(r->dept);
    cout << "Date of joining:\n";
    r->doj = *getDateFromUser();
    cout << "Address:\n";
    cout << "House Number: ";
    cin >> r->adr.houseNo;
    cout << "Street: ";
    getStringFromUser(r->adr.street);
    cout << "City: ";
    getStringFromUser(r->adr.city);
    cout << "State: ";
    getStringFromUser(r->adr.state);
    cout << "Country: ";
    getStringFromUser(r->adr.country);
    cout << "Pin code: ";
    cin >> r->adr.pin;
    return r;
}

ND* create(ND *start) {
    if (start == NULL) {
        start = (ND *)malloc(sizeof(ND));
        if (start == NULL) {
            cout << "Memory overflow\n";
            return NULL;
        }
        start->info = *getDataFromUser();
        start->next = NULL;
        return start;
    } else {
        // List already exists
        ND* newNode = (ND *)malloc(sizeof(ND));
        if (newNode == NULL) {
            cout << "Memory overflow\n";
            return start;
        }
        newNode->info = *getDataFromUser();
        ND* ptr = start;
        while (ptr->next != NULL) {
            if (ptr->next->info.aadhaar < newNode->info.aadhaar) {
                ptr = ptr->next;
                continue;
            }
            break;
        }
        newNode->next = ptr->next;
        ptr->next = newNode;
        return start;
    }
}

void displayInfo(Record r) {
    cout << "Aadhaar Number: " << r.aadhaar << endl;
    cout << "Name: " << r.name << endl;
    cout << "Father Name: " << r.fatherName << endl;
    cout << "Mother Name: " << r.motherName << endl;
    cout << "Rank/position: " << r.rank << endl;
    cout << "Department: " << r.dept << endl;
    cout << "Address: #" << r.adr.houseNo << ", " << r.adr.street << ", " << r.adr.city << ", " << r.adr.state << ", " << r.adr.country << ", " << r.adr.pin << endl;
    cout << "Date Of Joining: " << r.doj.date << "/" << r.doj.month << "/" << r.doj.year << endl;
}

void display(ND *start) {
    if (start == NULL) {
        cout << "List is empty\n";
        return;
    }
    ND* ptr = start;
    while (ptr != NULL) {
        cout << "----------------\n";
        displayInfo(ptr->info);
        cout << "\n----------------\n";
        ptr = ptr->next;
    }
}

ND* search(ND* start) {
    ND* ptr = start;
    int aadhaar;
    cout << "Enter an aadhaar number to search: ";
    cin >> aadhaar;
    while (ptr != NULL) {
        if (ptr->info.aadhaar == aadhaar) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

ND* update(ND* start) {
    int query;
    ND* newNode = (ND *)malloc(sizeof(ND));
    if (newNode == NULL) {
        cout << "Memory overflow\n";
        return start;
    }
    newNode->info = *getDataFromUser();
    ND* ptr = start;
    ND* prev = start;
    if (start->next == NULL) {
        // single node list
        newNode->next = NULL;
        return newNode; // This will be our new starting point
    }
    while (ptr->next != NULL) {
        if (ptr->next->info.aadhaar != newNode->info.aadhaar) {
            prev = ptr;
            ptr = ptr->next;
            continue;
        }
        break;
    }
    newNode->next = ptr->next;
    delete ptr;
    prev->next = newNode;
    return start;
}

ND* deleteANode(ND* start) {
    if (start == NULL) {
        cout << "Empty list\n";
        return start;
    }
    if (start->next == NULL) {
        // single node list
        delete start;
        return NULL;
    }
    ND* ptr = start;
    int query;
    cout << "Enter the aadhaar number to delete: ";
    cin >> query;
    if (ptr->info.aadhaar == query) {
        // getting rid of the first item
        ND* temp = ptr->next;
        delete ptr;
        return temp;
    }
    while (ptr->next != NULL) {
        if (ptr->next->info.aadhaar == query) {
            ND* temp = ptr->next->next;
            delete ptr->next;
            ptr->next = temp;
            return start;
        }
        ptr = ptr->next;
    }
    return start;
}

int main() {
    ND *start = NULL;
    int choice;
    while (true) {
        cout << "Menu:\n";
        cout << "1. Add a node\n";
        cout << "2. Display all the nodes\n";
        cout << "3. Search for a node\n";
        cout << "4. Update a node\n";
        cout << "5. Delete a node\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                start = create(start);
                break;
            case 2:
                display(start);
                break;
            case 3:
                ND *node;
                node = search(start);
                if (node != NULL) {
                    cout << "----------------\n";
                    displayInfo(node->info);
                    cout << "\n----------------\n";
                    break;
                }
                cout << "No results were found.\n";
                break;
            case 4:
                start = update(start);
                break;
            case 5:
                start = deleteANode(start);
                break;
            case 6:
                return 0;
        }
    }
    return 0;
}