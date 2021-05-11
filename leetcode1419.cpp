#include <iostream>
#include <vector>
#include <string>

using namespace std;

string croak = "croak";

int findIndex(char ch) {
    for (int i = 0; i < croak.length(); i++) {
        if (croak.at(i) == ch) return i;
    }
    return -1;
}

int minNumberOfFrogs(string croakOfFrogs) {
    vector<int> frogs = {0, 0, 0, 0, 0};
    int count = 0;
    int idle = 0;
    for (char ch : croakOfFrogs) {
        int index = findIndex(ch);
        if (index == -1) return -1;
        if (index > 0 && frogs[index - 1] < 1) return -1;
        frogs[index]++;
        if (index == 0) {
            if (idle > 0) {
                idle--;
            } else {
                count++;
            }
        } else {
            frogs[index - 1]--;
        }
        if (index == 4) {
            idle++;
            frogs[index]--;
        }
    }
    for (auto i : frogs) {
        if (i != 0) return -1;
    }
    return count;
}

int main(int argv, char **args) {
    string croakStr;
    cin >> croakStr;
    cout << minNumberOfFrogs(croakStr) << endl;
    return 0;
}

