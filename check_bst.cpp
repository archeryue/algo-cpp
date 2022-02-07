#include <cstdint>
#include <iostream>

using namespace std;

class Node {
 public:
     int value;
     Node* left;
     Node* right;
};

bool inner_check(Node* root, int min, int max) {
    if (root == nullptr) {
        return true;
    }
    if (root->value > max || root->value < min) {
        return false;
    }
    bool left_ok = root->left == nullptr;
    if (root->left && root->value > INT32_MIN) {
        left_ok = inner_check(root->left, min, root->value-1);
    }
    bool right_ok = root->right == nullptr;
    if (root->right && root->value < INT32_MAX) {
        right_ok = inner_check(root->right, root->value+1, max);
    }
    return left_ok && right_ok;
}

bool check_bst(Node* root) {
    return inner_check(root, INT32_MIN, INT32_MAX);      
}
