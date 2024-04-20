#include <iostream>

enum class Color { RED, BLACK };

// generated and debugged by GPT3.5
template<typename T>
struct Node {
    T data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    explicit Node(T value)
        : data(value), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T>
class RedBlackTree {
private:
    Node<T>* root;

    // Private utility functions
    void leftRotate(Node<T>* node);
    void rightRotate(Node<T>* node);
    void fixInsertion(Node<T>* node);
    void fixDeletion(Node<T>* node);
    void transplant(Node<T>* u, Node<T>* v);
    Node<T>* minimumNode(Node<T>* node);
    void deleteNode(Node<T>* node);

public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree();

    // Public interface functions
    void insert(T value);
    void remove(T value);
    void display();
};

// Left rotation
template<typename T>
void RedBlackTree<T>::leftRotate(Node<T>* node) {
    Node<T>* child = node->right;
    node->right = child->left;

    if (child->left != nullptr)
        child->left->parent = node;

    child->parent = node->parent;

    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;

    child->left = node;
    node->parent = child;
}

// Right rotation
template<typename T>
void RedBlackTree<T>::rightRotate(Node<T>* node) {
    Node<T>* child = node->left;
    node->left = child->right;

    if (child->right != nullptr)
        child->right->parent = node;

    child->parent = node->parent;

    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->right)
        node->parent->right = child;
    else
        node->parent->left = child;

    child->right = node;
    node->parent = child;
}

// Fix the tree after insertion
template<typename T>
void RedBlackTree<T>::fixInsertion(Node<T>* node) {
    while (node != root && node->parent->color == Color::RED) {
        if (node->parent == node->parent->parent->left) {
            Node<T>* uncle = node->parent->parent->right;

            if (uncle != nullptr && uncle->color == Color::RED) {
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);
                }

                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                rightRotate(node->parent->parent);
            }
        } else {
            Node<T>* uncle = node->parent->parent->left;

            if (uncle != nullptr && uncle->color == Color::RED) {
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }

                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                leftRotate(node->parent->parent);
            }
        }
    }

    root->color = Color::BLACK;
}

// Fix the tree after deletion
template<typename T>
void RedBlackTree<T>::fixDeletion(Node<T>* node) {
    while (node != root && node->color == Color::BLACK) {
        if (node == node->parent->left) {
            Node<T>* sibling = node->parent->right;

            if (sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;
                leftRotate(node->parent);
                sibling = node->parent->right;
            }

            if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK) {
                sibling->color = Color::RED;
                node = node->parent;
            } else {
                if (sibling->right->color == Color::BLACK) {
                    sibling->left->color = Color::BLACK;
                    sibling->color = Color::RED;
                    rightRotate(sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;
                sibling->right->color = Color::BLACK;
                leftRotate(node->parent);
                node = root;
            }
        } else {
            Node<T>* sibling = node->parent->left;

            if (sibling->color == Color::RED) {
                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;
                rightRotate(node->parent);
                sibling = node->parent->left;
            }

            if (sibling->right->color == Color::BLACK && sibling->left->color == Color::BLACK) {
                sibling->color = Color::RED;
                node = node->parent;
            } else {
                if (sibling->left->color == Color::BLACK) {
                    sibling->right->color = Color::BLACK;
                    sibling->color = Color::RED;
                    leftRotate(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;
                sibling->left->color = Color::BLACK;
                rightRotate(node->parent);
                node = root;
            }
        }
    }

    if (node)
        node->color = Color::BLACK;
}


// Transplant nodes during deletion
template<typename T>
void RedBlackTree<T>::transplant(Node<T>* u, Node<T>* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

// Find the minimum node in a subtree
template<typename T>
Node<T>* RedBlackTree<T>::minimumNode(Node<T>* node) {
    while (node->left != nullptr)
        node = node->left;

    return node;
}

// Delete a node from the tree
template<typename T>
void RedBlackTree<T>::deleteNode(Node<T>* node) {
    Node<T>* child = (node->left != nullptr) ? node->left : node->right;
    Node<T>* original = node;
    Color originalColor = original->color;

    if (child != nullptr)
        child->parent = node->parent;

    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;

    delete original;

    if (originalColor == Color::BLACK && child != nullptr)
        fixDeletion(child);
}

// Destructor
template<typename T>
RedBlackTree<T>::~RedBlackTree() {
    while (root != nullptr)
        deleteNode(root);
}

// Insert a value into the tree
template<typename T>
void RedBlackTree<T>::insert(T value) {
    Node<T>* newNode = new Node<T>(value);

    if (root == nullptr) {
        root = newNode;
        root->color = Color::BLACK;
        return;
    }

    Node<T>* current = root;
    Node<T>* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;

    if (value < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsertion(newNode);
}

// Remove a value from the tree
template<typename T>
void RedBlackTree<T>::remove(T value) {
    Node<T>* node = root;

    while (node != nullptr) {
        if (value == node->data) {
            deleteNode(node);
            return;
        } else if (value < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
}

// Display the tree in-order
template<typename T>
void displayHelper(Node<T>* node) {
    if (node != nullptr) {
        displayHelper(node->left);
        std::cout << node->data << " ";
        displayHelper(node->right);
    }
}

template<typename T>
void RedBlackTree<T>::display() {
    displayHelper(root);
}

int main() {
    RedBlackTree<int> tree;

    tree.insert(5);
    tree.insert(10);
    tree.insert(15);
    tree.insert(20);
    tree.insert(25);
    tree.insert(30);
    tree.insert(35);

    std::cout << "Original Tree: ";
    tree.display();
    std::cout << std::endl;

    tree.remove(15);
    tree.remove(30);

    std::cout << "Tree after deletion: ";
    tree.display();
    std::cout << std::endl;

    return 0;
}
