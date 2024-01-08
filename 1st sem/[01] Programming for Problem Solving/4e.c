#include <stdio.h>

// Q - Write a program to take elements as an input into an array and then sort it using Insertion sort algorithm.

int main() {
    // Getting the elements
    int n, i, j, temp;
    printf("Enter the number of elements you want to enter: ");
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++) {
        printf("Enter integer: ");
        scanf("%d", &arr[i]);
    }
    // Insertion sort
    for (i = 1; i < n; i++) {
        j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j--;
        }
    }
    // Printing array
    for (i = 0; i < n-1; i++)
        printf("%d, ", arr[i]);
    printf("%d", arr[n-1]);
    return 0;
}