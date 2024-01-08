#include <stdio.h>

// Q - A positive integer is entered through the keyboard. Write a function that recieved a positive integer from the main and calculates the prime factors of that integer.

void primeFact(int);

int main() {
    printf("Enter a number: ");
    int a;
    scanf("%d", &a);
    primeFact(a);
    return 0;
}

void primeFact(int a) {
    for(int i=2;a>1;i++) {
        while(a%i==0) {
            printf("%d\n",i);
            a=a/i;
        }
    }
    return;
}