#include "outputmanager.h"

OutputManager::OutputManager(){}

OutputManager::~OutputManager(){}

void OutputManager::setOutputType(bool _type)
{
    toFile = _type;
    if(toFile){
        openFile();
    }
    return;
}

void OutputManager::openFile()
{
    outputFile.open(OUTPUT_FILE_PATH);
    if(outputFile.is_open()){
        messageToConsole("File successfully opened!");
        std::string message = "Writing output to file located in: ";
        message.append(OUTPUT_FILE_PATH);
        messageToConsole(message);
        return;
    }
    toFile = false;
    messageToConsole("File could not be opened! Writing output to console..");
    return;
}

void OutputManager::forceOutputToConsole(std::string message)
{
    std::cout << message << std::endl;
    return;
}

void OutputManager::messageToFile(std::string message)
{
    if(!outputFile){
        messageToConsole("Something happened with file..");
        messageToConsole("Writing output to console..");
        toFile = false;
        messageToConsole(message);
    }
    else{
        outputFile << message << std::endl;
    }
    return;
}

void OutputManager::messageToConsole(std::string message)
{
    std::cout << message << std::endl;
    return;
}

void OutputManager::printMessage(std::string message)
{
    if(toFile){
        messageToFile(message);
    }
    else{
        messageToConsole(message);
    }
    return;
}

void OutputManager::showWelcomeMessage()
{
    forceOutputToConsole(WELCOME_TEXT);
    return;
}

void OutputManager::showGoodByeMessage()
{
    forceOutputToConsole(GOOD_BYE_TEXT);
    return;
}

void OutputManager::showBadArguments()
{
    printMessage(BAD_ARGUMENTS);
    return;
}

void OutputManager::showHelp()
{
    printMessage(HELPER_TEXT);
    return;
}

void OutputManager::showErrorInformation(int error)
{
    std::string errMessage = "Error number: ";
    errMessage.append(std::to_string(error));
    errMessage.append("\n");
    errMessage.append("Error description: ");
    errMessage.append(strerror(error));
    errMessage.append("\n");
    printMessage(errMessage);
    return;
}


// specific messages

// casino
void OutputManager::showCasinoAlreadyOpen()
{
    printMessage(CASINO_ALREADY_OPENED);
    return;
}

void OutputManager::showOpeningCasino()
{
    printMessage(OPENING_CASINO);
    return;
}

void OutputManager::showCasinoOpened()
{
    printMessage(CASINO_OPENED);
    return;
}

void OutputManager::showCasinoAlreadyClose()
{
    printMessage(CASINO_ALREADY_CLOSED);
    return;
}

void OutputManager::showClosingCasino()
{
    printMessage(CLOSING_CASINO);
    return;
}

void OutputManager::showCasinoClosed()
{
    printMessage(CASINO_CLOSED);
    return;
}

void OutputManager::showCouldNotJoinByCasino()
{
    printMessage(COULD_NOT_JOIN_ROULETTE_BY_CASINO);
    return;
}

void OutputManager::showCouldNotJoinByRouletteAvailable(std::string playerName)
{
    std::string message = "Sorry ";
    message.append(playerName);
    message.append(", there are no roulettes availables at the moment.");
    printMessage(message);
    return;
}

void OutputManager::showPlayerHasJoinedRoulette(std::string playerName, int rouletteId)
{
    std::string message = playerName;
    message.append(" has joined roulette ");
    message.append(std::to_string(rouletteId));
    message.append(".");
    printMessage(message);
    return;
}

void OutputManager::showCouldNotJoinByRouletteClosed(std::string playerName)
{
    std::string message = "Sorry ";
    message.append(playerName);
    message.append(", no roulette open at the moment.");
    printMessage(message);
    return;
}

void OutputManager::showClosingAllGames()
{
    printMessage(CLOSING_ALL_GAMES);
    return;
}

// roulette
void OutputManager::showRouletteOpened(int rouletteId)
{
    std::string message = "Roulette ";
    message.append(std::to_string(rouletteId));
    message.append(" opened!");
    printMessage(message);
    return;
}

void OutputManager::showRouletteAlreadyOpen(int rouletteId)
{
    std::string message = "Roulette ";
    message.append(std::to_string(rouletteId));
    message.append(" is already open!");
    printMessage(message);
    return;
}

void OutputManager::showRouletteClosed(int rouletteId)
{
    std::string message = "Roulette ";
    message.append(std::to_string(rouletteId));
    message.append(" closed!");
    printMessage(message);
    return;
}

void OutputManager::showRouletteAlreadyClose(int rouletteId)
{
    std::string message = "Roulette ";
    message.append(std::to_string(rouletteId));
    message.append(" is already close!");
    printMessage(message);
    return;
}

void OutputManager::showCouldNotPlayDueToClose(int rouletteId)
{
    std::string message = "Roulette ";
    message.append(std::to_string(rouletteId));
    message.append(" is closed, could not play.");
    printMessage(message);
    return;
}

