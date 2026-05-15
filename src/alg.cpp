// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include #include "../../include/bst.h"//Правильный путь: из src/ → в include/

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
