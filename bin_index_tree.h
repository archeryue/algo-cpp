#ifndef BIN_INDEX_TREE
#define BIN_INDEX_TREE

#include <vector>

using namespace std;

int lowbit(int index) {
    return index & (-index);
}

class BinaryIndexedTree {
   public:
    BinaryIndexedTree(const vector<int>& orginal) : array(orginal.size() + 1) {
        for (int i = 1; i < array.size(); i++) {
            for (int j = i; j > i - lowbit(i); j--) {
                array[i] += orginal[j - 1];
            }
        }
    }

    void Update(int index, int delta) {
        index++; // start from 1
        while (index < array.size()) {
            array[index] += delta;
            index += lowbit(index);
        }
    }

    int Sum(int index) {
        index++; // start from 1
        int sum = 0;
        while (index > 0) {
            sum += array[index];
            index -= lowbit(index);
        }
        return sum;
    }

    int Sum(int start, int end) {
        return Sum(end) - Sum(start);
    }

   private:
    vector<int> array;
};

#endif