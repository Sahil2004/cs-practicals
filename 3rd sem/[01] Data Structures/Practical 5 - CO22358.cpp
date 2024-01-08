#include <iostream>

using namespace std;

#define MAX_SIZE 100

struct Node {
    int info;
    Node *next;
};

typedef Node ND;

bool isEmpty(int TOS) {
    return TOS == -1;
}

bool isEmpty(ND* stack) {
    return stack == NULL;
}

bool isFull(int TOS) {
    return TOS == MAX_SIZE;
}

bool isFull() {
    ND* newNode = (ND*)malloc(sizeof(ND));
    if (newNode == NULL) {
        return false;
    } else {
        delete newNode;
        return true;
    }
}

void push(int* S, int* TOS, int item) {
    if (isFull(*TOS)) {
        cout << "Overflow.\n";
        return;
    }
    *TOS = *TOS + 1;
    S[*TOS] = item;
}

ND* push(ND* S, int item) {
    ND* newNode = (ND *)malloc(sizeof(ND));
    if (newNode == NULL) {
        cout << "Overflow\n";
        return S;
    }
    newNode->info = item;
    newNode->next = S;
    return newNode;
}

int pop(int* S, int *TOS) {
    if (isEmpty(*TOS)) {
        cout << "Underflow\n";
        return -1;
    }
    int item = S[*TOS];
    *TOS = *TOS - 1;
    return item;
}

ND* pop(ND* S, int * info = NULL) {
    if (isEmpty(S)) {
        cout << "Underflow\n";
        return S;
    }
    ND* temp = S;
    if (info != NULL) {
        *info = temp->info;
    }
    S = S->next;
    delete temp;
    return S;
}

int peep(int *S, int *TOS, int loc) {
    int backupStack[MAX_SIZE];
    int bTos = 0;
    int item;
    if (isEmpty(*TOS)) {
        cout << "Underflow\n";
        return -1;
    }
    if (loc < 0 || loc > MAX_SIZE) {
        cout << "Overflow\n";
        return -1;
    }
    // Pop the stack until location is found
    for (int i = *TOS; i > loc; i--) {
        item = pop(S, TOS);
        push(backupStack, &bTos, item);
    }
    // Pop the element at the location and store
    int elem = pop(S, TOS);
    // Reconstruct the stack
    push(S, TOS, elem);
    for (int i = 0; i < loc; i++) {
        item = pop(backupStack, &bTos);
        push(S, TOS, item);
    }
    return elem;
}

int peep(ND* stack, int loc) {
    if (isEmpty(stack)) {
        cout << "Underflow\n";
        return -1;
    }
    ND* backupStack = NULL;
    ND* bTOS = backupStack;
    int i = 0;
    int info;
    int elem;
    while (stack != NULL) {
        stack = pop(stack, &info);
        backupStack = push(backupStack, info);
        bTOS = backupStack;
        if (i == loc) {
            elem = info;
            break;
        }
        i++;
    }
    while (backupStack != NULL) {
        backupStack = pop(backupStack, &info);
        stack = push(stack, info);
        bTOS = backupStack;
    }
    return elem;
}

void update(int *S, int *TOS, int item) {
    int backupStack[MAX_SIZE];
    int bTos = -1;
    if (isEmpty(*TOS)) {
        cout << "Underflow\n";
        return;
    }
    // Pop the stack until element is found
    int i = *TOS;
    while (S[i] != item) {
        push(backupStack, &bTos, pop(S, TOS));
        i--;
    }
    // Get rid of the old element
    pop(S, TOS);
    // Take the new element
    int elem;
    cout << "Enter the new element: ";
    cin >> elem;
    // Reconstruct the stack
    push(S, TOS, elem);
    for (int i = bTos; i >= 0; i--) {
        push(S, TOS, pop(backupStack, &bTos));
    }
}

void update(ND *stack, int item) {
    if (isEmpty(stack)) {
        cout << "Underflow\n";
        return;
    }
    ND* backupStack = NULL;
    ND* bTOS = backupStack;
    int info;
    while (stack != NULL) {
        stack = pop(stack, &info);
        if (info == item) {
            break;
        }
        backupStack = push(backupStack, info);
        bTOS = backupStack;
    }
    cout << "Enter the new element: ";
    cin >> info;
    stack = push(stack, info);
    while (backupStack != NULL) {
        backupStack = pop(backupStack, &info);
        stack = push(stack, info);
        bTOS = backupStack;
    }
}

