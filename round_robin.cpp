#include <thread>

using namespace std;

volatile int cnt = 0;

void RoundPrint(const int max, const int idx) {
    while (cnt < max) {
        while (cnt % 2 != idx) this_thread::yield();
        if (cnt < max) {
            printf("t%d:%d\n", idx, cnt);
            cnt++;
        }
    }
}

int main() {
    thread t0{RoundPrint, 100, 0};
    thread t1{RoundPrint, 100, 1};
    t0.join();
    t1.join();
    return 0;
}
