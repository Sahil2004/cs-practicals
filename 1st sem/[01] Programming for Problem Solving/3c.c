#include <stdio.h>

// Q - Write down a program to find out the factorial of given number.

int main() {
    int a;
    long long b = 1;
    printf("Enter a number: ");
    scanf("%d", &a);
    for (int i = a; i > 1; i--) {
        printf("%d x ", i);
        b *= i;
    }
    printf("1 = %ld", b);
    return 0;
}