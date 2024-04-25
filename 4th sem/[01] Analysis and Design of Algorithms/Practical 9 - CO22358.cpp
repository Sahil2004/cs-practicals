#include <iostream>

using namespace std;

bool place(int board[], int qi, int n) {
    for (int i = 1; i < qi; i++) {
        if (board[i] == n || abs(board[i] - n) == abs(i - qi)) {
            return false;
        }
    }
    return true;
}

void nqueens(int board[], int qi, int n) {
    for (int i = 1; i <= n; i++) {
        if (place(board, qi, i)) {
            board[qi] = i;
            if (qi == n) {
                cout << "Result: ";
                for (int j = 1; j < n; j++) {
                    cout << board[j] << ", ";
                }
                cout << board[n] << endl;
            } else {
                nqueens(board, qi + 1, n);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;
    int board[n + 1];
    nqueens(board, 1, n);
    return 0;
}
