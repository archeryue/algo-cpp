#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

volatile int cnt = 0;
static mutex cnt_mtx;

void RoundPrint(int max, int idx) {
    while (cnt < max) {
        cnt_mtx.lock();
        if (cnt < max && cnt % 2 == idx) {
            cout << cnt++ << endl;
        }
        cnt_mtx.unlock();
        this_thread::yield();
    }
}

int main() {
    thread t1{RoundPrint, 100, 0};
    thread t2{RoundPrint, 100, 1};
    t1.join();
    t2.join();
    return 0;
}
