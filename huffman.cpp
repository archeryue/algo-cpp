#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <sstream>

using namespace std;

class HNode {
public:
    HNode* left;
    HNode* right;
    
    HNode(char e, int c) : left(nullptr), right(nullptr), count(c) {
        elements.insert(e);
    }

    HNode(HNode* l, HNode* r): left(l), right(r) {
        elements.insert(l->elements.cbegin(), l->elements.cend());
        elements.insert(r->elements.cbegin(), r->elements.cend());
        count = l->count + r->count;
    }

    ~HNode() {}

    bool contains(char e) {
        return elements.count(e) > 0;
    }

    char onlyOne() {
        return *elements.begin();
    }

    string toString() {
        stringstream ss;
        for (auto e : elements) {
            ss << e;
        }
        ss << ":" << count;
        return ss.str();
    }

    friend class HNodeCmp;

private:
    set<char> elements;
    int count;
};

class HNodeCmp {
public:
    bool operator() (HNode* a, HNode* b) {
        return a->count > b->count;
    }
};

void buildHuffman(HNode* root, string pre, map<char, string>& codeMap) {
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        codeMap[root->onlyOne()] = pre;
        return;
    }

    if (root->left != nullptr) {
        buildHuffman(root->left, pre + "0", codeMap);
    }
    if (root->right != nullptr) {
        buildHuffman(root->right, pre + "1", codeMap);
    }
    return;
}

int main() {
    string input;
    cin >> input;

    map<char, int> countMap;
    for (auto c : input) {
        if (countMap.count(c) == 0) {
            countMap[c] = 0;
        }
        countMap[c]++;
    }

    priority_queue<HNode*, vector<HNode*>, HNodeCmp> pqueue;
    for (auto entry : countMap) {
        pqueue.push(new HNode(entry.first, entry.second));
    }

    while (pqueue.size() > 1) {
        HNode* l = pqueue.top(); pqueue.pop();
        HNode* r = pqueue.top(); pqueue.pop();
        pqueue.push(new HNode(l, r));
    }

    HNode* root = pqueue.top();
    map<char, string> codeMap;
    buildHuffman(root, "", codeMap);
    for (auto entry : codeMap) {
        cout << entry.first << ":" << entry.second << endl;
    }

    for (auto ch : input) {
        cout << codeMap[ch];
    }
    cout << endl;
    return 0;
}
