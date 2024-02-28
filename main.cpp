#include <iostream>
#include <array>
#include <vector>
#include <string_view>
#include "Random.h"

namespace Game
{
    int turns{7};

    std::vector<std::string> words{"apple", "flight", "tractor", "question", "cloud", "battle"};

    std::string_view getRandomWord()
    {
        return words[Random::get(0, words.size())]; // between 0 and length of 'words' array
    };
}

class Player
{
private:
    std::string_view randomWord{Game::getRandomWord()};
    std::vector<char> guessedCharacters{};
    int matchedWords{};

public:
    std::string_view getWord()
    {
        return this->randomWord;
    }

    std::vector<char> &getGuesses()
    {
        return this->guessedCharacters;
    }

    void addGuesses(char letter)
    {
        this->guessedCharacters.push_back(letter);
    }

    void addMatchedWords(int n)
    {
        this->matchedWords = n;
    }

    bool checkWin()
    {
        return matchedWords == this->randomWord.size();
    }
};

bool makeGuess(Player &player)
{
    std::cout << "Guess a letter ";
    while (true)
    {
        char guess{};
        std::cin >> guess;

        if (!std::cin)
        { // If error, loop again
            std::cin.clear();
            continue;
        }

        // If already a match, loop again
        bool alreadyGuessed{false};
        for (auto character : player.getGuesses())
        {
            if (character == guess)
            {
                std::cout << "You have already made that guess. Try again\n";
                alreadyGuessed = true;
            }
        }
        if (alreadyGuessed)
        {
            continue;
        }

        // if incorrect, --turn
        // bool match{ false }; // Set to true if match found; condition to end while loop as failure
        player.addGuesses(guess);
        for (auto index{0}; index < player.getWord().size(); ++index)
        {
            if (player.getWord()[index] == guess)
            {

                // player.addMatchedWords(3);
                return true;
            }
        }
        break;
    }
    std::cout << "Wrong\n";
    return false;
}

void draw(Player &player)
{
    if (!makeGuess(player))
    {
        Game::turns--;
        std::cout << Game::turns << "/7 guesses remaining\n";
    }; // Get guess
    int matchedTotal{};
    for (auto index{0}; index < player.getWord().size(); ++index)
    { // Print word if guess is right or wrong
        bool match{false};
        for (auto guesses{0}; guesses < player.getGuesses().size(); ++guesses)
        {
            if (player.getWord()[index] == player.getGuesses()[guesses])
            {
                match = true;
                matchedTotal++;
                std::cout << player.getGuesses()[guesses];
            }
        }
        if (!match)
        {
            std::cout << '_';
        }
    }
    std::cout << '\n';
    player.addMatchedWords(matchedTotal);
}

bool playGame(Player &player)
{ // True if won, false if lost
    while (Game::turns > 0)
    { // Game session loop;
        draw(player);
        if (player.checkWin())
        {
            return true;
        }
    }
    return false;
}

int main()
{
    while (true)
    { // Game loop; loop will reset game
        Player player{};
        Game::turns = 7;
        if (!playGame(player))
        {
            std::cout << "You lost. Better luck next time!\n";
        }
        else
        {
            std::cout << "Congratulations! you won!\n";
        }
        std::cout << "Do you want to play again? (y/n) ";
        char playAgain{};
        std::cin >> playAgain;

        if (playAgain == 'y')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    std::cout << "Thanks for playing!\n";
}
