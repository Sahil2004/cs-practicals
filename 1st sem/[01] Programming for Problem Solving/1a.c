#include <stdio.h>

/*
Q - The length and breadth of a rectangle and radius of a circle are input through the keyboard. Write down a program to calculate area and perimeter of rectangle and the area and circumference of circle.
*/

int main() {
    int l, b;
    float r;
    printf("Enter the length of a rectangle: ");
    scanf("%d", &l);
    printf("Enter the breadth of the rectangle: ");
    scanf("%d", &b);
    printf("Enter the radius of the circle: ");
    scanf("%f", &r);
    int area = l*b;
    int perimeter = (l+b)*2;
    float cirArea = 3.14*(r*r);
    float circumference = 2.0*3.14*r;
    printf("Area of the rectangle is: %d sq. units, perimeter of rectangle is: %d units.\nArea of circle is: %.2f sq. units, circumference of circle is: %.2f units.", area, perimeter, cirArea, circumference);
    return 0;
}