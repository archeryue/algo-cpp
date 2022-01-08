#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int cmpKthDistance(vector<int>& nums, int k, int distance) {
        int start = 0;
        int count = 0;
        for (int end = 1; end < nums.size(); end++) {
            while (start < end && (nums[end] - nums[start]) > distance) {
                start++;
            } 
            count += (end - start);
            if (count >= k) {
                return 1;
            }
        }
        return 0;
    }

    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int right = nums.back() - nums.front();
        int left = 0;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int cmp = cmpKthDistance(nums, k, mid);
            if (cmp) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main() {
    Solution s;
    vector<int> nums {1, 6, 1};
    cout << s.smallestDistancePair(nums, 0) << endl;
    return 0;
}