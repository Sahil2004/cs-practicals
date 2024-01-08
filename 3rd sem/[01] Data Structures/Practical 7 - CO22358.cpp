#include <iostream>

#define MAX_SIZE 5

using namespace std;

struct Node {
    int info;
    Node *next;
    Node *prev;
};

struct HNode {
    int count = 0;
    Node *front;
    Node *rear;
};

bool isEmpty(HNode* header) {
    return header->count == 0;
}

bool isFull(HNode* header) {
    return header->count == MAX_SIZE;
}

void insert(HNode* header, int item) {
    if (isFull(header)) {
        cout << "Overflow" << endl;
        return;
    }
    Node* newNode = new Node;
    newNode->info = item;
    newNode->next = nullptr;
    newNode->prev = header->rear;

    if (header->rear) {
        header->rear->next = newNode;
    } else {
        header->front = newNode;
    }

    header->rear = newNode;
    header->count++;
}

void delete_item(HNode* header) {
    if (isEmpty(header)) {
        cout << "Underflow" << endl;
        return;
    }
    Node* temp = header->front;
    header->front = temp->next;
    if (header->front) {
        header->front->prev = nullptr;
    } else {
        header->rear = nullptr;
    }
    delete temp;
    header->count--;
}

Node* search(HNode* header, int query) {
    Node* current = header->front;
    while (current != nullptr) {
        if (current->info == query) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool update(HNode* header, int old_value, int new_value) {
    Node* nodeToUpdate = search(header, old_value);
    if (nodeToUpdate) {
        nodeToUpdate->info = new_value;
        return true;
    }
    return false;
}

void displayQueue(HNode* header) {
    Node* current = header->front;
    
    if (isEmpty(header)) {
        cout << "Queue is empty." << endl;
        return;
    }

    cout << "Queue contents:" << endl;
    while (current != nullptr) {
        cout << current->info << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    HNode header;
    header.front = nullptr;
    header.rear = nullptr;
    Node* foundnode;
    int old_value, new_value;
    int choice;
    while (true) {
        cout << "1. Insert\n2. Delete\n3. Search\n4. Update\n5. Display\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                int item;
                cout << "Enter item to insert: ";
                cin >> item;
                insert(&header, item);
                break;
            case 2:
                delete_item(&header);
                break;
            case 3: 
                int query;
                cout << "Enter the value to search : ";
                cin >> query;
                foundnode = search(&header, query);
                if (foundnode) {
                    cout << "node found with value : " << foundnode -> info <<endl;
                }
                else {
                    cout <<"node not found." <<endl;
                }
                break;
            case 4:
                cout << "Enter the value to update : ";
                cin >> old_value;
                cout << "Enter the new value : ";
                cin >> new_value;
                if (update(&header, old_value, new_value)) {
                    cout << "Node updated successfully." << endl;
                } else {
                    cout << "Node not found or not updated." << endl;
                }
                break;
            case 5:
                displayQueue(&header);
                break;
            default:
                cout <<"Invalid Choice.";
        }
    }

    return 0;
}