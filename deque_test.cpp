#include <iostream>
#include "deque.h"

using namespace std;

void print(archer::Deque<int>& que) {
    for (int i = 0; i < que.Size(); i++) {
        cout << que[i] << " ";
    }
    cout << endl;
}

int main() {
    archer::Deque<int> que;
    for (int i = 0; i < 60; i++) {
        que.PushBack(i);
    }
    print(que);
    for (int i = 0; i > -20; i--) {
        que.PushFront(i);
    }
    print(que);
    for (int i = 0; i < 10; i++) {
        que.PopFront();
    }
    for (int i = 0; i < 20; i++) {
        que.PopBack();
    }
    print(que);
    while (que.Size() > 0) {
        que.PopFront();
    }
    print(que);
    return 0;
}
