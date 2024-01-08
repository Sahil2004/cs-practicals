#include <iostream>

// Objective: Using single, multilevel, multiple hierarchy and resolving ambiguity in multiple hierarchy.

using namespace std;

class Vehicle {
    int cost;
    int mntanCst;
public:
    Vehicle() {
        cost = 0;
        mntanCst = 0;
    }
    Vehicle(int c) {
        cost = c;
        mntanCst = c/100;
    }
    int getCost() {
        return cost;
    }
    int getMntanCst() {
        return mntanCst;
    }
};
  
class Fare {
    int petrolRate;
    int milage;
    int comission;
public:
    Fare() {
        petrolRate = 0;
        milage = 0;
        comission = 0;
    }
    Fare(int c) {
        petrolRate = 0;
        milage = 0;
        comission = c;
    }
    Fare(int p, int m) {
        petrolRate = p;
        milage = m;
        comission = 0;
    }
    Fare(int p, int m, int c) {
        petrolRate = p;
        milage = m;
        comission = c;
    }
    int getPetrolRate() {
        return petrolRate;
    }
    int getMilage() {
        return milage;
    }
    int getComission() {
        return comission;
    }
};
  
class Car : public Vehicle, public Fare {
    int cost;
public:
    void putCost() {
        cost = ((getPetrolRate()/getMilage())*5)*360 + Vehicle::getCost() + getMntanCst();
    }
    Car() {
        putCost();
    }
    Car(int p, int m, int c) : Vehicle(c), Fare(p, m) {
        putCost();
    }
    int getCost() {
        return cost;
    }
};
  
class Bus : public Vehicle, public Fare {
    int cost;
public:
    void putCost() {
        cost = Vehicle::getCost() + getMntanCst() + getComission()*2*360;
    }
    Bus() {
        putCost();
    }
    Bus(int c): Vehicle(), Fare(c) {
        putCost();
    }
    int getCost() {
        return cost;
    }
};

class Best: Bus, Car {
    char best;
    int cost;
public:
    void putBest() {
        best = (Bus::getCost() < Car::getCost()) ? 'B' : 'C';
    }
    void putCost() {
        cost = (Bus::getCost() < Car::getCost()) ? Bus::getCost() : Car::getCost();
    }
    Best() {
        putBest();
        putCost();
    }
    Best(int p, int m, int c, int cst) : Bus(c), Car(p, m, cst) {
        putBest();
        putCost();
    }
    string getBest() {
        if (best == 'B') {
            return "Bus";
        } else {
            return "Car";
        }
    }
    int getCost() {
        return cost;
    }
};

int main() {
    Best b1(100, 20, 5, 300000);
    cout << "Best vehical to go with is: " << b1.getBest() << "\n";
    cout << "Total cost: " << b1.getCost() << "\n";
    return 0;
}