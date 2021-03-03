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
    vector<int> init_solution = tsp_init(region_map);
    double res = tsp_result(region_map, init_solution);
    cout << "original result : " << res << endl;
    double t = 5000;
    double r = 0.9;
    srand((unsigned)time(NULL));
    vector<int>* current = &init_solution;
    while (t > 1) {
        auto rand_solution = tsp_solution(*current);
        double dist = tsp_result(region_map, rand_solution);
        if (dist < res ||
            exp((res - dist) / t) >= ((double)rand()) / RAND_MAX) {
            cout << dist << " " << res << " " << t << endl;
            res = dist;
            current = &rand_solution;
        }
        // anneling
        cout << "!" << endl;
        t *= r;
    }
    cout << "final result : " << res << endl;
}