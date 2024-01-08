#include <stdio.h>

/*
Q - Print the pattern:
        1
      1 2
    1 2 3
  1 2 3 4
1 2 3 4 5
*/

int main() {
    for (int i = 5, k = 1; i >= 1; --i, k++) {
        for (int j = 1; j < i; j++) {
            printf("  ");
        }
        for (int j = 1; j <= k; j++) {
            printf("%d ",j);
        }
        printf("\n");
    }
}