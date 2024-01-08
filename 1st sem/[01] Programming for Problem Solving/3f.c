#include <stdio.h>

// Q - Write down a program to find the range of a set of numbers.

int main() {
    int a, b, lowest, highest;
    printf("Enter the number of inputs you want to give: ");
    scanf("%d", &a);
    printf("Enter a number: ");
    scanf("%d", &b);
    highest = b;
    lowest = b;
    while (--a) {
        printf("Enter a number: ");
        scanf("%d", &b);
        if (b > highest) {
            highest = b;
        }
        if (b < lowest) {
            lowest = b;
        }
    }
    printf("Range is: %d", (highest - lowest));
    return 0;
}