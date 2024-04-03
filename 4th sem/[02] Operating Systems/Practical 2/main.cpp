#include <iostream>
#include <thread>

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

    void inputWorker(int elem) {
        cout << "inputWorker running" << endl;
        if (lastFilledIdx < size) {
            arr[lastFilledIdx] = elem;
            lastFilledIdx++;
        } else {
            cout << "Array Overflow." << endl;
        }
    }
    void input(int elem) {
        thread thr(&ArraySite::inputWorker, std::ref(*this), elem);
        thr.join();
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
    void addWorker(int data) {
        cout << "addWorker running" << endl;
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
    void add(int data) {
        thread thr2(&LinkedListSite::addWorker, std::ref(*this), data);
        thr2.join();
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
    void enqueueWorker(int data) {
        cout << "enqueueWorker running" << endl;
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
    void enqueue(int data) {
        thread thr3(&QueueSite::enqueueWorker, std::ref(*this), data);
        thr3.join();
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
        if (elem < 200) arrSite.input(elem);
        if (elem < 1000 && elem >= 200) llSite.add(elem);
        if (elem >= 1000) qSite.enqueue(elem);
    }

    cout << "Array Site: ";
    arrSite.displaySite();
    cout << "Linked List Site: ";
    llSite.displaySite();
    cout << "Queue Site: ";
    qSite.displaySite();
    return 0;
}