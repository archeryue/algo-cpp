#include <iostream>
#include <queue>

using namespace std;

// write a red-black tree class
class TreeNode {
public:
    TreeNode(int val) : val(val), left(nullptr), right(nullptr), parent(nullptr), color(0) {}
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    int color; // 0: red, 1: black
};

class RBTree {
public:
    RBTree() : root(nullptr) {}
    void Insert(int val);
    void Delete(int val);
    TreeNode *Search(int val);
    void Print();
private:
    TreeNode *root;
    void insert_fixup(TreeNode *node);
    void delete_fixup(TreeNode *node);
    void left_rotate(TreeNode *node);
    void right_rotate(TreeNode *node);
};

void RBTree::Insert(int val) {
    TreeNode *node = new TreeNode(val);
    if (root == nullptr) {
        root = node;
        root->color = 1;
        return;
    }
    TreeNode *cur = root;
    TreeNode *parent = nullptr;
    while (cur != nullptr) {
        parent = cur;
        if (val < cur->val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    if (val < parent->val) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    node->parent = parent;
    insert_fixup(node);
}

void RBTree::Delete(int val) {
    TreeNode *node = Search(val);
    if (node == nullptr) {
        return;
    }
    TreeNode *child = nullptr;
    if (node->left == nullptr || node->right == nullptr) {
        child = node->left == nullptr ? node->right : node->left;
    } else {
        TreeNode *cur = node->right;
        while (cur->left != nullptr) {
            cur = cur->left;
        }
        node->val = cur->val;
        node = cur;
        child = cur->right;
    }
    if (node->color == 1) {
        node->color = child->color;
        delete_fixup(child);
    }
    if (node->parent == nullptr) {
        root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }
    if (child != nullptr) {
        child->parent = node->parent;
    }
    delete node;
}

TreeNode *RBTree::Search(int val) {
    TreeNode *cur = root;
    while (cur != nullptr) {
        if (val == cur->val) {
            return cur;
        } else if (val < cur->val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return nullptr;
}

void RBTree::Print() {
    if (root == nullptr) {
        return;
    }
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front();
        q.pop();
        cout << node->val << " ";
        if (node->left != nullptr) {
            q.push(node->left);
        }
        if (node->right != nullptr) {
            q.push(node->right);
        }
    }
    cout << endl;
}

void RBTree::insert_fixup(TreeNode *node) {
    while (node != root && node->parent->color == 0) {
        if (node->parent == node->parent->parent->left) {
            TreeNode *uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == 0) {
                node->parent->color = 1;
                uncle->color = 1;
                node->parent->parent->color = 0;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                right_rotate(node->parent->parent);
            }
        } else {
            TreeNode *uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == 0) {
                node->parent->color = 1;
                uncle->color = 1;
                node->parent->parent->color = 0;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                left_rotate(node->parent->parent);
            }
        }
    }
    root->color = 1;
}

void RBTree::delete_fixup(TreeNode *node) {
    while (node != root && node->color == 1) {
        if (node == node->parent->left) {
            TreeNode *brother = node->parent->right;
            if (brother->color == 0) {
                brother->color = 1;
                node->parent->color = 0;
                left_rotate(node->parent);
                brother = node->parent->right;
            }
            if (brother->left->color == 1 && brother->right->color == 1) {
                brother->color = 0;
                node = node->parent;
            } else {
                if (brother->right->color == 1) {
                    brother->left->color = 1;
                    brother->color = 0;
                    right_rotate(brother);
                    brother = node->parent->right;
                }
                brother->color = node->parent->color;
                node->parent->color = 1;
                brother->right->color = 1;
                left_rotate(node->parent);
                node = root;
            }
        } else {
            TreeNode *brother = node->parent->left;
            if (brother->color == 0) {
                brother->color = 1;
                node->parent->color = 0;
                right_rotate(node->parent);
                brother = node->parent->left;
            }
            if (brother->left->color == 1 && brother->right->color == 1) {
                brother->color = 0;
                node = node->parent;
            } else {
                if (brother->left->color == 1) {
                    brother->right->color = 1;
                    brother->color = 0;
                    left_rotate(brother);
                    brother = node->parent->left;
                }
                brother->color = node->parent->color;
                node->parent->color = 1;
                brother->left->color = 1;
                right_rotate(node->parent);
                node = root;
            }
        }
    }
    node->color = 1;
}

void RBTree::left_rotate(TreeNode *node) {
    TreeNode *right = node->right;
    node->right = right->left;
    if (right->left != nullptr) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == nullptr) {
        root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

void RBTree::right_rotate(TreeNode *node) {
    TreeNode *left = node->left;
    node->left = left->right;
    if (left->right != nullptr) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == nullptr) {
        root = left;
    } else if (node == node->parent->left) {
        node->parent->left = left;
    } else {
        node->parent->right = left;
    }
    left->right = node;
    node->parent = left;
}

// test
int main() {
    RBTree tree = RBTree();
    for (int i = 0; i < 10; i++) {
        tree.Insert(i);
    }
    tree.Print();
    for (int i = 0; i < 10; i++) {
        int val = 10 + rand() % 10;
        cout << "insert " << val << endl;
        tree.Insert(val);
    }
    tree.Print();
    for (int i = 0; i < 10; i++) {
        tree.Delete(i);
    }
    tree.Print();
}
