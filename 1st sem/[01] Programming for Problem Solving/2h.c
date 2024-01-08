#include <stdio.h>

/*
Q - Write a program to find the greatest of the three numbers entered through the keyboard. Use conditional operators to make it.
*/

int main() {
    int a, b, c;
    printf("Enter the three numbers seprated by a space: ");
    scanf("%d %d %d", &a, &b, &c);
    a > b && a > c ? printf("First number is greatest.") : b > a && b > c ? printf("Second number is greatest.") : printf("Third number is greatest.");
    return 0;
}