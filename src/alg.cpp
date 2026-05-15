// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    std::string word;
    while (file >> word) {
        // Очищаем слово от знаков препинания и приводим к нижнему регистру
        std::string cleanWord;
        for (char c : word) {
            if (std::isalpha(c)) {
                cleanWord += std::tolower(c);
            }
        }
        if (!cleanWord.empty()) {
            tree.add(cleanWord);
        }
    }
    file.close();
}
