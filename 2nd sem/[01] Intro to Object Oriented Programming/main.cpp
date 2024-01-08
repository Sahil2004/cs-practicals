#include <iostream>

using namespace std;

int main() {
    int **ptr_arry;
    ptr_arry = new int * [3];
    ptr_arry[0] = new int [3];
    ptr_arry[0][0] = 1;
    return 0;
}