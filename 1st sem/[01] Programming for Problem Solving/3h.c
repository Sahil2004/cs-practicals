#include <stdio.h>

/*
Q - Print the pattern:
1
1 2 3
1 2 3 4 5
1 2 3 4 5 6 7
*/

int main() {
    for (int i = 1; i <= 7; i+=2) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
    return 0;
}