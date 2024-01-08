#include <stdio.h>

// Q - Write a program to get the matrices from the user and get the transpose of them and then display them.

int main() {
    // Getting the matrix
    int r, c, i, j;
    printf("Enter the number of rows you want for the matrix: ");
    scanf("%d", &r);
    printf("Enter the number of columns you want for the matrix: ");
    scanf("%d", &c);
    int A[r][c], O[c][r];
    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &A[i][j]); 
        }
    }
    // Getting the transpose of the matrix
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            O[j][i] = A[i][j];
        }
    }
    // Printing the matrix
    printf("Matrix after transpose is:\n");
    for (i = 0; i < c; i++) {
        for (j = 0; j < r; j++) {
            printf("%d\t", O[i][j]);
        }
        printf("\n");
    }
    return 0;
}