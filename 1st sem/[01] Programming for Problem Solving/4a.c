#include <stdio.h>

// Q- Searching the first occurence of the element in an array.

int main() {
    printf("Enter the number of elements you want to enter into array: ");
    int n, inpt, i;
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++) {
        printf("Enter the element: ");
        scanf("%d", &inpt);
        arr[i] = inpt;
    }
    printf("Enter the integer you want to search for: ");
    scanf("%d", &inpt);
    for (i = 0; i < n; ++i) {
        if (arr[i] == inpt) {
            printf("Found the number at index: %d", i);
            break;
        }
    }
    if (i == n) {
        printf("The number doesn't exist in the array.");
    }
    return 0;
}