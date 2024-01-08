#include <stdio.h>

int main() {
    int a;
    printf("Enter an integer: ");
    scanf("%d", &a);
    if (a%2 == 0) {
        printf("Integer is even.");
    } else {
        printf("Integer is odd.");
    }
    return 0;
}