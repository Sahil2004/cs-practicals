#include <stdio.h>
#include <math.h>

/*
Q - The lengths of three sides of a triangle are entered through the keyboard. Write down a program to check whether the triangle is an isosceles triangle or right angle or equilateral.
*/

int main() {
    float a, b, c;
    printf("Enter the three sides of a triangle seprated by space: ");
    scanf("%f %f %f", &a, &b, &c);
    if (a == b && b == c) {
        printf("The triangle is an equilateral triangle.");
    } else if (a == b || b == c || a == c) {
        printf("The triangle is isosceles.");
    } else {
        if (
            pow(a, 2) + pow(b, 2) == pow(c, 2) ||
            pow(a, 2) + pow(c, 2) == pow(b, 2) ||
            pow(b, 2) + pow(c, 2) == pow(a, 2)
        ) printf("The triangle is a right angled triangle.");
        else printf("The triangle is a scalene triangle.");
    }
    return 0;
}