#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
    int nearest = INT_MAX;
    for (auto g : ghosts) {
        int tmp = abs(g[0] - target[0]) + abs(g[1] - target[1]);
        nearest = nearest > tmp ? tmp : nearest;
    }
    return (abs(target[0]) + abs(target[1])) < nearest;
}

int main() {
    vector<vector<int>> gs {{1,0}, {0,3}};
    vector<int> t {0,1};
    cout << escapeGhosts(gs, t) << endl;
    return 0;
}
