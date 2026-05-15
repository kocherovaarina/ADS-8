// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <sstream>

template<typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size;
    int totalWords;

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
        } else {
            node->count++;
        }
        return node;
    }

    int search(Node* node, const T& value) const {
        if (!node) return 0;
        if (value == node->data) return node->count;
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

    std::string cleanWord(const std::string& word) const {
        std::string result;
        for (char c : word) {
            if (std::isalpha(c)) {
                result += std::tolower(c);
            }
        }
        return result;
    }

 public:
    BST() : root(nullptr), size(0), totalWords(0) {}

    ~BST() {
        clear(root);
    }

    void add(const T& value) {
        if (search(root, value) == 0) {
            size++;
        }
        root = insert(root, value);
        totalWords++;
    }

    int search(const T& value) const {
        return search(root, value);
    }

    int depth() const {
        return depth(root);
    }

    int count() const {
        return size;
    }

    int totalCount() const {
        return totalWords;
    }

    T* toArray() const {
        if (size == 0) return nullptr;
        T* arr = new T[size];
        int index = 0;
        inorder(root, arr, index);
        return arr;
    }

    void load(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;
        
        std::string word;
        while (file >> word) {
            std::string cleaned = cleanWord(word);
            if (!cleaned.empty()) {
                add(cleaned);
            }
        }
        file.close();
    }
};

// Определение функции makeTree
inline void makeTree(BST<std::string>& tree, const char* filename) {
    tree.load(filename);
}

#endif  // INCLUDE_BST_H_
