#include <iostream>
#include <vector>
#include <string>

using namespace std;

int kmp(const string& text, const string& pattern) {
    vector<int> next(pattern.length(), 0);
    // build next
    int i = 1, j = 0;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[j]) {
            next[i++] = ++j;
        } else if (j == 0) {
            i++;
        } else {
            j = next[j - 1];
        }
    }
    // search
    i = 0, j = 0;
    while (i < text.length() && j < pattern.length()) {
        if (text[i] == pattern[j]) {
            i++; j++;
        } else if (j == 0) {
            i++;
        } else {
            j = next[j - 1];
        }
    }
    return j == pattern.length() ? i - j : -1;
}

int main() {
    string text, pattern;
    cout << "text: "; cin >> text;
    cout << "pattern: "; cin >> pattern;
    cout << kmp(text, pattern) << endl;
    return 0;
}
