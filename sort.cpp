#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void msort(vector<int>& arr, int left, int right) {
    if (left == right - 1) return; 

    int mid = left + ((right - left) >> 1);
    msort(arr, left, mid);
    msort(arr, mid, right);

    int i = left, j = mid;
    vector<int> tmp;
    while (i < mid && j < right) {
        if (arr[i] < arr[j]) {
            tmp.push_back(arr[i++]);
        } else {
            tmp.push_back(arr[j++]);
        }
    }

    while (i < mid) tmp.push_back(arr[i++]);
    while (j < right) tmp.push_back(arr[j++]);

    copy(tmp.begin(), tmp.end(), arr.begin() + left);
}

void MergeSort(vector<int>& arr) {
    msort(arr, 0, arr.size());   
}

int main() {
    vector<int> arr {5, 3, 2, 7, 9, 11, 1, 56, 99, 0, 8};
    MergeSort(arr);
    for_each(arr.begin(), arr.end(), [](const int& e) {cout << e << " ";});
    cout << endl;
    return 0;
}
