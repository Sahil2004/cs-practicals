#include <stdio.h>

/*
The distance between two cities in kilometers is input through the keyboard. Write a program to convert and print this distance in meters, feet, inches and centimeters.
*/

int main() {
    int dist;
    printf("Enter the distance between two cities (in kms): ");
    scanf("%d", &dist);
    int meters = dist*1000;
    float feet = 3280.84*dist;
    float inches = 39370.1*dist;
    int cm = meters*100;
    printf("The distance in meters is: %d m, in feet: %.2f feet, in inches: %.2f inches, in centimeters: %d cm.", meters, feet, inches, cm);
    return 0;
}