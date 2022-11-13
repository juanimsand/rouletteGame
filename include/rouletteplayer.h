#ifndef ROULETTEPLAYER_H
#define ROULETTEPLAYER_H

//#include "player.h"
#include <string>
#include <vector>
#include <iostream>
#include "outputmanager.h"

#define INITIAL_BALANCE         -10
#define INITIAL_BET             5
#define MAX_BET                 4000
#define MIN_BET                 5
#define RANGE_MIN               0
#define RANGE_MAX               36

#define EVEN_STRING             "even"
#define ODD_STRING              "odd"
#define RED_STRING              "red"
#define BLACK_STRING            "black"
#define MINOR_STRING            "minor"
#define MAJOR_STRING            "major"

typedef enum rouletteBetType{
    EVEN            = 0,
    ODD,
    MINOR,
    MAJOR,
    RED,
    BLACK
}rouletteBetType;


class RoulettePlayer {

    public:

        RoulettePlayer(rouletteBetType _type, int _playerId, std::string _name);
        ~RoulettePlayer();

        void setOutputManager(OutputManager& outputMan);

		int playerId;		// player id for let Casino keep track of players
		std::string name;	// lets name players as Player A, Player B, etc.

        void changeBetType(rouletteBetType newBetType);
		rouletteBetType getBetType() const;
		void won();
		void lost();
        void bet();	// allows the player to bet, expected call from roullete
        void getOutOfRoulette();    // player will leave roulette
        int getPlayerBalance() const;    // 

		// check if it is ok here, or maybe in an output manager
		void showNotes();
		void showWinner();
		void showLooser();
		void showStatus();
        void showBalance();		

        
    private:

        OutputManager* outputManager;
        
		rouletteBetType betType;	// initialize it in constructor
		std::vector<int> notes;		// initialize it in constructor
		int currentRouletteBet;
		int rouletteBalance;

		void resetNotes();
        void updateRouletteBalance(int addToBalance);
        void updateTotalNotesToBalance();
        std::string getBetTypeString();
};
#endif