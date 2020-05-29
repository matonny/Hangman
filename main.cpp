#include <iostream>
#include <fstream>

void randomCategory();

void chooseCategory();

void quit();

int main()
{
    bool gameOn = true;
    std::cout << "Welcome to Hangman! Choose game mode by typing its number: " << std::endl;
    std::cout << "1. Random category" << std::endl << "2. Choose category" << std::endl << "3. Quit" << std::endl;
    while (gameOn)
    {

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
    std::fstream wordList;
    wordList.open(".wordList.txt", std::ios::in);
    if(!wordList.is_open()){
        std::cout << "The file couldn't be opened" << std::endl;
    }
}

void chooseCategory()
{
    std::cout << "CHOSE CATEGORY" << std::endl;
}

void quit()
{

}
