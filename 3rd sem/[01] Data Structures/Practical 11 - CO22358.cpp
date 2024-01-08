#include <iostream>

using namespace std;

void heap(int *arr, int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if(right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if(largest != i) {
        swap(arr[i], arr[largest]);
        heap(arr, n, largest);
    }
}

void buildHeap(int *arr, int n) {
    for(int i = n/2 - 1; i >= 0; i--) {
        heap(arr, n, i);
    }
}

void printHeap(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        cout << i << ": ";
        cout << arr[i] << " ";
    }
}

int main() {
    cout << "Enter the length of data: ";
    int len;
    cin >> len;
    int arr[len];
    for (int i = 0; i < len; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << endl;
    buildHeap(arr, n);
    cout << endl;
    printHeap(arr, n);
}