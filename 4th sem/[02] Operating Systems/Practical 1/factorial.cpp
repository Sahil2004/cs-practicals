// factorial.cpp
#include <iostream>
#include <thread>
#include "factorial.h"

using namespace std;

Factorial::Factorial() {
    facNo = 0;
}

void Factorial::setNumber(int n) {
    facNo = n;
}

int Factorial::getNumber() {
    return facNo;
}

void Factorial::calculate(int res, std::promise<int>& p) {
    int ans = 1;
    for (int i = res; i > 0; i--) {
        ans *= i;
    }
    p.set_value(ans);
}
