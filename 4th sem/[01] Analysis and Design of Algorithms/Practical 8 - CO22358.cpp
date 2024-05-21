#include <iostream>
#include <cstring>

using namespace std;

void findLCS(char str1[], char str2[], int len1, int len2, int dp[][100], char dir[][100]) {
    for (int i = 0; i <= len1; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= len2; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                dir[i][j] = '|';
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                dir[i][j] = '^';
            } else {
                dp[i][j] = dp[i][j - 1];
                dir[i][j] = '<';
            }
        }
    }
}

void printLCS(char dir[][100], char str[], int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (dir[i][j] == '|') {
        printLCS(dir, str, i - 1, j - 1);
        cout << str[i - 1];
    } else if (dir[i][j] == '^') {
        printLCS(dir, str, i - 1, j);
    } else {
        printLCS(dir, str, i, j - 1);
    }
}

int main() {
    char str1[100], str2[100];
    cout << "Enter the first string: ";
    cin.getline(str1, 100);
    cout << "Enter the second string: ";
    cin.getline(str2, 100);

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int dp[100][100];
    char dir[100][100];

    findLCS(str1, str2, len1, len2, dp, dir);

    cout << "Length of LCS: " << dp[len1][len2] << endl;

    cout << "LCS: ";
    printLCS(dir, str1, len1, len2);
    cout << endl;

    return 0;
}
