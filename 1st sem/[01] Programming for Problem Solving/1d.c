#include <stdio.h>

/*
A four digit number is input through the keyboard. Write down a program to find the sum of the first and fourth digits of the given number.
*/

int main() {
    int a;
    printf("Enter a four digit number: ");
    scanf("%d", &a);
    int b = a%10;
    a /= 1000;
    int sum = b + a%10;
    printf("The sum is: %d", sum);
    return 0;
}