#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next;
};

class linkedlist {
    Node *head;
public:
    linkedlist() {
        head = NULL;
    }
    void insert(int value) {
        Node *newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }
    void display() {
        Node *temp = head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    linkedlist li;
    li.insert(1);
    li.insert(2);
    li.insert(3);
    li.display();
    return 0;
}