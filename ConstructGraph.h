#include <fstream>
#include "Graph.h"

void readWordsFromFile(std::string fileName, std::vector<std::string> &words) {
    /*
     * Reads the words from a file and stores them in a vector.
     * In: fileName - the name of the file
     *    words - the vector where the words will be stored
     * Out: words - the vector with the words
     */
    std::ifstream file(fileName);

    if (!file.is_open())
        throw std::runtime_error("Couldn't open the file!");

    std::string word;
    while (getline(file, word))
        words.push_back(word);
}

void findWildcardsOfWord(std::vector<std::string> &wildcards, std::string word) {
    /*
     * Finds the wildcards of a word.
     * In: wildcards - the vector where the wildcards will be stored
     *    word - the word
     * Out: wildcards - the vector with the wildcards
     */
    for (int i = 0; i < word.size() - 1; i++) {
        std::string wildcard = word;
        wildcard[i] = '*';
        wildcards.push_back(wildcard);
    }
}

void createWildcardsMap(std::vector<std::string> &words, std::map<std::string, std::vector<std::string>> &wildcardsMap) {
    /*
     * Creates a map with the wildcards of the words.
     * In: words - the vector with the words
     *    wildcardsMap - the map where the wildcards will be stored
     * Out: wildcardsMap - the map with the wildcards
     */
    for (auto word: words) {
        std::vector<std::string> wildcards;
        findWildcardsOfWord(wildcards, word);
        for (auto wildcard: wildcards) {
            if (wildcardsMap.find(wildcard) != wildcardsMap.end()) {
                wildcardsMap[wildcard].push_back(word);
            } else {
                std::vector<std::string> newVector;
                newVector.push_back(word);
                wildcardsMap[wildcard] = newVector;
            }
        }
    }
}

void createGraph(Graph<std::string> &graph, std::vector<std::string> &words) {
    /*
     * Creates a graph with the words.
     * In: graph - the graph
     *    words - the vector with the words
     * Out: graph - the graph with the words
     */
    for (auto word: words)
        graph.addVertex(word);
    std::map<std::string, std::vector<std::string>> wildcardsMap;
    createWildcardsMap(words, wildcardsMap);
    for (auto pair : wildcardsMap) {
        for (int i = 0; i < pair.second.size() - 1; i++)
            for (int j = i + 1; j < pair.second.size(); j++) {
                graph.addEdge(pair.second[i], pair.second[j]);
            }
    }
}