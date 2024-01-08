#include <stdio.h>

// Q - A record contains name of the cricketer, age, no. of test matches played, average runs scored in each test match. Create an array of structure to hold record of 20 cricketers and then write a program to read these records and display the names of cricketers who have scored maximum average runs and minimum average runs.

int main() {
    struct cricketer {
        char name[10];
        int age;
        int tM;
        int avg;
    } b[20];

}