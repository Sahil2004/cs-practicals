#include <stdio.h>

/*
Q - Write a program to take elements as an input into an array and sort it using bubble sort algorithm.
*/

int main() {
    // Taking input
    int n, inpt, i, j, c;
    printf("Enter the number of elements you want to insert into the array: ");
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++) {
        printf("Enter the element: ");
        scanf("%d", &inpt);
        arr[i] = inpt;
    }
    // Bubble sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                c = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = c;
            }
        }
    } 
    // Printing array
    for (i = 0; i < n-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d", arr[n-1]);
    return 0;
}