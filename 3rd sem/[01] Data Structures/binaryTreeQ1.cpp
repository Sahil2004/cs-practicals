#include <iostream>

#define MAX_SIZE 100

using namespace std;

struct Node {
    char info;
    Node *leftST;
    Node *rightST;
};

typedef Node ND;

ND* createNode(char info) {
    ND* newNode = (ND*)malloc(sizeof(ND));
    newNode->info = info;
    newNode->leftST = NULL;
    newNode->rightST = NULL;
    return newNode;
}

ND* constructTree(char* exp) {
    ND* root = createNode(exp[1]);
    ND* current = root;
    for (int i = 2; exp[i] != '\0'; i++) {
        if (exp[i] == '+' || exp[i] == '-') {
            current->leftST = createNode(exp[i]);
            current = current->leftST;
        } else if (exp[i] == '*' || exp[i] == '/') {
            current->rightST = createNode(exp[i]);
            current = current->rightST;
        } else {
            current->info = exp[i];
        }
    }
    return root;
}

void displayTree(ND *root, int level = 0) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        cout << "      ";
    }
    cout << root->info << endl;
    displayTree(root->leftST, level + 1);
    displayTree(root->rightST, level + 1);
}

int main() {
    char exp[MAX_SIZE];
    ND *root;
    int choice;
    while (true) {
        cout << "Menu:\n";
        cout << "1. Construct a tree\n";
        cout << "2. Display the tree\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter expression: ";
                cin.ignore();
                cin.getline(exp, MAX_SIZE);
                root = constructTree(exp);
                break;
            case 2:
                displayTree(root);
                break;
            case 3:
                return 0;
            default:
                cout << "You entered an invalid choice.\n";
                break;
        }
    }
    return 0;
}