// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>

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
    int uniqueWords;
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

    int find(Node* node, const T& value) const {
        if (!node) return 0;
        if (value == node->data) return node->count;
        if (value < node->data) return find(node->left, value);
        return find(node->right, value);
    }

    int getDepth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(getDepth(node->left), getDepth(node->right));
    }

    void inorder(Node* node, T* arr, int& index) const {
        if (node) {
            inorder(node->left, arr, index);
            arr[index++] = node->data;
            inorder(node->right, arr, index);
        }
    }

 public:
    BST() : root(nullptr), uniqueWords(0), totalWords(0) {}

    ~BST() {
        clear(root);
    }

    void add(const T& value) {
        if (find(root, value) == 0) {
            uniqueWords++;
        }
        root = insert(root, value);
        totalWords++;
    }

    int search(const T& value) const {
        return find(root, value);
    }

    int depth() const {
        return getDepth(root);
    }

    int count() const {
        return uniqueWords;
    }

    T* toArray() const {
        if (uniqueWords == 0) return nullptr;
        T* arr = new T[uniqueWords];
        int index = 0;
        inorder(root, arr, index);
        return arr;
    }
};

// Функция makeTree будет вызвана из alg.cpp
// Она определена здесь как inline, чтобы не было конфликта
inline void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    std::string word;
    while (file >> word) {
        std::string cleanWord;
        for (char c : word) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                cleanWord += std::tolower(static_cast<unsigned char>(c));
            }
        }
        if (!cleanWord.empty()) {
            tree.add(cleanWord);
        }
    }
    file.close();
}

#endif  // INCLUDE_BST_H_
