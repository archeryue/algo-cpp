#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        vector<int> maxV(4, INT_MIN);
        vector<int> minV(4, INT_MAX);
        for (int i = 0; i < arr1.size(); i++) {
            maxV[0] = max(maxV[0], arr1[i] + arr2[i] + i);
            maxV[1] = max(maxV[1], arr1[i] - arr2[i] + i);
            maxV[2] = max(maxV[2], arr1[i] + arr2[i] - i);
            maxV[3] = max(maxV[3], arr1[i] - arr2[i] - i);

            minV[0] = min(minV[0], arr1[i] + arr2[i] + i);
            minV[1] = min(minV[1], arr1[i] - arr2[i] + i);
            minV[2] = min(minV[2], arr1[i] + arr2[i] - i);
            minV[3] = min(minV[3], arr1[i] - arr2[i] - i);
        }
        int ret = INT_MIN;
        for (int i = 0; i < 4; i++) {
            maxV[i] -= minV[i];
            ret = max(ret, maxV[i]);
        }
        return ret;
    }
};

int main() {
    Solution s;
    vector<int> arr1 {1,-2,-5,0,10};
    vector<int> arr2 {0,-2,-1,-7,-4};
    cout << s.maxAbsValExpr(arr1, arr2) << endl;
    return 0;
}