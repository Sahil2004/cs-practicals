#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

void printBoard(const vector<int>& board) {
    int n = board.size();
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (board[row] == col) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void solveNQueens(vector<int>& board, int row, int& solutions) {
    int n = board.size();
    if (row == n) {
        solutions++;
        printBoard(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueens(board, row + 1, solutions);
        }
    }
}

int main() {
    for (int n = 17; n <= 17; ++n) {
        vector<int> board(n, -1);
        int solutions = 0;

        auto start = high_resolution_clock::now();
        solveNQueens(board, 0, solutions);
        auto end = high_resolution_clock::now();

        duration<double> duration = end - start;
        cout << "For N = " << n << ", found " << solutions << " solutions in "
             << duration.count() << " seconds.\n" << endl;
    }

    return 0;
}
