#include <stdio.h>

int main() {
    int x1, y1, x2, y2, x3, y3;
    printf("(x1, y1): ");
    scanf("%d %d", &x1, &y1);
    printf("(x2, y2): ");
    scanf("%d %d", &x2, &y2);
    printf("(x3, y3): ");
    scanf("%d %d", &x3, &y3);
    int b = x1*y2 - x1*y3 - y1*x2 + y1*x3 + x2*y3 - x3*y2;
    if (b == 0) {
        printf("Three points are coincident.");
    } else {
        printf("Three points are not conincident.");
    }
    return 0;
}