#include <iostream>

using namespace std;

void display(int* arr, int size) {
    cout << "Array: ";
    for (int i = 0; i < size - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[size - 1];
    cout << endl;
}

int menu() {
    cout << "Menu:" << endl;
    cout << "1. Display" << endl;
    cout << "2. Selection Sort" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* selectionSort(int* arr, int size) {
    int min;
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        if (min != i) swap(&arr[min], &arr[i]);
    }
    return arr;
}

int main() {
    int size;
    cout << "Enter the size of dataset: ";
    cin >> size;
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
    while (true) {
        int choice = menu();
        switch (choice) {
            case 1:
                display(arr, size);
                break;
            case 2:
                arr = selectionSort(arr, size);
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }
    return 0;
}