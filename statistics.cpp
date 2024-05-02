#include "statistics.h"
#include <iostream>
#include <fstream>
#include <set>

std::vector<std::string> allUsedWord(std::string fileName) {
    std::ifstream myFile(fileName);
    std::vector<std::string> usedWords;

    std::string line;
    while (getline(myFile, line)) {
        if (line[0] == 'U') {
            int i = 12;
            std::string word;
            while (i < line.size()) {
                if (line[i] != ',')
                    word += line[i];
                else {
                    usedWords.push_back(word);
                    word = "";
                }
                i ++;
            }
        }
    }
    return usedWords;
}

int numberUniqueWords(std::vector<std::string>usedWords) {
    std::set<std::string>uniqueWords;
    for (auto word: usedWords)
        uniqueWords.insert(word);
    return uniqueWords.size();
}
