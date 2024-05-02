#ifndef WORDLADDER_DICTIONARY_H
#define WORDLADDER_DICTIONARY_H

#include <map>
#include <iostream>
#include <fstream>
#include "Graph.h"


class Dictionary {
private:
    std::map<std::string, std::vector<std::string>> wildcardsMap;
    std::vector<std::string> dictionary;

public:
    Dictionary() = default;

    void createDictionary(std::string filePath) {
        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Failed to open the file.");

        std::string word;
        while (getline(file, word)) {
            word.pop_back();
            dictionary.push_back(word);
            for (int i = 0; i < word.size(); i++) {
                std::string wildcard = word;
                wildcard[i] = '*';
                wildcardsMap[wildcard].push_back(word);
            }
        }
    }

    template<typename T>
    void createGraph(Graph<T> &graph) {
        for (const auto& wildcard : wildcardsMap) {
            auto words = wildcard.second;
            if (words.size() > 1) {
                for (int i = 0; i < words.size(); i ++) {
                    if (graph.checkVertex(words[i]) == false)
                        graph.addVertex(words[i]);
                    for (int j = i + 1; j < words.size(); j++) {
                        if (graph.checkVertex(words[j]) == false)
                            graph.addVertex(words[j]);
                        graph.addEdge(words[i], words[j]);
                    }
                }
            }
        }
    }

    std::vector<std::string> getDictionary() {
        return dictionary;
    }

    int getNumberOfWords() {
        return dictionary.size();
    }
};


#endif
