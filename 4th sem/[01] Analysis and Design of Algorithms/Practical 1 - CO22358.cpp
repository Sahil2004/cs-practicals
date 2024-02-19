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

int* selectionSortMinAsc(int* arr, int size) {
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

int* selectionSortMinDesc(int* arr, int size) {
    int min;
    for (int i = size - 1; i > 1; i--) {
        min = i;
        for (int j = 0; j < i; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        if (min != i) swap(&arr[min], &arr[i]);
    }
    return arr;
}

int* selectionSortMaxAsc(int* arr, int size) {
    int max;
    for (int i = 0; i < size - 1; i++) {
        max = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[max] > arr[j]) {
                max = j;
            }
        }
        if (max != i) swap(&arr[max], &arr[i]);
    }
    return arr;
}

int* selectionSortMaxDesc(int* arr, int size) {
    int max;
    for (int i = size - 1; i > 1; i--) {
        max = i;
        for (int j = 0; j < i + 1; j++) {
            if (arr[max] < arr[j]) {
                max = j;
            }
        }
        if (max != i) swap(&arr[max], &arr[i]);
    }
    return arr;
}

int main() {
    int size, method;
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
                cout << "How do you want to run selection sort?" << endl;
                cout << "1. Minimum Increasing" << endl;
                cout << "2. Maximum Increasing" << endl;
                cout << "3. Minimum Decreasing" << endl;
                cout << "4. Maximum Decreasing" << endl;
                cout << "Enter your choice: ";
                cin >> method;
                switch (method) {
                    case 1:
                        arr = selectionSortMinAsc(arr, size);
                        break;
                    case 2:
                        arr = selectionSortMaxAsc(arr, size);
                        break;
                    case 3:
                        arr = selectionSortMinDesc(arr, size);
                        break;
                    case 4:
                        arr = selectionSortMaxDesc(arr, size);
                        break;
                }
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