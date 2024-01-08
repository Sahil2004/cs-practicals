#include <stdio.h>

// Q - Write a program to get the matrices from the user and add and display them.

int main() {
    // Getting the matrix
    int r, c, i, j, k;
    printf("Enter the number of rows you want for the matrix: ");
    scanf("%d", &r);
    printf("Enter the number of columns you want for the matrix: ");
    scanf("%d", &c);
    int A[r][c], B[r][c], O[r][c];
    for (i = 0; i < 2; i++) {
        printf("Enter the elements of the matrix:\n");
        for (j = 0; j < r; j++) {
            for (k = 0; k < c; k++) {
                if (i == 0) {
                    scanf("%d", &A[j][k]); 
                } else {
                    scanf("%d", &B[j][k]);
                }
            }
        }
    }
    // Adding the matrices
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            O[i][j] = A[i][j] + B[i][j];
        }
    }
    // Printing the matrix
    printf("Matrix after addition is:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%d\t", O[i][j]);
        }
        printf("\n");
    }
    return 0;
}