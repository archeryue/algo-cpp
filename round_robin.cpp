#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

volatile int counter = 0;

static mutex cnt_mutex;

void RoundPrint(int max, int index) {
    while (counter < max) {
        cnt_mutex.lock();
        if (counter < max && counter % 2 == index) {
            cout << counter << endl;
            counter++;
        }
        cnt_mutex.unlock();
    }
}

int main() {
    thread t1{RoundPrint, 100, 0};
    thread t2{RoundPrint, 100, 1};
    t1.join();
    t2.join();
    return 0;
}
