#include <iostream>
#include <vector>
#include <string>

using namespace std;

int kmp(const string& text, const string& query) {
    vector<int> next(query.length(), 0);
    // build next
    int i = 1, j = 0;
    while (i < query.length()) {
        if (query[i] == query[j]) {
            next[i++] = ++j;
        } else if (j == 0) {
            i++;
        } else {
            j = next[j - 1];
        }
    }
    // search
    i = 0, j = 0;
    while (i < text.length() && j < query.length()) {
        if (text[i] == query[j]) {
            i++; j++;
        } else if (j == 0) {
            i++;
        } else {
            j = next[j - 1];
        }
    }
    return j == query.length() ? i - j : -1;
}

int main() {
    string text, query;
    cout << "text: "; cin >> text;
    cout << "query: "; cin >> query;
    cout << kmp(text, query) << endl;
    return 0;
}
