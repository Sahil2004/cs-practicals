#include <stdio.h>

int main() {
    float men = (80000 * 52.00)/100.00;
    float literatePeople = (80000 * 48.00)/100.00;
    float literateMen = (men * 35.00)/100.00;
    float literateWomen = literatePeople - literateMen;
    int illitrateMen = (men  - literateMen);
    int illitrateWomen = (80000 - men) - literateWomen;
    printf("Illiterate Men: %d\nIlliterate Women: %d\n", illitrateMen, illitrateWomen);
    return 0;
}