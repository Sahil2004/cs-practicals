#include <stdio.h>

// Q - Write down a function that calculates the factorial of an integer entered through the keyboard.

int fact(int);

int main() {
    printf("Enter a number: ");
    int a;
    scanf("%d", &a);
    int ans = fact(a);
    printf("%d! = %d", a, ans);
    return 0;
}

int fact(int a) {
    int res = 1;
    do {
        res *= a;
    } while (--a);
    return res;
}