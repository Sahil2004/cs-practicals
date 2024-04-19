#include <iostream>
#include <climits>

using namespace std;

// Without Divide and Conquer Design Strategy

struct MinMax {
    int min;
    int max;
};

MinMax findMinMax(int arr[], int n) {
    MinMax result;
    if (n == 1) {
        result.min = arr[0];
        result.max = arr[0];
        return result;
    }

    if (arr[0] < arr[1]) {
        result.min = arr[0];
        result.max = arr[1];
    } else {
        result.min = arr[1];
        result.max = arr[0];
    }

    for (int i = 2; i < n; i++) {
        if (arr[i] < result.min) {
            result.min = arr[i];
        } else if (arr[i] > result.max) {
            result.max = arr[i];
        }
    }

    return result;
}

int main() {
    int arr[] = {1000, 11, 445, 1, 330, 3000};
    int n = sizeof(arr) / sizeof(arr[0]);
    MinMax result = findMinMax(arr, n);
    cout << "Minimum element: " << result.min << endl;
    cout << "Maximum element: " << result.max << endl;
    return 0;
}
