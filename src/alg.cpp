// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

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

std::vector<std::pair<std::string, int>> freqVector;

void collectCallback(const std::string& word, int freq) {
  freqVector.push_back({word, freq});
}

void printFreq(BST<std::string>& tree) {
  freqVector.clear();
  
  tree.traverse(collectCallback);
  
  std::sort(freqVector.begin(), freqVector.end(),
    [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      if (a.second != b.second) {
        return a.second > b.second;
      }
      return a.first < b.first;
    });
  
  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cout << "Cannot open result/freq.txt for writing!" << std::endl;
    return;
  }
  
  for (const auto& wordFreq : freqVector) {
    std::cout << wordFreq.first << " " << wordFreq.second << std::endl;
    outFile << wordFreq.first << " " << wordFreq.second << std::endl;
  }
  
  outFile.close();
}
