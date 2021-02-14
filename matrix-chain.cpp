#include <iostream>
#include <vector>

using namespace std;

int main(int argv, char **args) {
    int n;
    cin >> n;
    int x, y;
    vector<pair<int, int>> matrix_chain;
    vector<vector<int>> cal_table(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        matrix_chain.push_back(make_pair(x, y));
    }
    for (int i = 0; i < n; i++) {
        cal_table[i][i] = 0;
    }
    for (int i = 1; i < n; i++) {
        // cal_table[i - 1][i] = matrix_chain[i - 1].first *
        // matrix_chain[i].first * matrix_chain[i].second;
        for (int j = i - 1; j >= 0; j--) {
            int min = INT_MAX;
            int base = matrix_chain[j].first * matrix_chain[i].second;
            for (int k = j; k < i; k++) {
                int res = cal_table[j][k] + cal_table[k + 1][i] +
                          (base * matrix_chain[k].second);
                if (res < min) {
                    min = res;
                }
            }
            cal_table[j][i] = min;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i) {
                cout << "  ";
            } else {
                cout << cal_table[i][j] << " ";
            }
        }
        cout << endl;
    }
}