#include <iostream>
using namespace std;

struct TreeNode {
    char value;
    TreeNode* leftChild;
    TreeNode* rightChild;

    TreeNode(char val) : value(val), leftChild(nullptr), rightChild(nullptr) {}
};

void traversePreOrder(TreeNode* root) {
    if (root != nullptr) {
        cout << root->value << " ";
        traversePreOrder(root->leftChild);
        traversePreOrder(root->rightChild);
    }
}

void traverseInOrder(TreeNode* root) {
    if (root != nullptr) {
        traverseInOrder(root->leftChild);
        cout << root->value << " ";
        traverseInOrder(root->rightChild);
    }
}

void traversePostOrder(TreeNode* root) {
    if (root != nullptr) {
        traversePostOrder(root->leftChild);
        traversePostOrder(root->rightChild);
        cout << root->value << " ";
    }
}

int evaluateExpressionTree(TreeNode* root, int z, int v, int u, int x, int y) {
    if (root != nullptr) {
        if (root->value >= 'a' && root->value <= 'z') {
            switch (root->value) {
                case 'z':
                    return z;
                case 'v':
                    return v;
                case 'u':
                    return u;
                case 'x':
                    return x;
                case 'y':
                    return y;
            }
        } else {
            int leftValue = evaluateExpressionTree(root->leftChild, z, v, u, x, y);
            int rightValue = evaluateExpressionTree(root->rightChild, z, v, u, x, y);
            switch (root->value) {
                case '+':
                    return leftValue + rightValue;
                case '-':
                    return leftValue - rightValue;
                case '*':
                    return leftValue * rightValue;
                case '/':
                    if (rightValue != 0)
                        return leftValue / rightValue;
                    else {
                        cout << "Error: Division by zero\n";
                        exit(1);
                    }
            }
        }
    }
    return 0;
}

void printMainMenu() {
    cout << "\n1. Pre-order traversal\n";
    cout << "2. In-order traversal\n";
    cout << "3. Post-order traversal\n";
    cout << "4. Evaluate expression tree\n";
    cout << "5. Exit\n";
    cout << "Select an option: ";
}

int main() {
    int z = 2, v = 3, u = 4, x = 5, y = 6;

    TreeNode* root = new TreeNode('-');
    root->leftChild = new TreeNode('z');
    root->rightChild = new TreeNode('+');
    root->rightChild->leftChild = new TreeNode('v');
    root->rightChild->rightChild = new TreeNode('*');
    root->rightChild->rightChild->leftChild = new TreeNode('/');
    root->rightChild->rightChild->rightChild = new TreeNode('y');
    root->rightChild->rightChild->leftChild->leftChild = new TreeNode('u');
    root->rightChild->rightChild->leftChild->rightChild = new TreeNode('x');

    int userOption;
    do {
        printMainMenu();
        cin >> userOption;

        switch (userOption) {
            case 1:
                cout << "Pre-order traversal: ";
                traversePreOrder(root);
                cout << "\n";
                break;
            case 2:
                cout << "In-order traversal: ";
                traverseInOrder(root);
                cout << "\n";
                break;
            case 3:
                cout << "Post-order traversal: ";
                traversePostOrder(root);
                cout << "\n";
                break;
            case 4:
                cout << "Result of the expression tree: " << evaluateExpressionTree(root, z, v, u, x, y) << endl;
                break;
            case 5:
                cout << "Exiting program\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (userOption != 5);

    delete root;
    return 0;
}
