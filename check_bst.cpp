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
    if (root->value > max || root->value < min) {
        return false;
    }
    if (root->left != nullptr && root->left->value > root->value) {
        return false;
    }
    if (root->right != nullptr && root->right->value < root->value) {
        return false;
    }
    return inner_check(root->left, min, root->value) && inner_check(root->right, root->value, max);
}

bool check_bst(Node* root) {
    return inner_check(root, INT32_MIN, INT32_MAX);      
}
