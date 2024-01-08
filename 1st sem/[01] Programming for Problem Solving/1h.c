#include <stdio.h>

int main() {
    int a;
    printf("Enter the number: ");
    scanf("%d", &a);
    int ans = 0;
    ans += a%10 + 1;
    ans += (((a%100 - a%10)/10)+1)*10;
    ans += (((a%1000 - a%100)/100)+1)*100;
    printf("Answer: %d\n", ans);
    return 0;
}