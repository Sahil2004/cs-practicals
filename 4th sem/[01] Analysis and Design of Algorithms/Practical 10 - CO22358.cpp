#include <iostream>
using namespace std;

void printSubset(int subset[], int size) {
    for (int i = 0; i < size; i++) {
        cout << subset[i] << " ";
    }
    cout << endl;
}

void sumOfSubsets(int set[], int subset[], int setSize, int subsetSize, int sum, int targetSum) {
    if (sum == targetSum) {
        printSubset(subset, subsetSize);
        return;
    }
    if (setSize == 0) {
        return;
    }
    subset[subsetSize] = set[setSize - 1];
    sumOfSubsets(set, subset, setSize - 1, subsetSize + 1, sum + set[setSize - 1], targetSum);
    sumOfSubsets(set, subset, setSize - 1, subsetSize, sum, targetSum);
}

int main() {
    int set[] = {10, 7, 5, 18, 12, 20, 15};
    int targetSum = 35;
    int setSize = sizeof(set) / sizeof(set[0]);
    int subset[setSize];

    cout << "Subsets of the given set that sum to " << targetSum << " are:" << endl;
    sumOfSubsets(set, subset, setSize, 0, 0, targetSum);

    return 0;
}
