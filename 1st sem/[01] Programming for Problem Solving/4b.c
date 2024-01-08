#include <stdio.h>

// Q- Find the number of occurences of an element in the array.

int main() {
    int n, inpt, i, occ = 0;
    printf("Enter the number of elements you want to enter into array: ");
    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++) {
        printf("Enter the number: ");
        scanf("%d", &inpt);
        arr[i] = inpt;
    }
    printf("Enter the element you want to search the occurrences for: ");
    scanf("%d", &inpt);
    for (i = 0; i < n; i++) {
        if (inpt == arr[i])
            occ++;
    }
    if (occ > 0)
        printf("The number of occurrences of %d is: %d", inpt, occ);
    else
        printf("No occurrences of the element found.");
    return 0;
}