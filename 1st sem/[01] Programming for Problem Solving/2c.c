#include <stdio.h>

int main() {
    int first, second, third;
    printf("Age of 1st person: ");
    scanf("%d", &first);
    printf("Age of second person: ");
    scanf("%d", &second);
    printf("Age of third person: ");
    scanf("%d", &third);
    if (first > second && first > third) {
        printf("First person is oldest.");
    } else if (second > first && second > third) {
        printf("Second person is oldest.");
    } else {
        printf("Third person is oldest.");
    }
    return 0;
}