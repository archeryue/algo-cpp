#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

const int kGeoBitCount = 8 * 5;

const vector<char> kGeoTable {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'b', 'c', 'd', 'e', 'f', 'g',
                            'h', 'j', 'k', 'm', 'n', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

vector<bool> binarySearch(double start, double end, double value, int loop) {
    vector<bool> ret(loop);
    for (int i = 0; i <= loop; i++) {
        double mid = start + (end - start) / 2;
        if (value > mid) {
            ret[i] = true;
            start = mid;
        } else {
            ret[i] = false;
            end = mid;
        }
    }
    return ret;
}

char base32(vector<bool> bits) {
    assert(bits.size() == 5);
    int value = 0;
    for (bool bit : bits) {
        value = ((value << 1) | bit);
    }
    return kGeoTable[value];
}

string GeoHash(double longitude, double latitude) {
    int loop = kGeoBitCount / 2;
    vector<bool> lonCode = binarySearch(-180, 180, longitude, loop);
    vector<bool> latCode = binarySearch(-90, 90, latitude, loop);
    vector<bool> bitCode(kGeoBitCount);
    for (int i = 0; i < loop; i++) {
        bitCode[2 * i] = lonCode[i];
        bitCode[2 * i + 1] = latCode[i];
    }
    string ret;
    int i = 0;
    while (i < bitCode.size()) {
        auto start = bitCode.begin() + i;
        auto end = bitCode.begin() + i + 5;
        vector<bool> bits(start, end);
        ret.push_back(base32(bits));
        i += 5;
    }
    return ret;
}

int main() {
    cout << GeoHash(116.390705, 39.923201) << endl;
    return 0;
}