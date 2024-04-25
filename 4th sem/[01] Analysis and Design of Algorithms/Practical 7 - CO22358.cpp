#include <iostream>
#include <climits>
using namespace std;

void computeMatrixChainOrder(int dimensions[], int size, int minCostMatrix[][100], int splitMatrix[][100]) {
    for (int i = 1; i <= size; i++) {
        minCostMatrix[i][i] = 0;
    }

    for (int chainLength = 2; chainLength <= size; chainLength++) {
        for (int i = 1; i <= size - chainLength + 1; i++) {
            int j = i + chainLength - 1;
            minCostMatrix[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int cost = minCostMatrix[i][k] + minCostMatrix[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (cost < minCostMatrix[i][j]) {
                    minCostMatrix[i][j] = cost;
                    splitMatrix[i][j] = k;
                }
            }
        }
    }
}

void printOptimalParentheses(int splitMatrix[][100], int start, int end) {
    if (start == end) {
        cout << "A" << start;
    } else {
        cout << "(";
        printOptimalParentheses(splitMatrix, start, splitMatrix[start][end]);
        printOptimalParentheses(splitMatrix, splitMatrix[start][end] + 1, end);
        cout << ")";
    }
}

int main() {
    int numberOfMatrices;
    cout << "Enter the number of matrices: ";
    cin >> numberOfMatrices;
    
    int dimensions[numberOfMatrices + 1];
    cout << "Enter dimensions of matrices: ";
    for (int i = 0; i <= numberOfMatrices; i++) {
        cin >> dimensions[i];
    }

    int minCostMatrix[100][100];
    int splitMatrix[100][100];

    computeMatrixChainOrder(dimensions, numberOfMatrices, minCostMatrix, splitMatrix);

    cout << "Minimum number of scalar multiplications: " << minCostMatrix[1][numberOfMatrices] << endl;

    cout << "Optimal Parenthesization: ";
    printOptimalParentheses(splitMatrix, 1, numberOfMatrices);
    cout << endl;

    return 0;
}
