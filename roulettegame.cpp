#include "casino.h"
#include "appgeneralmacros.h"

#include <fstream>
#include <cstring>

bool validArgument(std::string argument)
{
    if( argument != HELP_OPTION &&
        argument != HELP_SHORTCUT_OPTION &&
        argument != SAVE_TO_FILE_OPTION )
    {
        return false;
    }
    return true;
}

bool helperArgument(std::string argument)
{
    if( argument == HELP_OPTION ||
        argument == HELP_SHORTCUT_OPTION )
    {
        return true;
    }
    return false;
}

bool outputToFile(std::string argument)
{
    if( argument == SAVE_TO_FILE_OPTION){
        return true;
    }
    return false;
}

void createSixRoulettePlayers(std::vector<RoulettePlayer>& players)
{
    RoulettePlayer player1(RED,         1, "Player A");
    RoulettePlayer player2(BLACK,       2, "Player B");
    RoulettePlayer player3(_19_TO_36,   3, "Player C");
    RoulettePlayer player4(_1_TO_18,    4, "Player D");
    RoulettePlayer player5(EVEN,        5, "Player E");
    RoulettePlayer player6(ODD,         6, "Player F");

    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);
    players.push_back(player5);
    players.push_back(player6);
    return;
}

void joinPlayersToRoulette(Casino& myCasino, std::vector<RoulettePlayer>& players)
{
    for(int i = 0; i < players.size(); i++){
        myCasino.joinRoulette(players[i]);
    }
    return;
}

void showPlayersBalance(std::vector<RoulettePlayer>& players)
{
    // show each player balance and total players balance
    int totalPlayersBalance = 0;
    for(int i = 0; i < players.size(); i++){
        totalPlayersBalance += players[i].getPlayerBalance();
        std::cout << players[i].name << " balance is: " << players[i].getPlayerBalance() << std::endl;
    }
    std::cout << "Total (" << players.size() << ") players balance is: " << totalPlayersBalance << std::endl;
    return;
}

int main(int argc, char* argv[])
{

    std::ofstream output;
    std::streambuf *coutbuf;

    std::cout << WELCOME_TEXT << std::endl;
    if(argc > 2){
        std::cout << BAD_ARGUMENTS << std::endl;
        // show error information
        std::cout << "Error number: " << E2BIG << std::endl;
        std::cout << "Error description: " << strerror(E2BIG) << std::endl;
        return EXIT_FAILURE;
    }
    if(argc == 2){
        if(!validArgument(argv[1])){
            std::cout << BAD_ARGUMENTS << std::endl;
            // show error information
            std::cout << "Error number: " << EINVAL << std::endl;
            std::cout << "Error description: " << strerror(EINVAL) << std::endl;
            return EXIT_FAILURE;
        }
        if(helperArgument(argv[1])){
            std::cout << HELPER_TEXT << std::endl;
            return EXIT_SUCCESS;
        }
        if(outputToFile(argv[1])){
            // set output to file
            output.open(OUTPUT_FILE_PATH);
            if(output.is_open()){
                std::cout << "File successfully opened!" << std::endl;
                std::cout << "Writing output to file located in: " << OUTPUT_FILE_PATH << std::endl;
                coutbuf = std::cout.rdbuf(); //save old buf
                std::cout.rdbuf(output.rdbuf()); //redirect std::cout to OUTPUT_FILE_PATH!
            }
            else{
                std::cout << "File could not be opened! Writing output to console.." << std::endl;
            }
        }
    }

    std::cout << "Initializing game..." << std::endl;
    // initialize objects and data structures
    Casino myCasino;
    std::vector<RoulettePlayer> players;
    createSixRoulettePlayers(players);
    
    // show initialized, starting
    std::cout << "Game initialized.." << std::endl << "Starting game.." << std::endl;
    // open casino
    myCasino.open();
    // open roulettes in casino
    myCasino.openRoulettes();
    // add players to a roulette of casino
    joinPlayersToRoulette(myCasino, players);
    // start playing casino's roulettes
    myCasino.playRoulettes();
    // close casino
    myCasino.close();

    // show relevant game information
    showPlayersBalance(players);
    if(output.is_open()){
        std::cout.rdbuf(coutbuf); //reset to standard output again
        output.close();
        std::cout << "File successfully closed!" << std::endl;
    }
    std::cout << GOOD_BYE_TEXT << std::endl;
    return EXIT_SUCCESS;
}