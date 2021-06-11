#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <numeric>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (auto triple : times) {
            graph[triple[0]].push_back(make_pair(triple[2], triple[1]));
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> unsettle;
        vector<bool> settled(n + 1, false);
        int ret = INT_MIN;
        unsettle.push(make_pair(0, k));
        while(!unsettle.empty()) {
            auto settling = unsettle.top(); unsettle.pop();
            if (settled[settling.second]) continue;
            ret = max(ret, settling.first);
            for (auto reach : graph[settling.second]) {
                if (settled[reach.second]) continue;
                unsettle.push(make_pair(settling.first + reach.first, reach.second));
            }
            settled[settling.second] = true;
        }
        return accumulate(settled.begin(), settled.end(), 0) == n ? ret : -1;
    }
};

int main() {
    Solution s;
    vector<vector<int>> times = {{1,2,1}, {2,3,2}, {1,3,2}};
    cout << s.networkDelayTime(times, 3, 1) << endl;
    return 0;
}