#include <stdio.h>

/*
Q - Write a program to print the following pattern:
    A
   B C
  D E F
 G H I J
K L M N O
*/

int main() {
    int k = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 5; j > i; j--) {
            printf(" ");
        }
        for (int j = 1; j <= i; j++) {
            printf("%c ", (char)(65+k));
            k++;
        }
        printf("\n");
    }
    return 0;
}