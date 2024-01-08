#include <stdio.h>

// Q - Interchange the even elements of array with the odd ones.

int main() {
    int n, i, j, inpt, temp;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++) {
        printf("Enter the element: ");
        scanf("%d", &inpt);
        arr[i] = inpt;
    }
    for (i = 0; i < n; i+=2) {
        temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
    }
    for (i = 0; i < n-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d", arr[n-1]);
    return 0;
}