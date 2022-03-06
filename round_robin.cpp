#include <atomic>
#include <thread>

using namespace std;

atomic<int> cnt(0);

void RoundPrint(const int max, const int idx) {
    while (cnt.load() < max) {
        while (cnt.load() % 2 != idx) this_thread::yield();
        if (cnt.load() < max) {
            printf("t%d:%d\n", idx, cnt.load());
            cnt.fetch_add(1);
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
