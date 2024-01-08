#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

void swap(int *n, int *m) {
    int temp = *n;
    *n = *m;
    *m = temp;
}

int linearSearch(int *arr, int size, int item) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == item) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int *arr, int size, int item) {
    int l = 0;
    int r = size - 1;
    int mid;
    while (l <= r) {
        mid = (l + (r -1))/2;
        if (arr[mid] == item) {
            return mid;
        } else if (arr[mid] < item) {
            l = mid + 1;
        } else if (arr[mid] > item) {
            r = mid - 1;
        }
    }
    return -1;
}

int* insertionSort(int *arr, int size, int item) {
    int key, j;
    for (int i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            swap(&arr[j], &arr[j+1]);
            j--;
        }
        arr[j+1] = key;
    }
    return arr;
}

int* selectionSort(int *arr, int size, int item) {
    int minIdx;
    for (int i = 0; i < size; i++) {
        minIdx = i;
        for (int j = i; j < size; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(&arr[i], &arr[minIdx]);
    }
    return arr;
}

int* bubbleSort(int *arr, int size, int item) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
    return arr;
}

int* radixSort(int *arr, int size, int item) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    for (int exp = 1; max/exp > 0; exp *= 10) {
        int output[size];
        int count[10] = {0};
        for (int i = 0; i < size; i++) {
            count[(arr[i]/exp)%10]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i-1];
        }
        for (int i = size - 1; i >= 0; i--) {
            output[count[(arr[i]/exp)%10] - 1] = arr[i];
            count[(arr[i]/exp)%10]--;
        }
        for (int i = 0; i < size; i++) {
            arr[i] = output[i];
        }
    }
    return arr;
}

int* mergeSort(int *arr, int size, int item) {
    if (size == 1) {
        return arr;
    }
    int mid = size/2;
    int left[mid];
    int right[size - mid];
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }
    mergeSort(left, mid, item);
    mergeSort(right, size - mid, item);
    int i = 0, j = 0, k = 0;
    while (i < mid && j < size - mid) {
        if (left[i] < right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < mid) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < size - mid) {
        arr[k] = right[j];
        j++;
        k++;
    }
    return arr;
}

void heapify(int *arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
 
int* heapSort(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
    return arr;
}

void displayArray(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[size - 1] << endl;
}

int main() {
    int len, item;
    cout << "Enter the length of the data: ";
    cin >> len;
    int arr[len], choice;
    cout << "Dataset generated:\n";
    for (int i = 0; i < len; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }
    cout << endl;
    while (true) {
        cout << "Menu:\n";
        cout << "1. Linear Search\n";
        cout << "2. Binary Search\n";
        cout << "3. Insertion Sort\n";
        cout << "4. Selection Sort\n";
        cout << "5. Bubble Sort\n";
        cout << "6. Radix Sort\n";
        cout << "7. Merge Sort\n";
        cout << "8. Heap Sort\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        auto start = high_resolution_clock::now();
        switch (choice) {
            case 1:
                cout << "Enter the item to search: ";
                cin >> item;
                cout << "Item found at index " << linearSearch(arr, len, item) << endl;
                break;
            case 2:
                cout << "Enter the item to search: ";
                cin >> item;
                cout << "Item found at index " << binarySearch(arr, len, item) << endl;
                break;
            case 3:
                cout << "Sorted array: ";
                displayArray(insertionSort(arr, len, item), len);
                break;
            case 4:
                cout << "Sorted array: ";
                displayArray(selectionSort(arr, len, item), len);
                break;
            case 5:
                cout << "Sorted array: ";
                displayArray(bubbleSort(arr, len, item), len);
                break;
            case 6:
                cout << "Sorted array: ";
                displayArray(radixSort(arr, len, item), len);
                break;
            case 7:
                cout << "Sorted array: ";
                displayArray(mergeSort(arr, len, item), len);
                break;
            case 8:
                cout << "Sorted array: ";
                displayArray(heapSort(arr, len), len);
                break;
            case 9:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << duration.count() << " microseconds\n";
    }
    return 0;
}