#include "dictionary.h"
#include "Graph.h"

void autoMode() {
    std::string startWord;
    std::string finishWord;

    std::cout << "Please enter the start word: ";
    std::cin >> startWord;
    std::cout << "Please enter the finish word: ";
    std::cin >> finishWord;

    if (startWord.size() != finishWord.size())
        throw std::invalid_argument("The words must have the same number of characters.");

    std::string filePath = "/Users/mariaborca/Documents/GitHub/WordLadder/EnglishDictionary/" + std::to_string(startWord.size()) + ".txt";

    Dictionary dictionary;
    dictionary.createDictionary(filePath);

    if (std::find(dictionary.getDictionary().begin(), dictionary.getDictionary().end(), startWord) == dictionary.getDictionary().end())
        throw std::invalid_argument("The starting word is not valid.");

    if (std::find(dictionary.getDictionary().begin(), dictionary.getDictionary().end(), finishWord) == dictionary.getDictionary().end())
        throw std::invalid_argument("The finish word is not valid.");

    Graph<std::string> graph;
    dictionary.createGraph(graph);

    std::vector<std::string> path = graph.BFS(startWord, finishWord);

    if (path.empty())
        throw std::runtime_error("There is no way of obtaining" + finishWord + "from " + startWord +'.');
    else {
        std::cout << "Transformation: \n";
        for (auto word : path)
            std::cout << word << '\n';
    }
}