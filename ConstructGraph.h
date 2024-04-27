#include <fstream>

void readWordsFromFile(std::string fileName, std::vector<std::string> &words) {
    std::ifstream file(fileName);

    if (!file.is_open())
        throw std::runtime_error("Couldn't open the file!");

    std::string word;
    while (getline(file, word))
        words.push_back(word);
}

void findWildcardsOfWord(std::vector<std::string> &wildcards, std::string word) {
    for (int i = 0; i < word.size() - 1; i++) {
        std::string wildcard = word;
        wildcard[i] = '*';
        wildcards.push_back(wildcard);
    }
}

void createWildcardsMap(std::vector<std::string> &words, std::map<std::string, std::vector<std::string>> &wildcardsMap) {
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
    for (auto word: words)
        graph.addVertex(word);
    int cont = 0;
    std::map<std::string, std::vector<std::string>> wildcardsMap;
    createWildcardsMap(words, wildcardsMap);
    for (auto pair : wildcardsMap) {
        for (int i = 0; i < pair.second.size() - 1; i++)
            for (int j = i + 1; j < pair.second.size(); j++) {
                //std::cout << pair.second[i] << '\n' << pair.second[j] << "\n\n";
                cont ++;
                graph.addEdge(pair.second[i], pair.second[j]);
            }
    }
}