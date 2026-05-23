// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>

template <typename T>
class BST {
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& value)
        : key(value), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root_;

  void clear(Node* node) {
    if (!node) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node* insertNode(Node* node, const T& value) {
    if (!node) {
      return new Node(value);
    }
    if (value < node->key) {
      node->left = insertNode(node->left, value);
    } else if (node->key < value) {
      node->right = insertNode(node->right, value);
    } else {
      ++node->count;
    }
    return node;
  }

  int searchNode(const Node* node, const T& value) const {
    if (!node) {
      return 0;
    }
    if (value < node->key) {
      return searchNode(node->left, value);
    }
    if (node->key < value) {
      return searchNode(node->right, value);
    }
    return node->count;
  }

  int depthNode(const Node* node) const {
    if (!node) {
      return -1;
    }
    const int leftDepth = depthNode(node->left);
    const int rightDepth = depthNode(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

  Node* copyNode(const Node* node) {
    if (!node) {
      return nullptr;
    }
    Node* copy = new Node(node->key);
    copy->count = node->count;
    copy->left = copyNode(node->left);
    copy->right = copyNode(node->right);
    return copy;
  }

 public:
  BST() : root_(nullptr) {}

  BST(const BST& other) : root_(copyNode(other.root_)) {}

  BST& operator=(const BST& other) {
    if (this != &other) {
      clear(root_);
      root_ = copyNode(other.root_);
    }
    return *this;
  }

  ~BST() { clear(root_); }

  void insert(const T& value) { root_ = insertNode(root_, value); }

  int search(const T& value) const { return searchNode(root_, value); }

  int depth() const { return depthNode(root_); }
};

#endif  // INCLUDE_BST_H_
