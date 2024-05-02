#include "playMode.h"
#include "dictionary.h"
#include "Graph.h"
#include <chrono>

bool valid(std::string word1, std::string word2) {
    int distinctLetters = 0;
    for (int i = 0; i < word1.size(); i++)
        if (word1[i] != word2[i])
            distinctLetters++;
    return distinctLetters == 1;
}

void printDifference(std::string word1, std::string word2) {
    std::cout << "The new word: ";
    for (int i = 0; i < word1.size(); i++) {
        if (word1[i] == word2[i])
            std::cout << word1[i];
        else std::cout << '(' << word2[i] << ')';
    }
    std::cout << '\n';
}

void
saveToFile(std::string filePath, std::string time, std::vector<std::string> usedWords, int numberOfHints,
           int numberOfMoves, int optimalNumberOfMoves) {
    std::ofstream myFile(filePath, std::ios::app);
    myFile << "Starting word: " << usedWords[0] << "\nTarget word: " << usedWords[usedWords.size() - 1] << '\n';
    myFile << "Date and time: " << time;
    myFile << "Number of hints used: " << numberOfHints << '\n';
    myFile << "Used words: ";
    for (auto word : usedWords)
        myFile << word << ", ";
    myFile << '\n';
    myFile << "Number of moves: " << numberOfMoves << '\n';
    myFile << "The optimal number of moves that could have been used: " << optimalNumberOfMoves << '\n';

}

void playMode() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

    std::string name;
    std::cout << "Please enter your name: ";
    std::cin >> name;
    std::cout << "Welcome, " << name << "!\n\n";

    int numberOfCharacters;
    std::cout << "Please select the number of characters: ";
    std::cin >> numberOfCharacters;

    std::string filePath =
            "/Users/mariaborca/Documents/GitHub/WordLadder/EnglishDictionary/" + std::to_string(numberOfCharacters) +
            ".txt";
    Dictionary dictionary;
    dictionary.createDictionary(filePath);

    std::cout << "Please wait just a little bit to create the graph.\n\n";
    Graph<std::string> graph;
    dictionary.createGraph(graph);

    std::vector<std::string> words = dictionary.getDictionary();
    int startIndex = rand() % dictionary.getNumberOfWords();
    int finishIndex = rand() % dictionary.getNumberOfWords();
    while (graph.BFS(words[startIndex], words[finishIndex]).empty()) {
        startIndex = rand() % dictionary.getNumberOfWords();
        finishIndex = rand() % dictionary.getNumberOfWords();
    }

    std::string startingWord = words[startIndex];
    std::string finishWord = words[finishIndex];

    std::cout << "Starting word: " << startingWord << '\n';
    std::cout << "Target word: " << finishWord << '\n';
    std::cout << "Good luck!\n\n";

    std::cout << "Please enter hint! if you need a hint.\n";
    std::cout << "Please enter quit! if you want to exit the game\n\n";

    std::string answer;
    std::string currentWord = startingWord;

    std::cout << "Calculating the best path. Please wait.\n\n";
    std::vector<std::string> path = graph.BFS(startingWord, finishWord);
    int index = 1;

    int numberOfHints = 0;
    int numberOfMoves = 0;
    int optimalNumberOfMoves = path.size() - 1;

    std::vector<std::string> usedWords;
    usedWords.push_back(startingWord);

    while (answer != finishWord) {
        std::cout << "Please enter the word: ";
        std::cin >> answer;
        if (answer == "quit!") {
            std::cout << "Are you sure you want to quit the game! [y/n]";
            char ans;
            std::cin >> ans;
            if (ans == 'y')
                break;
        } else if (answer == "help!") {
            printDifference(currentWord, path[index]);
            currentWord = path[index];
            usedWords.push_back(currentWord);
            index++;
            numberOfHints++;
            if(currentWord == finishWord) {
                std::cout << "You did it! Congratulations!\n\n";
                break;
            }
        } else {
            if (std::find(words.begin(), words.end(), answer) == words.end())
                throw std::invalid_argument("The word is not in the dictionary!");
            else if (!valid(currentWord, answer))
                throw std::invalid_argument("The introduced word must differ by only one letter.");
            else {
                if (answer == finishWord) {
                    numberOfMoves++;
                    usedWords.push_back(answer);
                    std::cout << "You did it! Congratulations!\n\n";
                    break;
                }
                else {
                    std::cout << "Good job! Keep going!\n\n";
                    printDifference(currentWord, answer);
                    currentWord = answer;

                    index = 0;
                    numberOfMoves++;
                    usedWords.push_back(currentWord);

                    std::cout << "Calculating the best path. Please wait.\n\n";
                    path = graph.BFS(startingWord, finishWord);
                }
                
            }
        }
    }

    std::string fileName = name + ".csv";
    saveToFile(fileName, std::ctime(&t_c), usedWords, numberOfHints, numberOfMoves, optimalNumberOfMoves);
}
