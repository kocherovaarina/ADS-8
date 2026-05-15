// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

template<typename T>
class BST {
 private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size;

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
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    void inorder(Node* node, T* arr, int& index) const {
        if (node) {
            inorder(node->left, arr, index);
            arr[index++] = node->data;
            inorder(node->right, arr, index);
        }
    }

 public:
    BST() : root(nullptr), size(0) {}

    ~BST() {
        clear(root);
    }

    void add(const T& value) {
        if (!search(value)) {
            root = insert(root, value);
            size++;
        }
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    int depth() const {
        return depth(root);
    }

    int count() const {
        return size;
    }

    T* toArray() const {
        if (size == 0) return nullptr;
        T* arr = new T[size];
        int index = 0;
        inorder(root, arr, index);
        return arr;
    }
};

#endif  // INCLUDE_BST_H_
