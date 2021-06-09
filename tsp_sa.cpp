#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

#include "tsp.h"

using namespace std;

int main() {
    map<int, Region> region_map = load_regions();
    vector<int> current = tsp_init(region_map);
    double res = tsp_result(region_map, current);
    cout << "original result : " << res << endl;
    double t = 900;
    double r = 0.999999;
    // 900 0.999999 final result: 82190.1km
    srand((unsigned)time(NULL));
    vector<int> rand_solution;
    while (t > 1) {
        rand_solution = tsp_solution(current);
        double dist = tsp_result(region_map, rand_solution);
        double delta = dist - res;
        if (delta < 0 || exp(-delta / t) >= ((double)rand()) / RAND_MAX) {
            if (delta > 0) {
                cout << delta << " " << exp(-delta / t) << endl;
            }
            cout << dist << " " << res << " " << t << endl;
            res = dist;
            current = rand_solution;
        }
        // anneling
        t *= r;
    }
    cout << "final result : " << res << endl;
}
