#include <iostream>
#include <ostream>
#include "heap.h"

using namespace std;

int main() {
    archer::Heap<int> minHeap;
    for (int i = 10; i > 0; i--) {
        minHeap.Push(i);
    }
    cout << minHeap.Peek() << endl;
    minHeap.Pop(); minHeap.Pop();
    cout << minHeap.Peek() << endl;

    archer::Heap<int> maxHeap([](int a, int b) {return a > b;});
    for (int i = 0; i < 10; i++) {
        maxHeap.Push(i);
    }
    cout << maxHeap.Peek() << endl;
    for (int i = 0; i < 9; i++) {
        maxHeap.Pop();
    }
    cout << maxHeap.Peek() << endl;
    return 0;
}
