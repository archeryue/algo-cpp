#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <iostream>

namespace archer {

template<typename T>
class Deque {
 private:
    class NodePtr; 
    static const int INIT_SIZE = 0x04;
    static const int NODE_POWER = 0x04;
    static const int NODE_SIZE = 1 << NODE_POWER;
    void resize(bool left);
    void checkLeft();
    void checkRight();

 public:
    Deque() {
        table_size = INIT_SIZE;
        table = new T*[table_size];
        table_left = table_right = (table_size >> 1) - 1;
        table[table_left] = new T[NODE_SIZE];
        head = NodePtr(table_left, 0);
        tail = NodePtr(table_left, 0);
        size = 0;
    }

    ~Deque() {
        for (int i = table_left; i <= table_right; i++) {
            delete [] table[i];
        }
        delete [] table;
    }

    int Size() {
        return size;
    }

    T& At(int index) {
        int x = head.table_index;
        int y = 0;
        int psize = NODE_SIZE - head.node_index;
        if (index < psize) {
            y = head.node_index + index;
        } else {
            index -= psize;
            x++;
            x += index >> NODE_POWER;
            y += index & (NODE_SIZE - 1);
        }
        return table[x][y];
    }

    T& operator[](int index) {
        return At(index);
    }

    void PushFront(T e) {
        if (head.node_index == 0) {
            checkLeft();
            head.table_index--;
            head.node_index = NODE_SIZE;
        }
        table[head.table_index][--head.node_index] = e;
        size++;
    }

    void PopFront() {
        if (size == 0) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        if (head.node_index == NODE_SIZE - 1) {
            head.table_index++;
            head.node_index = -1;
        }
        head.node_index++;
        size--;
    }

    void PushBack(T e) {
        if (tail.node_index == NODE_SIZE) {
            checkRight();
            tail.table_index++;
            tail.node_index = 0;
        }
        table[tail.table_index][tail.node_index++] = e;
        size++;
    }

    void PopBack() {
        if (size == 0) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        if (tail.node_index == 0) {
            tail.table_index--;
            tail.node_index = NODE_SIZE;
        }
        tail.node_index--;
        size--;
    }

 private:
    NodePtr head;
    NodePtr tail;
    int size;
    int table_size;
    int table_left;
    int table_right;
    T** table;
};

template<typename T>
class Deque<T>::NodePtr {
 public:
    NodePtr() = default;
    NodePtr(int x, int y) : table_index(x), node_index(y) {}
    ~NodePtr() {}

    int table_index;
    int node_index;
};

template<typename T>
void Deque<T>::resize(bool left) {
    table_size = table_size + INIT_SIZE;
    T** tmp = new T*[table_size];            
    int shift = left ? INIT_SIZE : 0;
    for (int i = table_left; i <= table_right; i++) {
        tmp[shift + i] = table[i];
    }
    if (left) {
        table_left += INIT_SIZE;
        table_right += INIT_SIZE;
        head.table_index += INIT_SIZE;
        tail.table_index += INIT_SIZE;
    }
    delete [] table;
    table = tmp;
}

template<typename T>
void Deque<T>::checkLeft() {
    if (head.table_index - 1 < table_left) {
        if (table_left == 0) resize(true);
        table[--table_left] = new T[NODE_SIZE];
    }
}

template<typename T>
void Deque<T>::checkRight() {
    if (tail.table_index + 1 > table_right) {
        if (table_right == table_size - 1) resize(false);
        table[++table_right] = new T[NODE_SIZE];
    }
}

} // end namespace

#endif
