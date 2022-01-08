#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int sum = 0;
        if (X >= customers.size()) {
            for (int i = 0; i < customers.size(); i++) {
                sum += customers[i];   
            }
            return sum;
        }
        for (int i = 0; i < customers.size(); i++) {
            if (!grumpy[i]) sum += customers[i];
        }
        int bonus = 0;
        for (int i = 0; i < X; i++) {
            if (grumpy[i]) bonus += customers[i];
        }
        int maxBonus = bonus;
        for (int i = X; i < customers.size(); i++) {
            if (grumpy[i - X]) bonus -= customers[i - X];
            if (grumpy[i]) bonus += customers[i];
            maxBonus = bonus > maxBonus ? bonus : maxBonus;
        }
        return sum + maxBonus;
    }
};

int main() {
    vector<int> customers = {1,0,1,2,1,1,7,5};
    vector<int> grumpy = {0,1,0,1,0,1,0,1};
    int X = 3;
    Solution s;
    cout << s.maxSatisfied(customers, grumpy, X) << endl;
    return 0;
}