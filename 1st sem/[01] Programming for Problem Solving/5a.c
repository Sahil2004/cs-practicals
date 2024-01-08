#include <stdio.h>

// Q - Write a function that recieves a float and an integer value from the main function. The function calculates the product of these two values which is returned to the main function.

float prod(int, float);

int main() {
    printf("Enter the two numbers whose product is to be calculated (integer float): ");
    int a;
    float b;
    scanf("%d %f", &a, &b);
    float c = prod(a, b);
    printf("%dx%.2f = %.2f", a, b, c);
    return 0;
}

float prod (int a, float b) {
    return a*b;
}