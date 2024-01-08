#include <stdio.h>

int main() {
    int a, revs = 0, rem;
    printf("Enter a 5 digit integer: ");
    scanf("%d", &a);
    int c = a;
    if (a > 99999 || a < 9999) {
        printf("Number is invalid. It is not a 5 digit number.");
    }
    while (a != 0) {
        rem = a%10;
        revs = revs * 10 + rem;
        a /= 10;
    }
    printf("Reversed number = %d\n", revs);
    if (c == revs) printf("The numbers are equal.");
    else printf("The numbers aren't equal.");
    return 0;
}