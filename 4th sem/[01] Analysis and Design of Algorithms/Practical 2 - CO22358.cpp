#include <iostream>

using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitionAsc(int *arr, int first, int last) {
    int pivot = arr[(last + first) / 2];
    int i = (first - 1);
    for (int j = first; j <= last - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[last]);
    return (i + 1);
}

int partitionDsc(int *arr, int first, int last) {
    int pivot = arr[(last + first) / 2];
    int i = (first - 1);
    for (int j = first; j <= last - 1; j++) {
        if (arr[j] >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[last]);
    return (i + 1);
}

void quickSortAsc(int arr[], int first, int last) {
    if (first < last) {
        int pi = partitionAsc(arr, first, last);
        quickSortAsc(arr, first, pi - 1);
        quickSortAsc(arr, pi + 1, last);
    }
}

void quickSortDsc(int arr[], int first, int last) {
    if (first < last) {
        int pi = partitionDsc(arr, first, last);
        quickSortDsc(arr, pi + 1, last);
        quickSortDsc(arr, first, pi - 1);
    }
}

void display(int* arr, int size) {
    cout << "Array: ";
    for (int i = 0; i < size - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[size - 1];
    cout << endl;
}

int main() {
    int size, choice;
    cout << "Enter size of the array:  ";
    cin >> size;
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
    while (true) {
        cout << "Quick Sort\n";
        cout << "1. Ascending\n";
        cout << "2. Dscending\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                quickSortAsc(arr, 0, size - 1);
                break;
            case 2:
                quickSortDsc(arr, 0, size - 1);
                break;
            case 3:
                display(arr, size);
                break;
            case 4:
                exit(1);
            default:
                cout << "Invalid Choice";
                break;
        }
    }
    return 0;
}