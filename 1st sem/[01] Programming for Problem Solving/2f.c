#include <stdio.h>

/*
Q - A character is entered through the keyboard. Write down a program to find, if the entered character is a capital letter or small case letter, a digit or a special symbol.
Ascii values:
For A-Z = [65,90];
For a-z = [97-132];
For digits = [48, 57];
For special values = [0-47] + [58-64] + [91-96] + [123-127];
*/

int main() {
    char a;
    printf("Enter a character: ");
    scanf("%c", &a);
    if (a >= 65 && a <= 90) printf("It is a capital letter.");
    else if (a >= 97 && a <= 132) printf("It is a small case letter.");
    else if (a >= 48 && a <= 57) printf("It is a digit.");
    else printf("It is a special character.");
    return 0;
}