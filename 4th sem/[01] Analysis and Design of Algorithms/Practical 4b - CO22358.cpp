#include <iostream>
#include <climits>

using namespace std;

struct MinMax {
    int min;
    int max;
};

MinMax findMinMax(int arr[], int low, int high) {
    MinMax result, left, right;
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }
    int mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);
    if (left.min < right.min) {
        result.min = left.min;
    } else {
        result.min = right.min;
    }

    if (left.max > right.max) {
        result.max = left.max;
    } else {
        result.max = right.max;
    }

    return result;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    cout << "Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    MinMax result = findMinMax(arr, 0, n - 1);
    cout << "Minimum element: " << result.min << endl;
    cout << "Maximum element: " << result.max << endl;
    return 0;
}
