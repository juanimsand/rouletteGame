#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "appgeneralmacros.h"

class OutputManager{
    
    public:

        OutputManager();
        ~OutputManager();

        void setOutputType(bool _type);   // set output to file or console by setting toFile member  
        void forceOutputToConsole(std::string message); // show messages that must be printed on console whatever toFile member value

        void printMessage(std::string message); // simple function for general messages
        void showWelcomeMessage();
        void showGoodByeMessage();
        void showBadArguments();
        void showHelp();    // must include macros file for help text usage
        // error messages
        void showErrorInformation(int error);

        // casino messages
        void showCasinoAlreadyOpen();
        void showOpeningCasino();
        void showCasinoOpened();
        void showCasinoAlreadyClose();
        void showClosingCasino();
        void showCasinoClosed();
        void showCouldNotJoinByCasino();
        void showCouldNotJoinByRouletteAvailable(std::string playerName);
        void showPlayerHasJoinedRoulette(std::string playerName, int rouletteId);
        void showCouldNotJoinByRouletteClosed(std::string playerName);
        void showClosingAllGames();

        // roulette messages
        void showRouletteOpened(int rouletteId);
        void showRouletteAlreadyOpen(int rouletteId);
        void showRouletteClosed(int rouletteId);
        void showRouletteAlreadyClose(int rouletteId);
        void showCouldNotPlayDueToClose(int rouletteId);
        void showCouldNotPlayDueToLackOfPlayers(int rouletteId);
        void showStartingRoulette(int rouletteId);
        void showRoulettePlayNumber(int rouletteId, int playNumber);
        void showLastRoulettePlay(int rouletteId);
        void showPlaceBets();
        void showNoMoreBets();
        void showRouletteSpinning();
        void showBallFlangOut();
        void showHouseWins();
        void showWinnerNumber(int number, bool red);
        void showBadPlayerType();
        void showNumberInfo(int number, bool red, bool even, bool minor);
        void showPlayerNotesTitle();

        // roulette player messages
        void showPlayerWon(std::string name, int playerId, std::string betType, int ammountWon);
        void showPlayerLost(std::string name, int playerId, std::string betType, int ammountWon);
        void showPlayerOutOfMoney(std::string name);
        void showPlayerBetOutOfRange(std::string name, int bet);
        void showPlayerNotes(std::string playerName, std::vector<int>& notes);
        void showPlayerBalanceUpdated(std::string name, int balance);
        void showPlayerBetTypeUndefined(std::string name);

        //
        void showPlayerBalance(std::string name, int balance);
        void showPlayersTotalBalance(int playersQty, int totalBalance);

    private:

        std::ofstream outputFile;
        bool toFile = false;
        void openFile();
        void messageToFile(std::string message);
        void messageToConsole(std::string message);
};

#endif