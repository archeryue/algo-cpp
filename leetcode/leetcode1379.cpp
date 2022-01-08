#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
   public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        TreeNode* node;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(cloned);
        while (!nodeQueue.empty()) {
            node = nodeQueue.front();
            nodeQueue.pop();
            if (node == NULL) 
                continue;
            if (node->val == target->val) 
                return node;
            nodeQueue.push(node->left);
            nodeQueue.push(node->right);
        }
        return NULL;
    }
};