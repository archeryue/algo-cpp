#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max = -2147483648;
        int sum = 0;
        for (auto num : nums) {
            sum += num;
            max = sum > max ? sum : max;
            sum = sum < 0 ? 0 : sum;
        }
        return max;
    }
};

int main() {
    vector<int> nums = {1, -2, 1, 3, 5, -7};
    Solution s;
    return s.maxSubArray(nums);
}