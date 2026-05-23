// Copyright 2021 NNTU-CS
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  while (!file.eof()) {
    const int ch = file.get();
    if (ch >= 'A' && ch <= 'Z') {
      word += static_cast<char>(ch - 'A' + 'a');
    } else if (ch >= 'a' && ch <= 'z') {
      word += static_cast<char>(ch);
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
}
