#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node *prev;
};

class ArraySite {
    int *arr;
    int lastFilledIdx;
    int size;
public:
    ArraySite(int s) {
        size = s;
        arr = new int[size];
        lastFilledIdx = 0;
    }

    void input(int elem) {
        if (lastFilledIdx < size) {
            arr[lastFilledIdx] = elem;
            lastFilledIdx++;
        } else {
            cout << "Array Overflow." << endl;
        }
    }

    void displaySite() {
        for (int i = 0; i < lastFilledIdx; i++) {
            cout << arr[i] << ", ";
        }
        cout << endl;
    }
};

class LinkedListSite {
    Node *start;
    Node *curr;
public:
    LinkedListSite() {
        start = NULL;
    }
    void add(int data) {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = curr;
        if (start == NULL) {
            start = newNode;
            curr = start;
        } else {
            curr->next = newNode;
            curr = newNode;
        }
    }
    void displaySite() {
        Node *temp = start;
        while (temp != NULL) {
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class QueueSite {
    Node *front;
    Node *rear;
public:
    QueueSite() {
        front = NULL;
        rear = NULL;
    }
    void enqueue(int data) {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = NULL;
        if (front == NULL) {
            front = newNode;
            rear = front;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    void dequeue() {
        if (front == NULL) {
            cout << "Queue Underflow." << endl;
        } else {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
    }
    void displaySite() {
        Node *temp = front;
        while (temp != NULL) {
            cout << temp->data << ", ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    int size;
    cout << "Enter the number of items to store: ";
    cin >> size;
    ArraySite arrSite(size);
    LinkedListSite llSite;
    QueueSite qSite;

    for (int i = 0; i < size; i++) {
        int elem;
        cout << "Enter element " << i + 1 << ": ";
        cin >> elem;
        if (i < 200) arrSite.input(elem);
        if (i < 1000 && i >= 200) llSite.add(elem);
        if (i >= 1000) qSite.enqueue(elem);
    }

    cout << "Array Site: ";
    arrSite.displaySite();
    cout << "Linked List Site: ";
    llSite.displaySite();
    cout << "Queue Site: ";
    qSite.displaySite();
    return 0;
}