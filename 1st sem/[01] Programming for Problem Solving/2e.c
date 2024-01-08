#include <stdio.h>
#include <math.h>

int main() {
    int radius, centerx, centery, a, b;
    printf("Radius: ");
    scanf("%d", &radius);
    printf("Center (x, y): ");
    scanf("%d %d", &centerx, &centery); 
    printf("Enter a point: ");
    scanf("%d %d", &a, &b);
    int c = sqrt(pow((a-centerx), 2) + pow((b-centery), 2));
    if (c == radius) {
        printf("Point is on the circle.");
    } else if (c > radius) {
        printf("Point is outside the circle.");
    } else {
        printf("Point is inside the circle.");
    }
    return 0;
}