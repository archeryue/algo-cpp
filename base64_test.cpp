#include <iostream>
#include <vector>
#include <string>

#include "base64.h"

using namespace std;

int main() {
    vector<uint8_t> bytes {'A', 'B', 'C'};
    cout << Encode(bytes) << endl;
    for (auto byte : Decode(Encode(bytes))) {
        cout << (char)byte << " ";
    }
    cout << endl;
    bytes = {'s', 'd', 'f', '1', '2'};
    cout << Encode(bytes) << endl;
    for (auto byte : Decode(Encode(bytes))) {
        cout << (char)byte << " ";
    }
    cout << endl;
    return 0;
}
