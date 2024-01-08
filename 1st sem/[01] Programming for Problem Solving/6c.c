#include <stdio.h>

// Q - Write a program to get the matrices from the user and multiply them and display them.

int main() {
    // Getting the matrix
    int r, c, c2, i, j, k, sum;
    printf("Enter the number of rows you want for the 1st matrix: ");
    scanf("%d", &r);
    printf("Enter the number of columns you want for the 1st matrix: ");
    scanf("%d", &c);
    printf("Enter the number of columns of you want for the 2nd matrix: ");
    scanf("%d", &c2);
    int A[r][c], B[c][c2], O[r][c2];
    printf("Enter the elements of the 1st matrix:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &A[i][j]); 
        }
    }
    printf("Enter the elements of the 2nd matrix:\n");
    for (i = 0; i < c; i++) {
        for (j = 0; j < c2; j++) {
            scanf("%d", &B[i][j]); 
        }
    }

    // Multiplying the matrices
    for (i = 0; i < r; i++) {
        for (j = 0; j < c2; j++) {
            for (k = 0; k < c; k++) {
                sum += A[i][k]*B[k][j];
            }
            O[i][j] = sum;
            sum = 0;
        }
    }

    // Printing the matrix
    printf("Matrix after multiplication is:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c2; j++) {
            printf("%d\t", O[i][j]);
        }
        printf("\n");
    }
    return 0;
}