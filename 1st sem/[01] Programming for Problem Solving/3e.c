#include <stdio.h>

// Q - Write a program to input the number till the user wants and to count the total number of input of positive number, negative numbers and the zeroes.

int main() {
    int pos = 0, neg = 0, zeros = 0, a, wanna;
    printf("Start entering the numbers: ");
    while (1) {
        scanf("%d", &a);
        if ( a > 0 ) pos++;
        else if (a == 0) zeros++;
        else neg++;
        printf("Do you want to enter more numbers (-1 (don't want to continue), 0): ");
        scanf("%d", &wanna);
        if (wanna == -1) {
            break;
        }
    }
    printf("Total positive numbers: %d, negative: %d, zeroes: %d", pos, neg, zeros);
}