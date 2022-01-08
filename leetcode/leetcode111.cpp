#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    int minDepth(TreeNode *root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> nodeQueue;
        root->val = 1;
        nodeQueue.push(root);
        TreeNode* node = nodeQueue.front();
        while(node->left != nullptr || node->right != nullptr) {
            if (node->left != nullptr) {
                node->left->val = node->val + 1;
                nodeQueue.push(node->left);
            }
            if (node->right != nullptr) {
                node->right->val = node->val + 1;
                nodeQueue.push(node->right);
            }
            nodeQueue.pop();
            node = nodeQueue.front();
        }
        return node->val;
    }
};