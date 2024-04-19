#include <iostream>

using namespace std;

struct Process {
    int pid;
    int priority;
};
class Queue {
private:
    Process *queue;
    int front;
    int rear;
    int size;
    int capacity;
public:
    Queue() {
        front = rear = -1;
        size = 0;
        capacity = 10;
        queue = new Process[capacity];
    }
    void enqueue(Process p) {
        if (size == capacity) {
            cout << "Queue is full." << endl;
            return;
        }
        if (front == -1) {
            front = 0;
            rear = 0;
            queue[rear] = p;
            size++;
            return;
        }
        Process *bqueue = new Process[capacity];
        int k = 0;
        int i;
        for (i = size - 1; i >= 0; i--) {
            if (queue[i].priority > p.priority) {
                bqueue[k] = queue[i];
                k++;
            } else {
                break;
            }
        }
        queue[i + 1] = p;
        for (int j = 0; j < k; j++) {
            queue[i + j + 2] = bqueue[j];
        }
        rear = (rear + 1) % capacity;
        size++;
        delete[] bqueue;
    }

    Process dequeue() {
        if (size == 0) {
            cout << "Underflow." << endl;
            return {-1, -1};
        }
        Process p = queue[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        size--;
        return p;
    }
};

int main() {
    cout << "Enter the number of processes: ";
    int n;
    cin >> n;
    Queue q;
    for (int i = 0; i < n; i++) {
        Process p;
        cout << "Enter the process id: ";
        cin >> p.pid;
        cout << "Enter the priority: ";
        cin >> p.priority;
        q.enqueue(p);
    }
    for (int i = 0; i < n; i++)
    cout << q.dequeue().pid << endl;
    return 0;
}