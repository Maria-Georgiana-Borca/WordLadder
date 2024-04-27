#include "Graph.h"
#include <iostream>
#include "ConstructGraph.h"

int main() {
    std::vector<std::string> words;
    readWordsFromFile("/Users/mariaborca/Documents/GitHub/WordLadder/EnglishDictionary/2.txt", words);

    std::map<std::string, std::vector<std::string>> wildcardsMap;

    Graph<std::string> graph;
    createGraph(graph, words);
    return 0;
}