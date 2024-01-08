#include <stdio.h>

int main() {
    int a, b, c, d, e;
    printf("Please enter the marks obtained seprated by a space: ");
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    int aggregate = (a+b+c+d+e);
    float perc = aggregate/5.0;
    printf("Aggregate: %d, percentage marks: %.2f%%\n", aggregate, perc);
    return 0;
}