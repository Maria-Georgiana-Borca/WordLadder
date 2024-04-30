#include "playMode.h"
#include "dictionary.h"
#include "Graph.h"

void playMode() {
    std::string name;
    std::cout << "Please enter your name: ";
    std::cin >> name;

    int numberOfCharacters;
    std::cout << "Please select the number of characters: ";
    std::cin >> numberOfCharacters;

    std::string filePath =
            "/Users/mariaborca/Documents/GitHub/WordLadder/EnglishDictionary/" + std::to_string(numberOfCharacters) +
            ".txt";
    Dictionary dictionary;
    dictionary.createDictionary(filePath);

    Graph<std::string> graph;
    dictionary.createGraph(graph);

    int startIndex = rand() % dictionary.getNumberOfWords();
    int finishIndex = rand() % dictionary.getNumberOfWords();

    while (finishIndex == startIndex)
        finishIndex = rand() % dictionary.getNumberOfWords();

    std::vector<std::string> words = dictionary.getDictionary();

    std::cout << "Starting word: " << words[startIndex] << '\n';
    std::cout << "Target word: " << words[finishIndex] << '\n';

    std::string newWord = words[startIndex];
    std::vector<std::string> path = graph.BFS(words[startIndex], words[finishIndex]);
    while (newWord != words[finishIndex]) {
        char hint;
        std::cout << "Do you need a hint? (y/n)";
        std::cin >> hint;
        if (hint == 'y') {
            std::cout << "The hint: " << path[1] << '\n';
            newWord = path[1];
            path = graph.BFS(newWord, words[finishIndex]);
        } else {
            std::string answear;
            std::cout << "Please enter the word: ";
            std::cin >> answear;
            if (std::count(words.begin(), words.end(), answear) == 0)
                std::cout << "The introduced word is not valid.\n";
            else {
                int differentLetters = 0;
                for (int i = 0; i < answear.size(); i++)
                    if (newWord[i] != answear[i])
                        differentLetters ++;
                if (differentLetters != 1)
                    std::cout << "The new word should have only one different letter.\n";
                else {
                    newWord = answear;
                    path = graph.BFS(newWord, words[finishIndex]);
                }
            }
        }

    }

}
