#include <iostream>
#include <vector>

#include "bin_index_tree.h"

using namespace std;

int main() {
    BinaryIndexedTree binIndexTree({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    cout << binIndexTree.Sum(9) << endl;
    binIndexTree.Update(5, 100);
    cout << binIndexTree.Sum(10) << endl;
    cout << binIndexTree.Sum(4) << endl;
    cout << binIndexTree.Sum(4, 5) << endl;
    return 0;
}