void OutputManager::showCouldNotPlayDueToLackOfPlayers(int rouletteId)
{
    std::string message = "Roulette ";
    message.append(std::to_string(rouletteId));
    message.append(" has no players to play.");
    printMessage(message);
    return;
}

void OutputManager::showStartingRoulette(int rouletteId)
{
    std::string message = "Starting roulette number ";
    message.append(std::to_string(rouletteId));
    message.append("..");
    printMessage(message);
    return;
}

void OutputManager::showRoulettePlayNumber(int rouletteId, int playerNumber)
{
    std::string message = "Roulette ";
    message.append(std::to_string(rouletteId));
    message.append(" play number ");
    message.append(std::to_string(playerNumber));
    printMessage(message);
    return;
}

void OutputManager::showLastRoulettePlay(int rouletteId)
{
    std::string message = "Last roulette ";
    message.append(std::to_string(rouletteId));
    message.append(" play..");
    printMessage(message);
    return;
}

void OutputManager::showPlaceBets()
{
    printMessage(PLACE_YOUR_BETS);
    return;
}

void OutputManager::showNoMoreBets()
{
    printMessage(NO_MORE_BETS);
    return;
}

void OutputManager::showRouletteSpinning()
{
    printMessage(ROULETTE_SPINNING);
    return;
}

void OutputManager::showBallFlangOut()
{
    printMessage(BALL_FLANG_OUT_ROULETTE);
    return;
}

void OutputManager::showHouseWins()
{
    printMessage(HOUSE_WINS);
    return;
}

void OutputManager::showWinnerNumber(int number, bool red)
{
    std::string message = std::to_string(number);
    if(red){
        message.append(", red!");
    }
    else{
        message.append(", black!");
    }
    printMessage(message);
    return;
}

void OutputManager::showBadPlayerType()
{
    printMessage(BAD_PLAYER_TYPE);
    return;
}

void OutputManager::showNumberInfo(int number, bool red, bool even, bool minor)
{
    std::string message = "*** Number ";
    message.append(std::to_string(number));
    message.append(" information ***");
    message.append("\n");
    message.append(red ? "red" : "black");
    message.append("\n");
    message.append(even ? "even" : "odd");
    message.append("\n");
    message.append(minor ? "minor" : "major");
    printMessage(message);
    return;
}

void OutputManager::showPlayerNotesTitle()
{
    printMessage(SHOWING_PLAYER_NOTES);
    return;
}

// roulette player
void OutputManager::showPlayerWon(std::string name, int playerId, std::string betType, int ammountWon)
{
    std::string message = name;
    message.append(" (id: ");
    message.append(std::to_string(playerId));
    message.append(") bet on ");
    message.append(betType);
    message.append(" and won ");
    message.append(std::to_string(ammountWon));
    printMessage(message);
    return;
}

void OutputManager::showPlayerLost(std::string name, int playerId, std::string betType, int ammountWon)
{
    std::string message = name;
    message.append(" (id: ");
    message.append(std::to_string(playerId));
    message.append(") bet on ");
    message.append(betType);
    message.append(" and lost ");
    message.append(std::to_string(ammountWon));
    printMessage(message);
    return;
}

void OutputManager::showPlayerOutOfMoney(std::string name)
{
    std::string message = name;
    message.append(" is out of money!");
    printMessage(message);
    return;
}

void OutputManager::showPlayerBetOutOfRange(std::string name, int bet)
{
    std::string message = name;
    message.append(" bet ");
    message.append(std::to_string(bet));
    message.append(" is out of range!");
    printMessage(message);
    return;
}

void OutputManager::showPlayerNotes(std::string playerName, std::vector<int>& notes)
{
    std::string message = playerName;
    message.append(" notes are: ");
    if(notes.empty()){
        message.append("{ }");
        printMessage(message);
        return;
    }
    message.append("{ ");
    for(int i = 0; i < notes.size(); i++){
        message.append(std::to_string(notes[i]));
        if(i != (notes.size() - 1)){            
            message.append(", ");
        }
        else{
            message.append(" }");
        }
    }
    printMessage(message);
    return;
}

void OutputManager::showPlayerBalanceUpdated(std::string name, int balance)
{
    std::string message = name;
    message.append(" balance updated. Balance is: ");
    message.append(std::to_string(balance));
    printMessage(message);
    return;
}

void OutputManager::showPlayerBetTypeUndefined(std::string name)
{
    std::string message = name;
    message.append(" has bet type undefined!");
    printMessage(message);
    return;
}

//
void OutputManager::showPlayerBalance(std::string name, int balance)
{
    std::string message = name;
    message.append(" balance is: ");
    message.append(std::to_string(balance));
    printMessage(message);
    if(toFile){ // if output is saved to file the print this message in console too
        forceOutputToConsole(message);
    }
    return;
}

void OutputManager::showPlayersTotalBalance(int playersQty, int totalBalance)
{
    std::string message = "Total ";
    message.append(std::to_string(playersQty));
    message.append(" players balance is: ");
    message.append(std::to_string(totalBalance));
    printMessage(message);
    if(toFile){ // if output is saved to file the print this message in console too
        forceOutputToConsole(message);
    }
    return;
}