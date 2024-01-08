#include <iostream>
#include <string>

using namespace std;

struct Node {
    char info;
    Node *LeftST;
    Node *RightST;
};

typedef Node ND;

ND* createNode(char info) {
    ND* newNode = (ND*)malloc(sizeof(struct Node));
    newNode->info = info;
    newNode->LeftST = NULL;
    newNode->RightST = NULL;
    return newNode;
}

ND* construct(string expression) {
    ND *root = createNode(expression[1]);
    ND *current = root;
    for (int i = 2; i < expression.length(); i++) {
        if (expression[i] == '+' || expression[i] == '-') {
            current->LeftST = createNode(expression[i]);
            current = current->LeftST;
        } else if (expression[i] == '*' || expression[i] == '/') {
            current->RightST = createNode(expression[i]);
            current = current->RightST;
        } else {
            current->info = expression[i];
        }
    }
    return root;
}

void printTree(ND *root) {
    if (root == NULL) return;
    cout << root->info << " ";
    printTree(root->LeftST);
    printTree(root->RightST);
}

void preOrderTraversal(ND *root) {
  if (root == NULL) {
    return;
  }
  cout << root->info << " ";
  preOrderTraversal(root->LeftST);
  preOrderTraversal(root->RightST);
}

int main() {
    int t;
    string expression = "E=A+B/C*D-F+L";
    ND *root = construct(expression);
    do {
        cout<<"1. Binary tree for expression E=A+B/C*D-F+L\n";
        cout<<"2. Pre order traversal\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>t;
        switch (t) {
            case 1:
                cout << "Binary tree: ";
                printTree(root);
                cout << endl;
                break;
            case 2:
                cout << "Binary tree before pre-order traversal: ";
                printTree(root);
                cout << endl;
                cout << "Binary tree after pre-order traversal: ";
                preOrderTraversal(root);
                cout << endl;
                break;
            case 3:
                return 0;
        }
    } while (t!=4);
    return 0;
}