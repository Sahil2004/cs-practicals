#include <stdio.h>

/*
Q - Write a program to take elements as an input into an array and the sort it using Selection sort algorithm.
*/

int main() {
    // Taking input
    int n, inpt, i, j, min_idx, temp;
    printf("Enter the number of elements you want to insert into the array: ");
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++) {
        printf("Enter the element: ");
        scanf("%d", &inpt);
        arr[i] = inpt;
    }
    // Selection sort
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j< n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
    // Printing array
    for (i = 0; i < n-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d", arr[n-1]);
    return 0;
}