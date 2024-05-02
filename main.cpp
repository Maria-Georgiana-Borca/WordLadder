#include "dictionary.h"
#include "automaticMode.h"
#include "playMode.h"
#include "statistics.h"

void run() {
    while (true) {
        std::cout << "Welcome to word ladder!\n\n";
        std::cout << "What mode do you want to try?\n";
        std::cout << "1. Automatic mode.\n";
        std::cout << "2. Play mode.\n";
        std::cout << "3. Statistics.\n";
        std::cout << "0. Exit\n\n";

        int option;
        std::cout << "Please enter an option: ";
        std::cin >> option;

        if (option == 0)
            break;
        else if (option == 1) {
            try {
                autoMode();
                std::cout << "\n\n";
            } catch (const std::invalid_argument &e) {
                std::cout << "Couldn't start the game: " << e.what() << "\n\n";
            } catch (const std::runtime_error &e) {
                std::cout << "Couldn't start the game: " << e.what() << "\n\n";
            }
        } else if (option == 2) {
            try {
                playMode();
            } catch (const std::invalid_argument &e) {
                std::cout << "Couldn't start the game: " << e.what() << "\n\n";
            }
        } else if(option == 3) {
            std::string name;
            std::cout << "Please enter the user name: ";
            std::cin >> name;
            std::string fileName = name + ".csv";
            std::vector<std::string> allWordsUsed = allUsedWord(fileName);
            std::cout << "The number of unique words used: " << numberUniqueWords(allWordsUsed) << '\n';
        } else {
            std::cout << "The option must be between 0 and 2!\n\n";
        }
    }
}

int main() {
    run();
    return 0;
}