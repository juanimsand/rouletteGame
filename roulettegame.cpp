#include "casino.h"
#include "outputmanager.h"

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

void showPlayersBalance(std::vector<RoulettePlayer>& players, OutputManager& outputManager)
{
    // show each player balance and total players balance
    int totalPlayersBalance = 0;
    for(int i = 0; i < players.size(); i++){
        totalPlayersBalance += players[i].getPlayerBalance();
        outputManager.showPlayerBalance(players[i].name, players[i].getPlayerBalance());
    }
    outputManager.showPlayersTotalBalance(players.size(), totalPlayersBalance);
    return;
}

int main(int argc, char* argv[])
{
    OutputManager outputManager;
    outputManager.showWelcomeMessage();
    if(argc > 2){
        outputManager.showBadArguments();
        // show error information
        outputManager.showErrorInformation(E2BIG);
        return EXIT_FAILURE;
    }
    if(argc == 2){
        if(!validArgument(argv[1])){
            outputManager.showBadArguments();
            // show error information
            outputManager.showErrorInformation(EINVAL);
            return EXIT_FAILURE;
        }
        if(helperArgument(argv[1])){
            outputManager.showHelp();
            return EXIT_SUCCESS;
        }
        if(outputToFile(argv[1])){
            // set output to file
            outputManager.setOutputType(true);
        }
    }


    // initialize objects and data structures
    Casino myCasino;
    std::vector<RoulettePlayer> players;
    createSixRoulettePlayers(players);

    // set output managers
    myCasino.setOutputManager(outputManager);
    for(int i = 0; i < players.size(); i++){
        players[i].setOutputManager(outputManager);
    }
    
    // add new line to console output
    outputManager.forceOutputToConsole("\n");
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
    showPlayersBalance(players, outputManager);
    outputManager.showGoodByeMessage();
    return EXIT_SUCCESS;
}