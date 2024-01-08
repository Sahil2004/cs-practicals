#include <stdio.h>

// Q - A positive integer is entered through the keyboard. Write a function that recieved a positive integer from the main and calculates the prime factors of that integer using recursion.

int primeFact(int, int);

int main() {
    printf("Enter a number: ");
    int a;
    scanf("%d", &a);
    int ans = primeFact(a, 2);
    printf("%d", ans);
    return 0;
}

int primeFact(int a, int i) {
    if (a <= 1) {
        return 1;
    } else if (a % i == 0 && a>1) {
        int d = i;
        a /= i;
        int c = primeFact(a, i);
        printf("%dx", c);
        return d;
    } else {
        i++;
        int c = primeFact(a, i);
        return c;
    }
}