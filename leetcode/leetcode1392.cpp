#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

string longestPrefix(string s) {
    vector<int> next(s.length(), 0);
    int i = 1, j = 0;
    while (i < s.length()) {
        if (s[i] == s[j]) {
            next[i++] = ++j;
        } else if (j == 0) {
            i++;
        } else {
            j = next[j-1];
        }
    }
    return s.substr(0, next[next.size()-1]);
}

int main() {
    cout << longestPrefix("tobeornottobe") << endl;
    cout << longestPrefix("level") << endl;
    cout << longestPrefix("a") << endl;
    return 0;
}
