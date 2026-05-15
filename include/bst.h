// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <functional>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insert(Node* node, const T& key) {
    if (!node) {
      return new Node(key);
    }
    if (key < node->key) {
      node->left = insert(node->left, key);
    } else if (key > node->key) {
      node->right = insert(node->right, key);
    } else {
      node->count++;
    }
    return node;
  }

  int search(Node* node, const T& key) const {
    if (!node) {
      return 0;
    }
    if (key == node->key) {
      return node->count;
    }
    if (key < node->key) {
      return search(node->left, key);
    }
    return search(node->right, key);
  }

  int depth(Node* node) const {
    if (!node) {
      return 0;
    }
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
  }

  void inorder(Node* node, const std::function<void(const T&, int)>& visit) const {
    if (node) {
      inorder(node->left, visit);
      visit(node->key, node->count);
      inorder(node->right, visit);
    }
  }

  void clear(Node* node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    clear(root);
  }

  void insert(const T& key) {
    root = insert(root, key);
  }

  int search(const T& key) const {
    return search(root, key);
  }

  int depth() const {
    return depth(root);
  }

  void traverseInOrder(const std::function<void(const T&, int)>& visit) const {
    inorder(root, visit);
  }
};

#endif  // INCLUDE_BST_H_

