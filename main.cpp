#include <iostream>
using namespace std;

enum Color { RED, BLACK };

class Node {
public:
    int data;
    Color color;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        color = RED;
        left = right = nullptr;
    }
};

class RedBlackTree {
private:
    Node* root;

    // Left Rotation
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        return y;
    }

    // Right Rotation
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;

        return x;
    }

    // Fix Red-Red Violations
    Node* fixInsert(Node* node) {

        // Left Left Case
        if (node->left &&
            node->left->color == RED &&
            node->left->left &&
            node->left->left->color == RED) {

            if (node->right &&
                node->right->color == RED) {

                // Recoloring
                node->color = RED;
                node->left->color = BLACK;
                node->right->color = BLACK;
            }
            else {
                // Rotation
                node = rotateRight(node);

                node->color = BLACK;
                node->right->color = RED;
            }
        }

        // Left Right Case
        else if (node->left &&
                 node->left->color == RED &&
                 node->left->right &&
                 node->left->right->color == RED) {

            if (node->right &&
                node->right->color == RED) {

                // Recoloring
                node->color = RED;
                node->left->color = BLACK;
                node->right->color = BLACK;
            }
            else {
                // Rotations
                node->left = rotateLeft(node->left);
                node = rotateRight(node);

                node->color = BLACK;
                node->right->color = RED;
            }
        }

        // Right Right Case
        else if (node->right &&
                 node->right->color == RED &&
                 node->right->right &&
                 node->right->right->color == RED) {

            if (node->left &&
                node->left->color == RED) {

                // Recoloring
                node->color = RED;
                node->left->color = BLACK;
                node->right->color = BLACK;
            }
            else {
                // Rotation
                node = rotateLeft(node);

                node->color = BLACK;
                node->left->color = RED;
            }
        }

        // Right Left Case
        else if (node->right &&
                 node->right->color == RED &&
                 node->right->left &&
                 node->right->left->color == RED) {

            if (node->left &&
                node->left->color == RED) {

                // Recoloring
                node->color = RED;
                node->left->color = BLACK;
                node->right->color = BLACK;
            }
            else {
                // Rotations
                node->right = rotateRight(node->right);
                node = rotateLeft(node);

                node->color = BLACK;
                node->left->color = RED;
            }
        }

        return node;
    }

    // Recursive Insert
    Node* insertHelper(Node* node, int value) {

        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insertHelper(node->left, value);

        else if (value > node->data)
            node->right = insertHelper(node->right, value);

        node = fixInsert(node);

        return node;
    }

    // Inorder Traversal
    void inorderHelper(Node* node) {

        if (node == nullptr)
            return;

        inorderHelper(node->left);

        cout << node->data
             << "("
             << (node->color == RED ? "R" : "B")
             << ") ";

        inorderHelper(node->right);
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    void insert(int value) {

        root = insertHelper(root, value);

        // Root always BLACK
        root->color = BLACK;
    }

    void inorder() {
        inorderHelper(root);
    }
};

int main() {

    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(13);

    cout << "Inorder Traversal:\n";
    tree.inorder();

    return 0;
}