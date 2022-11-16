#include "casino.h"
#include "appgeneralmacros.h"

#include <fstream>
#include <cstring>
#include <memory>

bool validArgument(std::string argument)
{
    if (argument != HELP_OPTION &&
        argument != HELP_SHORTCUT_OPTION &&
        argument != SAVE_TO_FILE_OPTION)
    {
        return false;
    }
    return true;
}

bool helperArgument(std::string argument)
{
    if (argument == HELP_OPTION ||
        argument == HELP_SHORTCUT_OPTION)
    {
        return true;
    }
    return false;
}

bool outputToFile(std::string argument)
{
    if (argument == SAVE_TO_FILE_OPTION)
    {
        return true;
    }
    return false;
}

void createSixRoulettePlayers(std::vector<std::shared_ptr<RoulettePlayer>> &players)
{
    std::shared_ptr<RoulettePlayer> player1 = std::make_shared<RoulettePlayer>(RoulettePlayer(RED, 1, "Player A"));
    std::shared_ptr<RoulettePlayer> player2 = std::make_shared<RoulettePlayer>(RoulettePlayer(BLACK, 2, "Player B"));
    std::shared_ptr<RoulettePlayer> player3 = std::make_shared<RoulettePlayer>(RoulettePlayer(_19_TO_36, 3, "Player C"));
    std::shared_ptr<RoulettePlayer> player4 = std::make_shared<RoulettePlayer>(RoulettePlayer(_1_TO_18, 4, "Player D"));
    std::shared_ptr<RoulettePlayer> player5 = std::make_shared<RoulettePlayer>(RoulettePlayer(EVEN, 5, "Player E"));
    std::shared_ptr<RoulettePlayer> player6 = std::make_shared<RoulettePlayer>(RoulettePlayer(ODD, 6, "Player F"));

    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);
    players.push_back(player5);
    players.push_back(player6);
    return;
}

void showPlayersBalance(std::vector<std::shared_ptr<RoulettePlayer>> &players)
{
    // show each player balance and total players balance
    int totalPlayersBalance = 0;
    for (int i = 0; i < players.size(); i++)
    {
        totalPlayersBalance += players[i]->getPlayerBalance();
        std::cout << players[i]->getPlayerName() << " balance is: " << players[i]->getPlayerBalance() << std::endl;
    }
    std::cout << "Total (" << players.size() << ") players balance is: " << totalPlayersBalance << std::endl;
    return;
}

int main(int argc, char *argv[])
{

    std::ofstream output;
    std::streambuf *coutbuf;

    std::cout << WELCOME_TEXT << std::endl;
    if (argc > 2)
    {
        std::cout << BAD_ARGUMENTS << std::endl;
        // show error information
        std::cout << "Error number: " << E2BIG << std::endl;
        std::cout << "Error description: " << strerror(E2BIG) << std::endl;
        return EXIT_FAILURE;
    }
    if (argc == 2)
    {
        if (!validArgument(argv[1]))
        {
            std::cout << BAD_ARGUMENTS << std::endl;
            // show error information
            std::cout << "Error number: " << EINVAL << std::endl;
            std::cout << "Error description: " << strerror(EINVAL) << std::endl;
            return EXIT_FAILURE;
        }
        if (helperArgument(argv[1]))
        {
            std::cout << HELPER_TEXT << std::endl;
            return EXIT_SUCCESS;
        }
        if (outputToFile(argv[1]))
        {
            // set output to file
            output.open(OUTPUT_FILE_PATH);
            if (output.is_open())
            {
                std::cout << "File successfully opened!" << std::endl;
                std::cout << "Writing output to file located in: " << OUTPUT_FILE_PATH << std::endl;
                coutbuf = std::cout.rdbuf();     // save old buf
                std::cout.rdbuf(output.rdbuf()); // redirect std::cout to OUTPUT_FILE_PATH!
            }
            else
            {
                std::cout << "File could not be opened! Writing output to console.." << std::endl;
            }
        }
    }

    std::cout << "Initializing game..." << std::endl;
    // initialize objects and data structures
    Casino myCasino;
    std::vector<std::shared_ptr<RoulettePlayer>> playersPtrShr;
    createSixRoulettePlayers(playersPtrShr);

    // show initialized, starting
    std::cout << "Game initialized.." << std::endl
              << "Starting game.." << std::endl;
    // open casino
    myCasino.open();
    // open roulettes in casino
    myCasino.openRoulettes();
    // add players to a roulette of casino
    for (int i = 0; i < playersPtrShr.size(); i++)
    {
        myCasino.addPlayerToRoulette(playersPtrShr[i]);
    }
    //  start playing casino's roulettes
    myCasino.playRoulettes();
    // close casino
    myCasino.close();

    // show relevant game information
    showPlayersBalance(playersPtrShr);
    if (output.is_open())
    {
        std::cout.rdbuf(coutbuf); // reset to standard output again
        output.close();
        std::cout << "File successfully closed!" << std::endl;
        showPlayersBalance(playersPtrShr);
    }
    std::cout << GOOD_BYE_TEXT << std::endl;
    return EXIT_SUCCESS;
}