void display(int *S, int *TOS) {
    int backupStack[MAX_SIZE];
    int bTos = -1;
    int item;
    if (isEmpty(*TOS)) {
        cout << "Underflow\n";
        return;
    }
    // Pop the stack until location is found
    for (int i = *TOS; i >= 0; i--) {
        item = pop(S, TOS);
        push(backupStack, &bTos, item);
        cout << "Item: " << item << endl;
    }
    // Reconstruct the stack
    for (int i = bTos; i >= 0; i--) {
        push(S, TOS, pop(backupStack, &bTos));
    }
}

void display(ND* stack) {
    if (isEmpty(stack)) {
        cout << "Underflow\n";
        return;
    }
    ND* backupStack = NULL;
    ND* bTOS = backupStack;
    int info;
    while (stack != NULL) {
        stack = pop(stack, &info);
        backupStack = push(backupStack, info);
        cout << "Item: " << info << endl;
        bTOS = backupStack;
    }
    while (backupStack != NULL) {
        backupStack = pop(backupStack, &info);
        stack = push(stack, info);
        bTOS = backupStack;
    }
}

ND* create(ND* stack) {
    ND* newNode = (ND*)malloc(sizeof(ND));
    char choice = 'y';
    int info;
    while (choice == 'y' || choice == 'Y') {
        cout << "Enter the information to be stored in the node: ";
        cin >> info;
        stack = push(stack, info);
        cout << "Do you want to continue? (y/n) ";
        cin >> choice;
    }
    return stack;
}

int main() {
    int stack[MAX_SIZE];
    ND * lstack = NULL;
    ND * LTOS;
    int TOS = -1;
    int choice;
    char pchoice;
    int item, loc;
    int i = 1;
    cout << "Solve it using linked list or with array?(l/a) ";
    cin >> pchoice;
    while (true) {
        cout << "Menu:\n";
        if (pchoice == 'l') {
            cout << i << ". Create a stack\n";
            i++;
        }
        cout << i++ << ". Add a record\n";
        cout << i++ << ". Delete a record\n";
        cout << i++ << ". Update a record\n";
        cout << i++ << ". Display the records\n";
        cout << i++ << ". Peep a record\n";
        cout << i << ". Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                if (pchoice == 'a') {
                    cout << "Enter the item: ";
                    cin >> item;
                    push(stack, &TOS, item);
                } else if (pchoice == 'l') {
                    lstack = create(lstack);
                }
                break;
            case 2:
                if (pchoice == 'a') {
                    pop(stack, &TOS);
                } else {
                    cout << "Enter the item: ";
                    cin >> item;
                    lstack = push(lstack, item);
                }
                break;
            case 3:
                if (pchoice == 'a') {
                    cout << "Enter the item to be updated: ";
                    cin >> item;
                    update(stack, &TOS, item);
                } else {
                    lstack = pop(lstack);
                }
                break;
            case 4:
                if (pchoice == 'a') {
                    display(stack, &TOS);
                } else if (pchoice == 'l') {
                    cout << "Enter the item to be updated: ";
                    cin >> item;
                    update(lstack, item);
                }
                break;
            case 5:
                if (pchoice == 'a') {
                    cout << "Enter a location to peep at: ";
                    cin >> loc;
                    cout << "Element at location: " << peep(stack, &TOS, loc) << endl;
                    break;
                } else {
                    display(lstack);
                }
                break;
            case 6:
                if (pchoice == 'l') {
                    cout << "Enter a location to peep at: ";
                    cin >> loc;
                    cout << "Element at location: " << peep(lstack, loc) << endl;
                    break;
                } else {
                    return 0;
                }
            case 7:
                if (pchoice == 'l') {
                    return 0;
                }
                break;
            default:
                cout << "Invalid option chosen\n";
                break;
        }
        LTOS = lstack;
        i = 1;
    }
    return 0;
}