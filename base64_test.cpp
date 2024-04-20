#include <iostream>
#include <vector>
#include <string>

#include "base64.h"

using namespace std;

int main() {
    vector<uint8_t> bytes {'A', 'B', 'C'};
    cout << "testcase 1 " << endl;
    cout << "Source : ";
    for (auto byte : bytes) {
        cout << (char)byte << " ";
    }
    cout << endl << "Encode : ";
    cout << Encode(bytes) << endl << "Decode : ";
    for (auto byte : Decode(Encode(bytes))) {
        cout << (char)byte << " ";
    }
    cout << endl;
    cout << "testcase 2 " << endl;
    cout << "Source : ";
    bytes = {'s', 'd', 'f', '1', '2'};
    for (auto byte : bytes) {
        cout << (char)byte << " ";
    }
    cout << endl << "Encode : ";
    cout << Encode(bytes) << endl << "Decode : ";
    for (auto byte : Decode(Encode(bytes))) {
        cout << (char)byte << " ";
    }
    cout << endl;
    return 0;
}
