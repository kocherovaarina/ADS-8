// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

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

    int depth() const {
        return depth(root);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    int count() const {
        return count(root);
    }

    int count(Node* node) const {
        if (!node) return 0;
        return 1 + count(node->left) + count(node->right);
    }
};

#endif  // INCLUDE_BST_H_

// Теперь BST доступен — даже если #include не сработал

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file("src/war_peace.txt");
  if (!file.is_open()) {
    file.open("../src/war_peace.txt");
  }
  if (!file.is_open()) {
    file.open("./war_peace.txt");
  }
  if (!file.is_open()) {
    std::cout << "ERROR: Cannot open war_peace.txt" << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
  file.close();
}

