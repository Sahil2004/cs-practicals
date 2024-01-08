#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* leftST;
    Node* rightST;
};

typedef Node ND;

ND* createNode(int info) {
    ND* newNode = (ND*)malloc(sizeof(ND));
    newNode->data = info;
    newNode->leftST = NULL;
    newNode->rightST = NULL;
    return newNode;
}

int getMidIdx(int size, int* arr) {
    int mid = (size - 1)/2;
    if ((size-1) % 2 != 0) mid = size/2 - 1;
    if (arr[mid] % 2 != 0) {
        mid++;
    }
    return mid;
}

ND* constructTree(int *arr, int size) {
    if (size == 1) {
        ND* root = createNode(arr[0]);
        return root;
    }
    int mid = getMidIdx(size, arr);
    ND* root = createNode(arr[mid]);
    ND* current = root;
    int newlarr[mid];
    int newrarr[size - mid - 1];
    for (int i = 0; i < mid; i++) {
        newlarr[i] = arr[i];
    }
    int j = 0;
    for (int i = mid + 1; i <= size; i++) {
        newrarr[j++] = arr[i];
    }
    if (current->leftST == NULL)
    current->leftST = constructTree(newlarr, mid);
    if (current->rightST == NULL)
    current->rightST = constructTree(newrarr, size - mid - 1);
    if (current->leftST != NULL && current->rightST != NULL) {
        return root;
    }
    return root;
}

void preOrderTraversal(ND *root) {
    if (root == NULL) {
      return;
    }
    cout << root->data << " ";
    preOrderTraversal(root->leftST);
    preOrderTraversal(root->rightST);
}

void displayTree(ND *root, int level = 0) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        cout << "      ";
    }
    cout << root->data << endl;
    displayTree(root->leftST, level + 1);
    displayTree(root->rightST, level + 1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    ND* root = constructTree(arr, 11);
    displayTree(root);
    return 0;
}