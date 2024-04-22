#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void process(int &data, mutex &mtx) {
    mtx.lock();
    cout << "Thread " << this_thread::get_id() << " read data: " << data << endl;
    data = rand() % 100;
    cout << "Thread " << this_thread::get_id() << " wrote data: " << data << endl;
    mtx.unlock();
}

int main() {
    mutex mtx;
    int data = 0;

    thread t1(process, ref(data), ref(mtx));
    thread t2(process, ref(data), ref(mtx));
    thread t3(process, ref(data), ref(mtx));
    thread t4(process, ref(data), ref(mtx));
    thread t5(process, ref(data), ref(mtx));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}