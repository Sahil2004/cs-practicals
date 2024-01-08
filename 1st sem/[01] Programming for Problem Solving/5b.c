#include <stdio.h>

// Q - Write a function that recieves marks obtained by a student in 3 different subjects from the main function. And returns the total marks and percentage of marks to the main.

void marksCalc(float, float, float, float *perc, float *total);

int main() {
    printf("Enter the marks of student in 3 subjects: ");
    float a, b, c;
    scanf("%f %f %f", &a, &b, &c);
    float perc, total;
    marksCalc(a, b, c, &perc, &total);
    printf("Total marks: %.2f, percentage marks: %.2f%%", total, perc);
    return 0;
}

void marksCalc (float a, float b, float c, float *perc, float *total) {
    *total = a+b+c;
    *perc = *total/3;
}