#include <stdio.h>

// Two numbers are entered through the keyboard. Write a program to find the value of one number raised to the power another number.

int main() {
    long long a,b,c = 1, d;
    printf("Enter two numbers seprated by a space: ");
    scanf("%ld %ld", &a, &b);
    d = b;
    do {
        c *= a;
    } while (--d);
    printf("%ld power %ld = %ld", a, b, c);
    return 0;
}