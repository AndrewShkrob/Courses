#include <cassert>
#include <deque>
#include <iostream>

using namespace std;

struct Node {
    Node(int v, Node *p)
            : value(v), parent(p) {}

    int value;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent;
};

Node *Next(Node *node) {
    if (!node)
        return nullptr;
    if (!node->left && !node->right && (!node->parent || node->parent->value < node->value)) {
        Node *next_node = node->parent;
        while (next_node && next_node->value <= node->value) {
            next_node = next_node->parent;
        }
        return next_node;
    }
    if (node->right && node->right->value > node->value) {
        Node *next_node = node->right;
        while (next_node->left)
            next_node = next_node->left;
        return next_node;
    }
    if (!node->left && !node->right && node->parent->value > node->value)
        return node->parent;

    return nullptr;
}