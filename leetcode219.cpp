#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> wnd;
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) {
                wnd.erase(nums[i - k - 1]);
            }
            if (wnd.count(nums[i])) return true;
            wnd.insert(nums[i]);
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 0, 1, 1};
    cout << s.containsNearbyDuplicate(nums, 2) << endl;
    return 0;
}