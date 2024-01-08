#include <stdio.h>

// Q - Write down a function that calculates the factorial of an integer entered through the keyboard using recursion.

int fact(int);

int main() {
    printf("Enter a number: ");
    int a;
    scanf("%d", &a);
    int c = a*fact(a-1);
    printf("%d! = %d", a, c);
    return 0;
}

int fact(int a) {
    if (a == 1) {
        return 1;
    } else {
        int c = a*fact(a-1);
        return c;
    }
}