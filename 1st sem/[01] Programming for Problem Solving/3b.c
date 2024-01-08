#include <stdio.h>

/*
Q - Write down a program to print the multiplication table of the number entered through the keyboard.
*/

int main() {
    int a;
    printf("Enter the number: ");
    scanf("%d", &a);
    for (int i = 1; i <= 10; i++) {
        printf("%d * %d = %d\n", a, i, (a*i));
    }
    return 0;
}