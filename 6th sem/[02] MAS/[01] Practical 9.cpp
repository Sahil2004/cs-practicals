#include <iostream>
#include <queue>
#include <random>

using namespace std;

struct Customer {
    int arrivalTime, serviceTime;
};

class SingleServerQueue {
private:
    queue<Customer> customerQueue;
    int totalWaitingTime, totalServiceTime, serverFreeTime;
    mt19937 rng;

public:
    SingleServerQueue(int totalCustomers = 5) : totalWaitingTime(0), totalServiceTime(0), serverFreeTime(0) {
        rng.seed(random_device()());  // Initialize rng inside the constructor
        generateCustomers(totalCustomers);
    }

    int getRandomTime(int min = 1, int max = 5) {
        return uniform_int_distribution<int>(min, max)(rng);
    }

    void generateCustomers(int totalCustomers) {
        int nextArrivalTime = getRandomTime();
        for (int i = 0; i < totalCustomers; i++) {
            Customer c = {nextArrivalTime, getRandomTime()};
            customerQueue.push(c);
            nextArrivalTime += getRandomTime();
        }
    }

    void processQueue() {
        cout << "Customer | Arrival | Service | Wait\n------------------------------------\n";
        int servedCustomers = 0;

        while (!customerQueue.empty()) {
            Customer c = customerQueue.front();
            customerQueue.pop();
            if (serverFreeTime < c.arrivalTime) serverFreeTime = c.arrivalTime;

            int waitTime = serverFreeTime - c.arrivalTime;
            totalWaitingTime += waitTime;
            totalServiceTime += c.serviceTime;
            serverFreeTime += c.serviceTime;

            cout << ++servedCustomers << "        | " << c.arrivalTime
                 << "       | " << c.serviceTime
                 << "      | " << waitTime << endl;
        }

        displayResults(servedCustomers);
    }

    void displayResults(int servedCustomers) {
        cout << "\nTotal Customers Served: " << servedCustomers << endl;
        if (servedCustomers > 0) {
            cout << "Average Waiting Time: " << (float)totalWaitingTime / servedCustomers << endl;
            cout << "Average Service Time: " << (float)totalServiceTime / servedCustomers << endl;
        }
    }
};

int main() {
    int totalCustomers;
    cout << "Enter the number of customers: ";
    cin >> totalCustomers;
    SingleServerQueue queueSimulation(totalCustomers);
    queueSimulation.processQueue();
    return 0;
}