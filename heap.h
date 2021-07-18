#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>
#include <functional>

namespace archer {

template<typename T>
class Heap {
public:
    Heap(std::function<bool(T, T)> cmp) : comparator(cmp) {
        data.push_back(0);
    }
    Heap() {
        comparator = [](T a, T b) {return a < b;};
        data.push_back(0);
    }
    ~Heap() {}
    void Push(T e);
    void Pop();
    const T& Peek();
private:
    inline void swap(T& a, T& b);
    std::vector<T> data;
    std::function<bool(T, T)> comparator;
};

template<typename T>
inline void Heap<T>::swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
void Heap<T>::Push(T e) {
    data.push_back(e);
    int i = data.size() - 1;
    while ((i > 1) && comparator(data[i], data[i/2])) {
        swap(data[i], data[i/2]);
        i /= 2;
    }
}

template<typename T>
void Heap<T>::Pop() {
    T last = data[data.size() - 1];
    data.pop_back();
    data[1] = last;
    int i = 1, j = 2 * i;
    while (i < j && j < data.size()) {
        if (j + 1 < data.size() && comparator(data[j + 1], data[j])) {
            j = j + 1;
        }
        if (comparator(data[j], data[i])) {
            swap(data[j], data[i]);
            i = j;
            j = 2 * i;
        } else {
            i = j;
        }
    }
}

template<typename T>
const T& Heap<T>::Peek() {
    // assert size > 1;
    return data[1];
}

} // end namespace
#endif
