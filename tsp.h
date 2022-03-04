#ifndef TSP_H
#define TSP_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

class Region {
   public:
    int code;
    string name;
    double longitude;
    double latitude;
};

const int tsp_start = 440300;
const double pi = 3.1415926535897932384626433832795;
const double EARTH_RADIUS = 6378.137;

map<int, Region> load_regions() {
    map<int, Region> region_map;
    ifstream ifs("region/cities.csv");
    string line;
    while (getline(ifs, line)) {
        stringstream ss(line);
        string buffer;
        Region region;
        getline(ss, buffer, ',');
        region.code = stoi(buffer);
        getline(ss, buffer, ',');
        region.name = buffer;
        getline(ss, buffer, ',');
        region.longitude = stod(buffer);
        getline(ss, buffer, ',');
        region.latitude = stod(buffer);
        region_map[region.code] = region;
    }
    ifs.close();
    return move(region_map);
}

vector<int> tsp_init(const map<int, Region>& region_map) {
    vector<int> solution;
    for (auto iter : region_map) {
        if (iter.first != tsp_start) {
            solution.push_back(iter.first);
        }
    }
    random_device rd;
    default_random_engine rng {rd()};
    shuffle(begin(solution), end(solution), rng);
    return move(solution);
}

vector<int> tsp_solution(const vector<int>& current) {
    vector<int> tsp_new(current);
    auto x = rand() % tsp_new.size(); 
    auto y = rand() % tsp_new.size();
    swap(tsp_new[x], tsp_new[y]);
    return move(tsp_new);
}

double rad(double d) {
    return d * pi / 180.0;
}

double tsp_distance(const Region& left, const Region& right) {
    double radLng1 = rad(left.longitude);
    double radLat1 = rad(left.latitude);
    double radLng2 = rad(right.longitude);
    double radLat2 = rad(right.latitude);
    double a = radLat1 - radLat2;
    double b = radLng1 - radLng2;

    double s = 2 * asin(sqrt(pow(sin(a / 2), 2) +
                             cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));
    return s * EARTH_RADIUS;
}

double tsp_result(const map<int, Region>& region_map,
                  const vector<int>& solution) {
    double sum = 0;
    int left = tsp_start;
    for (auto code : solution) {
        sum += tsp_distance(region_map.at(left), region_map.at(code));
        left = code;
    }
    sum += tsp_distance(region_map.at(left), region_map.at(tsp_start));
    return sum;
}

#endif
