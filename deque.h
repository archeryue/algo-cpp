#ifndef __DEQUE_H__
#define __DEQUE_H__

namespace archer {

int tableInitSize = 5;
int nodeSize = 10;

template<typename T>
class Deque {
 private:
    class NodePtr; 
 public:
    Deque() {
        table = new(sizeof(T*) * tableInitSize);
        table[tableInitSize / 2] = new(sizeof(T) * nodeSize);
        head = NodePtr(tableInitSize / 2, 0);
        tail = NodePtr(tableInitSize / 2, 0);
        size = 0;
    }
    ~Deque() {
        for (int i = head.tableIndex; i <= tail.tableIndex; i++) {
            delete(table[i]);
        }
        delete(table);
    }

    T& At(int index) {
        int x = head.tableIndex;
        int y = 0;
        int preSize = nodeSize - 1 - head.nodeIndex;
        if (index <= preSize) {
            y = head.nodeIndex + index;
        } else {
            index -= preSize;
            x += index / nodeSize;
            y += (index % nodeSize) - 1;
            y = y < 0 ? (y + nodeSize) : y;
        }
        return table[x][y];
    }

    void Push_front(T e) {
       // todo 
    }

    void Pop_front(T e) {
       // todo 
    }

    void Push_back(T e) {
       // todo 
    }

    void Pop_back(T e) {
       // todo 
    }
 private:
    T*[] table;
    NodePtr head;
    NodePtr tail;
    int size;
}

template<typename T>
class Deque<T>::NodePtr {
 public:
    NodePtr(int x, int y) : tableIndex(x), nodeIndex(y) {}
    ~NodePtr() {}

    int tableIndex;
    int nodeIndex;

    T& value() {
        return table[tableIndex][nodeIndex];
    };
}

} // end namespace

#endif
