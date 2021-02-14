#include <iostream>
#include <vector>

using namespace std;

int main(int argv, char **args) {
    // input
    int n;
    cin >> n;
    int x, y;
    vector<pair<int, int>> matrix_chain;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        matrix_chain.push_back(make_pair(x, y));
    }
    // init
    vector<vector<int>> cal_table(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        cal_table[i][i] = 0;
    }
    // dp
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            int min = INT_MAX;
            int base = matrix_chain[j].first * matrix_chain[i].second;
            for (int k = j; k < i; k++) {
                int res = cal_table[j][k] + cal_table[k + 1][i] +
                          (base * matrix_chain[k].second);
                min = res < min ? res : min;
            }
            cal_table[j][i] = min;
        }
    }
    // output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i) {
                cout << "0 ";
            } else {
                cout << cal_table[i][j] << " ";
            }
        }
        cout << endl;
    }
}