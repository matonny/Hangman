#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

void randomCategory();

void chooseCategory();

void quit();

std::vector<std::vector<std::string>> getWords();

int getRandomFromRange(const int &min, const int &max);
void gameLoop(const std::string &word);
void printHUD(const std::vector<char> &characters, const std::vector<bool> &guessedCharacters, const int &lives);
bool isLetter(const char &character);
std::vector<int> isInWord(const std::vector<char> &charactersOfWord, const char &testedCharacter);
std::vector<bool> updateGuessedLetters(std::vector<bool> guessedLetters, std::vector<int> correctEntries);
bool isGameWon(const std::vector<bool> &guessedLetter);

int main()
{
    bool gameOn = true;

    while (gameOn)
    {
        std::cout << "Welcome to Hangman! Choose game mode by typing its number: " << std::endl;
        std::cout << "1. Random category" << std::endl << "2. Choose category" << std::endl << "3. Quit" << std::endl;
        std::string option = "";
        std::cin >> option;
        if (option == "1")
        {
            randomCategory();
        } else if (option == "2")
        {
            chooseCategory();
        } else if (option == "3")
        {
            gameOn = false;
        } else
        {
            std::cout << "This is not a proper game mode" << std::endl;
        }
    }
}

void randomCategory()
{
    std::cout << "RANDOM CATEGORY " << std::endl;
    std::vector<std::vector<std::string> > allWords = getWords();
    for (int i = 0; i < allWords.size(); i++)
    {
        std::cout << "Category: " << allWords[i][0] << std::endl;
        for (int j = 1; j < allWords[i].size(); j++)
        {
            std::cout << allWords[i][j] << std::endl;
        }
    }
    int category = getRandomFromRange(0, allWords.size() - 1);
    int word = getRandomFromRange(1, allWords[category].size()-1);
    std::string generatedWord = allWords[category][word];
    gameLoop(generatedWord);
}

void chooseCategory()
{
    std::cout << "CHOSE CATEGORY" << std::endl;
}

void quit()
{

}

std::vector<std::vector<std::string>> getWords()
{
    std::string line;
    std::vector<std::vector<std::string> > allWords = {};
    std::ifstream words(".wordList.txt");
    if (words.is_open())
    {
        std::cout << "The file is loaded" << std::endl;
        while (std::getline(words, line))
        {
            std::istringstream iss(line);
            std::vector<std::string> wordsOfCategory((std::istream_iterator<std::string>(iss)),
                                                     std::istream_iterator<std::string>());
            allWords.push_back(wordsOfCategory);
        }
    } else
    {
        std::cout << "Can't load file" << std::endl;
    }
    return allWords;
}

int getRandomFromRange(const int &min, const int &max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void gameLoop(const std::string &wordToGuess)
{
    int lives = 9;
    std::vector<char> characters = {};
    for (int i = 0; i < wordToGuess.size(); i++)
    {
        characters.push_back(wordToGuess.at(i));
    }
    std::vector<bool> guessed(characters.size(), false);
    while (lives > 0)
    {
        printHUD(characters, guessed, lives);
        std::string answer = "";
        std::cin >> answer;
        if (answer.size() == 1 && isLetter(answer.at(0)))
        {
            std::vector<int> matchingEntries = isInWord(characters, answer.at(0));
            if(matchingEntries.size() > 0){
                std::cout << "Well done, you guessed the letter!" << std::endl;
                guessed = updateGuessedLetters(guessed, matchingEntries);
                if(isGameWon(guessed)){
                    std::cout << "Brawo, wygrałeś!" << std::endl;
                    break;
                }
            }else{
                std::cout << "You missed!" << std::endl;
                lives--;
                if(lives == 0){
                    std::cout << "GAME OVER, następnym razem pójdzie Ci lepiej! :)" << std::endl;
                }
            }

        } else
        {
            std::cout << "Please type a lowercase or uppercase letter" << std::endl;
        }
    }

}

void printHUD(const std::vector<char> &characters, const std::vector<bool> &guessedCharacters, const int &lives){
    if(lives > 1){
        std::cout << lives << " lives left" << std::endl;
    }else{
        std::cout << lives << " life left" << std::endl;
    }
    for(int i = 0; i < guessedCharacters.size(); i++){
        if(guessedCharacters[i]){
            std::cout << characters[i];
        }else{
            std::cout << "_";
        }
    }
    std::cout << std::endl;
}
bool isLetter (const char &character){
    if(character < 91 && character > 64){
        return true;
    }
    else if(character < 123 && character > 96){
        return true;
    }
    return false;
}
std::vector<int> isInWord(const std::vector<char> &charactersOfWord, const char &testedCharacter){
    std::vector<int> matchingEntries = {};
    for(int i = 0; i < charactersOfWord.size(); i++){
        if(charactersOfWord[i] == testedCharacter){
            matchingEntries.push_back(i);
        }
    }
    return matchingEntries;
}
std::vector<bool> updateGuessedLetters(std::vector<bool> guessedLetters, std::vector<int> correctEntries){
    for(int i = 0; i < correctEntries.size(); i++){
        guessedLetters[correctEntries[i]] = true;
    }
    return guessedLetters;
}
bool isGameWon(const std::vector<bool> &guessedLetter){
    bool allTrue = true;
    for (int i = 0; i < guessedLetter.size() ; i++){
        if(!guessedLetter[i]){
            allTrue = false;
        }
    }
    return allTrue;
}