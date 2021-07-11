#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <iostream>

namespace archer {

template<typename T>
class Deque {
 private:
    class NodePtr; 
    const int tableInitSize = 0x04;
    const int nodeSize = 0x10;

 public:
    Deque() {
        tableSize = tableInitSize;
        table = new T*[tableSize];
        tableLeft = tableRight = (tableSize >> 1) - 1;
        table[tableLeft] = new T[nodeSize];
        head = NodePtr(tableLeft, 0);
        tail = NodePtr(tableLeft, 0);
        size = 0;
    }

    ~Deque() {
        for (int i = head.tableIndex; i <= tail.tableIndex; i++) {
            delete(table[i]);
        }
        delete(table);
    }

    int Size() {
        return size;
    }

    T& At(int index) {
        int x = head.tableIndex;
        int y = 0;
        int preSize = nodeSize - head.nodeIndex;
        if (index < preSize) {
            y = head.nodeIndex + index;
        } else {
            index -= preSize;
            x++;
            x += index >> 4;
            y += index & 0xF;
        }
        return table[x][y];
    }

    void resize(bool left) {
        tableSize = tableSize + tableInitSize;
        T** tmp = new T*[tableSize];            
        int shift = left ? tableInitSize : 0;
        for (int i = tableLeft; i <= tableRight; i++) {
            tmp[shift + i] = table[i];
        }
        if (left) {
            tableLeft += tableInitSize;
            tableRight += tableInitSize;
            head.tableIndex += tableInitSize;
            tail.tableIndex += tableInitSize;
        }
        delete [] table;
        table = tmp;
    }

    void checkLeft() {
        if (head.tableIndex - 1 < tableLeft) {
            if (tableLeft == 0) resize(true);
            table[--tableLeft] = new T[nodeSize];
        }
    }

    void checkRight() {
        if (tail.tableIndex + 1 > tableRight) {
            if (tableRight == tableSize - 1) resize(false);
            table[++tableRight] = new T[nodeSize];
        }
    }

    void Push_front(T e) {
        if (head.nodeIndex == 0) {
            checkLeft();
            head.tableIndex--;
            head.nodeIndex = nodeSize;
        }
        table[head.tableIndex][--head.nodeIndex] = e;
        size++;
    }

    void Pop_front() {
        if (size == 0) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        if (head.nodeIndex == nodeSize - 1) {
            head.tableIndex++;
            head.nodeIndex = -1;
        }
        head.nodeIndex++;
        size--;
    }

    void Push_back(T e) {
        if (tail.nodeIndex == nodeSize) {
            checkRight();
            tail.tableIndex++;
            tail.nodeIndex = 0;
        }
        table[tail.tableIndex][tail.nodeIndex++] = e;
        size++;
    }

    void Pop_back() {
        if (size == 0) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        if (tail.nodeIndex == 0) {
            tail.tableIndex--;
            tail.nodeIndex = nodeSize;
        }
        tail.nodeIndex--;
        size--;
    }

 private:
    NodePtr head;
    NodePtr tail;
    int size;
    int tableSize;
    int tableLeft;
    int tableRight;
    T** table;
};

template<typename T>
class Deque<T>::NodePtr {
 public:
    NodePtr() = default;
    NodePtr(int x, int y) : tableIndex(x), nodeIndex(y) {}
    ~NodePtr() {}

    int tableIndex;
    int nodeIndex;
};

} // end namespace

#endif
