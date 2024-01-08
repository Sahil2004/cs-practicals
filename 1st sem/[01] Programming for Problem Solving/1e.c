#include <stdio.h>

int main() {
    int a, b;
    printf("Enter the two numbers with a space in between those: ");
    scanf("%d %d", &a, &b);
    int c = a;
    a = b;
    b = c;
    printf("Now, the first number is: %d, second number is: %d", a, b);
    return 0;
}