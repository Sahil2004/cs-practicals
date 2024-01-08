#include <stdio.h>

// Q - Convert the decimal number to binary number.

int main() {
    int i,n,a[10];
    printf("Enter the Decimal value: ");
    scanf("%d",&n);
    for(i=0;n!=0;i++) {
        a[i]=n%2;
        n=n/2;
    }
    n=i;
    printf("Binary Value: ");
    for(i=0;i<n;i++) {
        printf("%d",a[n-i-1]);
    }
    return 0;
}