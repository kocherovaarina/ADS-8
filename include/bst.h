// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <functional>
#include <string>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        Node* left = nullptr;
        Node* right = nullptr;

        explicit Node(const T& val) : value(val) {}
    };

    Node* root = nullptr;
    std::function<bool(const T&, const T&)> cmp = std::less<T>();

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* insert(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }
        if (cmp(value, node->value)) {
            node->left = insert(node->left, value);
        } else if (cmp(node->value, value)) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    // Вспомогательные методы с другим именем — чтобы не было рекурсии в себя
    int depthHelper(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depthHelper(node->left), depthHelper(node->right));
    }

    int countHelper(Node* node) const {
        if (!node) return 0;
        return 1 + countHelper(node->left) + countHelper(node->right);
    }

    int search(Node* node, const T& value, int depth) const {
        if (!node) {
            return -1;
        }
        if (!cmp(value, node->value) && !cmp(node->value, value)) {
            return depth;
        }
        if (cmp(value, node->value)) {
            return search(node->left, value, depth + 1);
        } else {
            return search(node->right, value, depth + 1);
        }
    }

 public:
    BST() = default;
    explicit BST(std::function<bool(const T&, const T&)>& comparator) : cmp(comparator) {}

    ~BST() {
        clear(root);
    }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const T& value) {
        root = insert(root, value);
    }

    // Публичные методы — вызывают вспомогательные
    int depth() const {
        return depthHelper(root);
    }

    int count() const {
        return countHelper(root);
    }

    int search(const T& value) const {
        return search(root, value, 0);
    }
};

#endif  // INCLUDE_BST_H_
