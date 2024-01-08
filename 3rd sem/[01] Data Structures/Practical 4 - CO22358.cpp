#include <iostream>
#include <string.h>

using namespace std;

struct DOB {
    int date;
    int month;
    int year;
};

struct Record {
    char ssn[9];
    char name[100];
    char gender;
    char pname[100];
    struct DOB cdob;
};

struct Node {
    struct Record info;
    Node *prev;
    Node *next;
};

typedef Node ND;

DOB* getDateFromUser() {
    DOB *d = (DOB *)malloc(sizeof(DOB));
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

Record* getDataFromUser() {
    Record *r = (Record *)malloc(sizeof(Record));
    cout << "Enter Social Security Number: ";
    cin >> r->ssn;
    cout << "Enter your name: ";
    cin.ignore();
    cin >> r->name;
    cout << "Enter your gender(m/f): ";
    cin >> r->gender;
    cout << "Enter your parent's name: ";
    cin >> r->pname;
    cout << "Enter your date of birth:\n";
    r->cdob = *getDateFromUser();
    return r;
}

ND* create(ND* start) {
    if (start == NULL) {
        // list is empty
        start = (ND *)malloc(sizeof(ND));
        if (start == NULL) {
            cout << "Memory Overflow\n";
            return NULL;
        }
        start->prev = NULL;
        start->next = NULL;
        start->info = *getDataFromUser();
        return start;
    }
    ND* newNode = (ND*)malloc(sizeof(ND));
    if (newNode == NULL) {
        cout << "Memory Overflow\n";
        return start;
    }
    newNode->info = *getDataFromUser();
    if (start->next == NULL) {
        // single node list
        if (strcmp(start->info.ssn, newNode->info.ssn) == 0) {
            cout << "Record with the social security number already exists.\n";
            delete newNode;
            return start;
        }
        if (strcmp(start->info.ssn, newNode->info.ssn) > 0) {
            newNode->next = start;
            start->prev = newNode;
            newNode->prev = NULL;
            return newNode;
        }
        start->next = newNode;
        newNode->prev = start;
        newNode->next = NULL;
        cout << start->next << endl;
        return start;
    }
    ND* ptr = start;
    while (ptr != NULL) {
        if (strcmp(ptr->info.ssn, newNode->info.ssn) == 0) {
            cout << "Record with the social security number already exists.\n";
            delete newNode;
            return start;
        }
        if (strcmp(ptr->info.ssn, newNode->info.ssn) > 0) {
            newNode->next = ptr;
            ptr->prev->next = newNode;
            newNode->prev = ptr->prev;
            ptr->prev = newNode;
            return start;
        }
        if (ptr->next == NULL) {
            // if the new entered node has the largest ssn
            ptr->next = newNode;
            newNode->prev = ptr;
            newNode->next = NULL;
            return start;
        }
        ptr = ptr->next;
    }
    return start;
}

void displayANode(Record r) {
    cout << "Social Security Number: " << r.ssn << endl;
    cout << "Name of the person: " << r.name << endl;
    cout << "Gender: " << r.gender << endl;
    cout << "Parents Name: " << r.pname << endl;
    cout << "Date of birth: " << r.cdob.date << "/" << r.cdob.month << "/" << r.cdob.year << endl;
}

void display(ND* start) {
    if (start == NULL) {
        cout << "List is empty\n";
        return;
    }
    if (start != NULL && start->next == NULL) {
        cout << "--------------------\n";
        displayANode(start->info);
        cout << "--------------------\n";
        return;
    }
    ND* ptr = start;
    while (ptr != NULL) {
        cout << "--------------------\n";
        displayANode(ptr->info);
        cout << "--------------------\n";
        ptr = ptr->next;
    }
}

ND* searchANode(ND* start) {
    if (start == NULL) {
        cout << "List is empty.\n";
        return NULL;
    }
    char ssn[9];
    cout << "Enter the ssn for which you want to search: ";
    cin >> ssn;
    ND* ptr = start;
    while (ptr != NULL) {
        if (strcmp(ptr->info.ssn, ssn) == 0) {
            return ptr;
        }
        ptr = ptr->next;
    }
    cout << "No results found.\n";
    return NULL;
}

void search(ND* start) {
    ND* node = searchANode(start);
    if (node != NULL) {
        cout << "--------------------\n";
        displayANode(node->info);
        cout << "--------------------\n";
    }
}

ND* deleteANode(ND* start) {
    if (start == NULL) {
        cout << "Underflow\n";
        return NULL;
    } else if (start->next == NULL) {
        // single node list
        delete start;
        return NULL;
    }
    ND* node = searchANode(start);
    if (node->prev == NULL) {
        // starting node
        node->next->prev = NULL;
        start = node->next;
        delete node;
        return start;
    }
    if (node->next == NULL) {
        // last node
        node->prev->next = node->next;
        delete node;
        return start;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    return start;
}

void update(ND* start) {
    if (start == NULL) {
        cout << "Underflow\n";
        return;
    }
    ND* node = searchANode(start);
    node->info = *getDataFromUser();
}

int main() {
    ND *start = NULL;
    int choice;
    while (true) {
        cout << "Menu:\n";
        cout << "1. Add a record\n";
        cout << "2. Display all the records\n";
        cout << "3. Search for a record\n";
        cout << "4. Update a record\n";
        cout << "5. Delete a record\n";
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
                search(start);
                break;
            case 4:
                update(start);
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