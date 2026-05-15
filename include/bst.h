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

  Node* Insert(Node* node, const T& key) {
    if (!node) {
      return new Node(key);
    }
    if (key < node->key) {
      node->left = Insert(node->left, key);
    } else if (key > node->key) {
      node->right = Insert(node->right, key);
    } else {
      ++node->count;
    }
    return node;
  }

  int Search(Node* node, const T& key) const {
    if (!node) {
      return 0;
    }
    if (key == node->key) {
      return node->count;
    }
    if (key < node->key) {
      return Search(node->left, key);
    }
    return Search(node->right, key);
  }

  int Depth(Node* node) const {
    if (!node) {
      return 0;
    }
    int left_depth = Depth(node->left);
    int right_depth = Depth(node->right);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
  }

  void Inorder(Node* node, const std::function<void(const T&, int)>& visit) const {
    if (node) {
      Inorder(node->left, visit);
      visit(node->key, node->count);
      Inorder(node->right, visit);
    }
  }

  void Clear(Node* node) {
    if (node) {
      Clear(node->left);
      Clear(node->right);
      delete node;
    }
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    Clear(root);
  }

  void Insert(const T& key) {
    root = Insert(root, key);
  }

  int Search(const T& key) const {
    return Search(root, key);
  }

  int Depth() const {
    return Depth(root);
  }

  void TraverseInOrder(const std::function<void(const T&, int)>& visit) const {
    Inorder(root, visit);
  }
};

#endif  // INCLUDE_BST_H_
