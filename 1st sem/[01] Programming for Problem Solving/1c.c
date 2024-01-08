#include <stdio.h>

/*
Q - A five digit number is input through the keyboard. Write down a program to find the sum of digits of the given number.
*/

int main() {
    int a;
    printf("Enter a five digit number: ");
    scanf("%d", &a);
    if (!(a <= 99999 || a > 9999)) {
        printf("Number is invalid.");
    }
    int b = a%10;
    a /= 10;
    int c = a%10;
    a /= 10;
    int d = a%10;
    a /= 10;
    int e = a%10;
    a /= 10;
    int n = b + c + d + e + a; 
    printf("The sum of numbers is: %d", n);
    return 0;
}