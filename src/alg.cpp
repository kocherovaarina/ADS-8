// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

// Вспомогательная функция для обхода дерева и сбора данных
void collectWords(BST<std::string>::Node* node, std::vector<std::pair<std::string, int>>& words) {
  if (!node) {
    return;
  }
  // Обход левого поддерева
  collectWords(node->left, words);
  // Добавляем текущий узел
  words.emplace_back(node->key, node->count);
  // Обход правого поддерева
  collectWords(node->right, words);
}

void printFreq(BST<std::string>& tree) {
  // Вектор для хранения пар «слово — частота»
  std::vector<std::pair<std::string, int>> words;

  // Собираем все слова и частоты из дерева
  collectWords(tree.root_, words);

  // Сортируем по убыванию частоты
  std::sort(words.begin(), words.end(),
    [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      return a.second > b.second;
    });

  // Открываем файл для записи результата
  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cout << "Cannot open result/freq.txt for writing!" << std::endl;
    return;
  }

  // Выводим на экран и записываем в файл
  for (const auto& wordFreq : words) {
    // Вывод на экран
    std::cout << wordFreq.first << " " << wordFreq.second << std::endl;
    // Запись в файл
    outFile << wordFreq.first << " " << wordFreq.second << std::endl;
  }

  outFile.close();
}
