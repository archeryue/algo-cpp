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
        que.Push_back(i);
    }
    print(que);
    for (int i = 0; i > -20; i--) {
        que.Push_front(i);
    }
    print(que);
    for (int i = 0; i < 10; i++) {
        que.Pop_front();
    }
    for (int i = 0; i < 20; i++) {
        que.Pop_back();
    }
    print(que);
    while (que.Size() > 0) {
        que.Pop_front();
    }
    print(que);
    return 0;
}
