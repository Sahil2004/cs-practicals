#include <iostream>

using namespace std;

void merge(int arr[], int l, int m, int r, bool asc) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (asc) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
        } else {
            if (L[i] >= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r, bool asc) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, asc);
        mergeSort(arr, m + 1, r, asc);

        merge(arr, l, m, r, asc);
    }
}

void display(int arr[], int size) {
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int size, choice;
    cout << "Enter size of the array: ";
    cin >> size;
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
    while (true) {
        cout << "Merge Sort" << endl;
        cout << "1. Ascending" << endl;
        cout << "2. Descending" << endl;
        cout << "3. Display" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                mergeSort(arr, 0, size - 1, true);
                break;
            case 2:
                mergeSort(arr, 0, size - 1, false);
                break;
            case 3:
                display(arr, size);
                break;
            case 4:
                exit(1);
            default:
                cout << "Invalid Choice" << endl;
                break;
        }
    }
    return 0;
}
