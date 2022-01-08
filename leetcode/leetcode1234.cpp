#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool underControl(unordered_map<char, int>& charCount, int k) {
        return charCount['Q'] <= k && charCount['W'] <= k && charCount['E'] <= k && charCount['R'] <= k;
    }

    int balancedString(string s) {
        unordered_map<char, int> charCount;
        for (auto ch : s) {
            charCount[ch]++;
        }
        int k = s.length() / 4;
        if (underControl(charCount, k)) return 0;
        int ret = INT_MAX;
        for (int start = 0, end = 0; end < s.length(); end++) {
            charCount[s[end]]--;
            while (underControl(charCount, k) && start <= end) {
                ret = min(ret, end - start + 1);
                charCount[s[start++]]++;
            }
        }
        return ret;
    }
};

int main() {
    Solution s;
    cout << s.balancedString("QWERQQQR") << endl;
    return 0;
}