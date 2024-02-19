#include <iostream>

using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp; 
}

int partitionAsc(int *arr, int first, int last) {
    int pivot = (last + first) / 2;
    cout << "first: " << first << " and last: " << last << endl;
    while (first <= last && first != pivot && last != pivot) {
        while (arr[first] < arr[pivot]) {
            cout << "arr[first]: " << arr[first] << " and arr[pivot]: " << arr[pivot] << endl;
            if (first < last) first++;
            else break;
        };
        while (arr[last] > arr[pivot]) {
            cout << "arr[last]: " << arr[last] << " and arr[pivot]: " << arr[pivot] << endl;
            if (first < last) last--;
            else break;
        };
        if (first <= last) {
            swap(arr[first], arr[last]);
            first++;
            last--;
        }
    }
    swap(arr[first], arr[pivot]);
    return first;
}

void quickSortAsc(int *arr, int left, int right) {
    if (left < right) {
        int pivot = partitionAsc(arr, left, right);
        quickSortAsc(arr, left, pivot - 1);
        quickSortAsc(arr, pivot + 1, right);
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
                // quickSortDsc(arr, 0, size - 1);
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