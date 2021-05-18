#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int res = 0;
        for (int len = minSize; len <= maxSize; len++) {
            unordered_map<string, int> count;
            unordered_map<char, int> letter;
            int start = 0;
            string str = "";
            for (int end = 0; end < s.size(); end++) {
                letter[s[end]]++;
                str += s[end];

                if ((end - start + 1) > len) {
                    letter[s[start]]--;
                    if (letter[s[start]] == 0) letter.erase(s[start]);
                    start++;
                    str.erase(str.begin());
                }

                if ((end - start + 1) == len && letter.size() <= maxLetters) {
                    count[str]++;
                }
            }
            for (auto& [k, v] : count) {
                res = max(res, v);
            }
        } 
        return res;
    }
};

int main() {
    Solution s;
    cout << s.maxFreq("aababcaab", 2, 3, 4) << endl;
    return 0;
}